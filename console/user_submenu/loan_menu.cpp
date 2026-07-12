#include "loan_menu.h"

void LoanMenu::show() {
    std::vector<std::string> options = {
        "显示推荐信息",
        "借阅图书",
        "续借图书",
        "归还图书",
        "查看当前借阅",
        "查看借阅历史",
        "查看图书借阅历史",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("借阅管理", options);
        switch (choice) {
            case 1: displayRecommendations(); break;
            case 2: borrowBook(); break;
            case 3: renewBook(); break;
            case 4: returnBook(); break;
            case 5: displayCurrentLoans(); break;
            case 6: displayUserLoanHistory(); break;
            case 7: displayBookLoanHistory(); break;
            case 8: return; // 返回上级菜单
            default: std::cout << "无效的选择，请重新输入。" << std::endl;break;
        }
    }
}

void LoanMenu::displayRecommendations() {
    std::cout << "\n=== 显示推荐信息 ===" << std::endl;
    std::cout << "本馆总借阅量: " << loanService::getInstance().getTotalBorrowedBooks() << std::endl;
    std::cout << "当前总出借数: " << loanService::getInstance().getTotalBorrowingBooks() << std::endl;

    int topN = readInt("请输入要显示的前N名（最受欢迎图书和最活跃用户）: ");
    auto mostBorrowedBooks = loanService::getInstance().getMostBorrowedBooks(topN);
    auto mostActiveUsers = loanService::getInstance().getMostActiveUsers(topN);

    std::cout << "\n--- 最受欢迎图书 ---" << std::endl;
    for (const auto& pair : mostBorrowedBooks) {
        std::string title = BookService::getInstance().getBookTitleByISBN(pair.first);
        std::cout << "ISBN: " << pair.first << ", 标题: " << title << ", 借阅次数: " << pair.second << std::endl;
    }

    std::cout << "\n--- 最活跃用户 ---" << std::endl;
    for (const auto& pair : mostActiveUsers) {
        std::cout << "用户ID: " << pair.first << ", 借阅次数: " << pair.second << std::endl;
    }

    std::cout << "\n--- 每月借阅量 ---" << std::endl;
    auto totalBorrowVSMonth = loanService::getInstance().getTotalBorrowVSMonth();
    for (const auto& pair : totalBorrowVSMonth) {
        std::cout << "月份: " << pair.first << ", 借阅量: " << pair.second << std::endl;
    }

    User* user = UserService::getInstance().getCurrentUser();
    if (user) {
        std::cout << "\n--- 用户 " << user->getUsername() << " 的每月借阅量 ---" << std::endl;
        auto userBorrowVSMonth = loanService::getInstance().getUserBorrowVSMonth(user->getId());
        for (const auto& pair : userBorrowVSMonth) {
            std::cout << "月份: " << pair.first << ", 借阅量: " << pair.second << std::endl;
        }
    } else {
        std::cout << "\n未登录用户，无法显示个人每月借阅量。" << std::endl;
    }

    pause();
}

void LoanMenu::borrowBook() {
    std::cout << "\n=== 借阅图书 ===" << std::endl;
    std::string libCode = readLine("请输入图书副本编号: ");

    User* user = UserService::getInstance().getCurrentUser();
    std::string userId = user ? user->getId() : "";
    BookCopy* copy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    std::string ISBN = copy ? copy->getISBN() : "";
    std::string errorMessage;

    std::cout <<"您是"<< user->getUsername() << "，ID: " << userId << std::endl;
    std::cout <<"您要借阅的图书副本编号是: " << libCode << "，对应ISBN: " << ISBN << std::endl;
    std::cout <<"书名为: " << BookService::getInstance().getBookTitleByISBN(ISBN) << std::endl;
    std::cout <<"请确认是否继续借阅？(y/n): ";
    std::string confirm = readLine("");
    if (confirm != "y" && confirm != "Y") {
        std::cout << "借阅操作已取消。" << std::endl;
        pause();
        return;
    }

    if (loanService::getInstance().borrowBook(userId, ISBN, libCode, errorMessage)) {
        std::cout << "借阅成功！" << std::endl;
    } else {
        std::cout << "借阅失败: " << errorMessage << std::endl;
    }
    pause();
}

void LoanMenu::renewBook() {
    std::cout << "\n=== 续借图书 ===" << std::endl;
    displayCurrentLoans();
    std::string libCode = readLine("请输入图书副本编号: ");

    User* user = UserService::getInstance().getCurrentUser();
    std::string userId = user ? user->getId() : "";
    BookCopy* copy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    std::string ISBN = copy ? copy->getISBN() : "";
    std::string errorMessage;

    std::cout << "书名为: " << BookService::getInstance().getBookTitleByISBN(ISBN) << std::endl;

    if (loanService::getInstance().renewBook(userId, ISBN, libCode, errorMessage)) {
        std::cout << "续借成功！" << std::endl;
    } else {
        std::cout << "续借失败: " << errorMessage << std::endl;
    }
    pause();
}

void LoanMenu::returnBook() {
    std::cout << "\n=== 归还图书 ===" << std::endl;
    displayCurrentLoans();
    std::string libCode = readLine("请输入图书副本编号: ");

    User* user = UserService::getInstance().getCurrentUser();
    std::string userId = user ? user->getId() : "";
    BookCopy* copy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    std::string ISBN = copy ? copy->getISBN() : "";
    std::string errorMessage;

    std::cout << "书名为: " << BookService::getInstance().getBookTitleByISBN(ISBN) << std::endl;

    if (loanService::getInstance().returnBook(userId, ISBN, libCode, errorMessage)) {
        std::cout << "归还成功！" << std::endl;
    } else {
        std::cout << "归还失败: " << errorMessage << std::endl;
    }
    pause();
}

void LoanMenu::displayCurrentLoans() {
    std::cout << "\n=== 当前借阅 ===" << std::endl;
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法查看当前借阅。" << std::endl;
        pause();
        return;
    }
    std::string userId = user->getId();
    auto loans = loanService::getInstance().getBorrowingBooksByUser(userId);
    if (loans.empty()) {
        std::cout << "您当前没有借阅的图书。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMenu::displayUserLoanHistory() {
    std::cout << "\n=== 借阅历史 ===" << std::endl;
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法查看借阅历史。" << std::endl;
        pause();
        return;
    }
    std::string userId = user->getId();
    auto loans = loanService::getInstance().getBorrowHistoryByUser(userId);
    if (loans.empty()) {
        std::cout << "您没有借阅历史记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMenu::displayBookLoanHistory() {
    std::cout << "\n=== 图书借阅历史 ===" << std::endl;
    std::string ISBN = readLine("请输入图书ISBN: ");
    std::cout << "书名: " << BookService::getInstance().getBookTitleByISBN(ISBN) << std::endl;
    auto loans = loanService::getInstance().getBorrowHistoryByISBN(ISBN);
    if (loans.empty()) {
        std::cout << "该图书没有借阅历史记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMenu::printLoans(const std::vector<Loan>& loans) {
    printSeparator('=');
    std::cout << std::left
              << std::setw(10) << "借阅ID"
              << std::setw(15) << "副本编号"
              << std::setw(18) << "ISBN"
              << std::setw(25) << "书名"
              << std::setw(20) << "借阅日期"
              << std::setw(20) << "到期日期"
              << std::setw(20) << "归还日期"
              << std::setw(10) << "状态" 
              << std::endl;
    printSeparator('-');

    for (const auto& loan : loans) {
        std::string status = loan.getIsReturned() ? "已归还" : (loan.isOverdue() ? "逾期" : "借阅中");
        std::string title = BookService::getInstance().getBookTitleByISBN(loan.getISBN());
        std::cout << std::left
                  << std::setw(10) << loan.getId()
                  << std::setw(15) << loan.getLibCode()
                  << std::setw(18) << loan.getISBN()
                  << std::setw(25) << title
                  << std::setw(20) << loan.getLoanDate().toString()
                  << std::setw(20) << loan.getDueDate().toString()
                  << std::setw(20) << (loan.getIsReturned() ? loan.getReturnDate().toString() : "-")
                  << std::setw(10) << status
                  << std::endl;
    }
    printSeparator('=');
}






