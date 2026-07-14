#include "loanservice.h"
#include <algorithm>
#include <map>
#include <vector>
#include "bookservice.h"
#include "userservice.h"
#include "bookcopyservice.h"
#include "dao/loandao.h"
#include "model/patron.h"
#include "timeservice.h"

loanService::loanService()
{
    readLoansFromFile();
}

loanService& loanService::getInstance(){
    static loanService instance;
    return instance;
}

bool loanService::readLoansFromFile() {
    loans = LoanDao::getInstance().loadLoansFromFile("data/loans.txt");
    return !loans.empty();
}

bool loanService::writeLoansToFile() const {
    return LoanDao::getInstance().saveLoansToFile("data/loans.txt", loans);
}

bool loanService::borrowBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage) {
    //检查
    //1.书的信息和用户的信息对不对？
    if (!UserService::getInstance().getUserById(userId)) {
        errorMessage = "用户不存在";
        return false;
    }
    if (!BookService::getInstance().isBookValid(ISBN)) {
        errorMessage = "图书信息不存在";
        return false;
    }
    if (!bookCopyService::getInstance().getBookCopyByLibCode(libCode)) {
        errorMessage = "图书副本不存在";
        return false;
    }
    
    //2.该书是否被借阅？
    BookCopy* targetBookCopy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    if (targetBookCopy->getStatus() != available) {
        errorMessage = "图书副本已被借阅或不可用";
        return false;
    }
   
    //3.该用户的在借数量达到上限没有？

    Patron* targetUser = dynamic_cast<Patron*>(UserService::getInstance().getUserById(userId));
    if (!targetUser) {
        errorMessage = "用户不是借阅者";
        return false;
    }
    if (getBorrowingBooksByUser(userId).size() >= targetUser->getBorrowLimit()) {
        errorMessage = "用户已达到借阅上限";
        return false;
    }
    //4.该用户是否有未归还的逾期书籍？
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId && !loan.getIsReturned()) {
            if (loan.isOverdue()) {
                errorMessage = "用户有未归还的逾期书籍";
                return false;
            }
        }
    }
    //操作
    //1.更改图书状态
    targetBookCopy->setStatus(borrowed);
    //2.添加借阅记录
    std::string loanId = "LN" + std::to_string(loans.size() + 1); 
    Date loanDate = Date::today();
    Loan newLoan(loanId, libCode, ISBN, userId, loanDate, TimeService::getInstance().calculateDueDate(loanDate), Date(), false);
    loans.push_back(newLoan);
    writeLoansToFile();
    return true; 
}

bool loanService::renewBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage) {
    // 检查用户是否存在
    User* user = UserService::getInstance().getUserById(userId);
    if (!user) {
        errorMessage = "用户不存在";
        return false;
    }

    // 检查图书副本是否存在
    BookCopy* bookCopy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    if (!bookCopy) {
        errorMessage = "图书副本不存在";
        return false;
    }

    // 查找对应的借阅记录
    auto it = std::find_if(loans.begin(), loans.end(), [&](const Loan& loan) {
        return loan.getUserId() == userId && loan.getISBN() == ISBN && loan.getLibCode() == libCode && !loan.getIsReturned();
    });

    if (it == loans.end()) {
        errorMessage = "未找到对应的借阅记录";
        return false;
    }

    // 检查是否逾期
    if (it->isOverdue()) {
        errorMessage = "图书已逾期，无法续借";
        return false;
    }

    for (const auto& loan : loans) {
        if (loan.getUserId() == userId && !loan.getIsReturned()) {
            if (loan.isOverdue()) {
                errorMessage = "用户有未归还的逾期书籍";
                return false;
            }
        }
    }

    // 续借操作
    Date newDueDate = TimeService::getInstance().calculateRenewedDueDate(it->getDueDate());
    it->setDueDate(newDueDate);
    writeLoansToFile();
    return true;
}

bool loanService::returnBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage) {
    // 检查用户是否存在
    User* user = UserService::getInstance().getUserById(userId);
    if (!user) {
        errorMessage = "用户不存在";
        return false;
    }

    // 检查图书副本是否存在
    BookCopy* bookCopy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    if (!bookCopy) {
        errorMessage = "图书副本不存在";
        return false;
    }

    // 查找对应的借阅记录
    auto it = std::find_if(loans.begin(), loans.end(), [&](const Loan& loan) {
        return loan.getUserId() == userId && loan.getISBN() == ISBN && loan.getLibCode() == libCode && !loan.getIsReturned();
    });

    if (it == loans.end()) {
        errorMessage = "未找到对应的借阅记录";
        return false;
    }

    // 归还操作
    it->setIsReturned(true);
    it->setReturnDate(Date::today());
    bookCopy->setStatus(available);

    writeLoansToFile();
    return true;
}

std::vector<Loan> loanService::getBorrowingBooksByUser(const std::string& userId) {
    std::vector<Loan> borrowingLoans;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId && !loan.getIsReturned()) {
            borrowingLoans.push_back(loan);
        }
    }
    return borrowingLoans;
}

std::vector<Loan> loanService::getBorrowHistoryByUser(const std::string& userId) {
    std::vector<Loan> borrowHistory;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) {
            borrowHistory.push_back(loan);
        }
    }
    return borrowHistory;
}

std::vector<Loan> loanService::getBorrowHistoryByISBN(const std::string& ISBN) {
    std::vector<Loan> borrowHistory;
    for (const auto& loan : loans) {
        if (loan.getISBN() == ISBN) {
            borrowHistory.push_back(loan);
        }
    }
    return borrowHistory;
}

int loanService::getTotalBorrowedBooks() const {
    return loans.size();
}

int loanService::getTotalBorrowingBooks() const {
    return std::count_if(loans.begin(), loans.end(), [](const Loan& loan) {
        return !loan.getIsReturned();
    });
}

std::map<std::string, int> loanService::getMostBorrowedBooks(int topN) const {
    std::map<std::string, int> bookCount;
    for (const auto& loan : loans) {
        if (!loan.getIsReturned()) {
            bookCount[loan.getISBN()]++;
        }
    }
    return bookCount;
}

std::map<std::string, int> loanService::getMostActiveUsers(int topN) const{
    std::map<std::string, int> userCount;
    for (const auto& loan : loans) {
        if (!loan.getIsReturned()) {
            userCount[loan.getUserId()]++;
        }
    }
    return userCount;
}

std::map<std::string, int> loanService::getTotalBorrowVSMonth() const{
    std::map<std::string, int> monthCount;
    for (const auto& loan : loans) {
        monthCount[loan.getLoanDate().toYearMonthString()]++;
    }
    return monthCount;
}

std::map<std::string, int> loanService::getUserBorrowVSMonth(const std::string& userId) const{
    std::map<std::string, int> monthCount;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) {
            monthCount[loan.getLoanDate().toYearMonthString()]++;
        }
    }
    return monthCount;
}
