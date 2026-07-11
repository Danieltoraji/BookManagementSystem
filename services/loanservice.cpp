#include "loanservice.h"
#include <algorithm>
#include "bookservice.h"
#include "userservice.h"
#include "bookcopyservice.h"
#include "dao/loandao.h"
#include "model/patron.h"

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
    if (targetUser->getCurrentBorrowBooks().size() >= targetUser->getBorrowLimit()) {
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
    //1.更改用户、图书各状态
    //2.添加借阅记录
    return false; // TODO: 实现借阅逻辑
}