#include "loan_monitor_menu.h"


void LoanMonitorMenu::show()
{
    std::vector<std::string> options = {
        "查看所有借阅记录",
        "按用户查询借阅历史",
        "按ISBN查询借阅历史",
        "按馆藏号查询借阅历史",
        "查看所有在借图书",
        "查看特定用户的当前借阅",
        "借阅统计概览",
        "最受欢迎图书排行",
        "最活跃用户排行",
        "每月借阅量统计",
        "从文件读取借阅记录",
        "保存借阅记录到文件",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("借阅监控", options);
        switch (choice) {
            case 1: displayAllLoans(); break;
            case 2: searchByUser(); break;
            case 3: searchByISBN(); break;
            case 4: searchByLibCode(); break;
            case 5: displayAllCurrentBorrowing(); break;
            case 6: displayUserCurrentBorrowing(); break;
            case 7: displayStatistics(); break;
            case 8: displayMostBorrowed(); break;
            case 9: displayMostActiveUsers(); break;
            case 10: displayMonthlyStats(); break;
            case 11: readFromFile(); break;
            case 12: saveToFile(); break;
            case 13: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void LoanMonitorMenu::displayAllLoans()
{
    std::cout << "\n=== 查看所有借阅记录 ===" << std::endl;
    printLoans(loanService::getInstance().loans);
    pause();
}

void LoanMonitorMenu::searchByUser()
{
    std::cout << "\n=== 按用户查询借阅历史 ===" << std::endl;
    std::string userId = readLine("请输入用户ID: ");
    auto loans = loanService::getInstance().getBorrowHistoryByUser(userId);
    if (loans.empty()) {
        std::cout << "该用户没有借阅历史记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMonitorMenu::searchByISBN()
{
    std::cout << "\n=== 按ISBN查询借阅历史 ===" << std::endl;
    std::string ISBN = readLine("请输入图书ISBN: ");
    auto loans = loanService::getInstance().getBorrowHistoryByISBN(ISBN);
    if (loans.empty()) {
        std::cout << "该图书没有借阅历史记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMonitorMenu::searchByLibCode()
{
    std::cout << "\n=== 按馆藏号查询借阅历史 ===" << std::endl;
    std::string libCode = readLine("请输入图书馆藏号: ");
    auto loans = loanService::getInstance().getBorrowHistoryByLibCode(libCode);
    if (loans.empty()) {
        std::cout << "该馆藏号没有借阅历史记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMonitorMenu::displayAllCurrentBorrowing()
{
    std::cout << "\n=== 查看所有在借图书 ===" << std::endl;
    auto loans = loanService::getInstance().getAllCurrentBorrowing();
    if (loans.empty()) {
        std::cout << "当前没有在借图书。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMonitorMenu::displayUserCurrentBorrowing()
{
    std::cout << "\n=== 查看特定用户的当前借阅 ===" << std::endl;
    std::string userId = readLine("请输入用户ID: ");
    auto loans = loanService::getInstance().getBorrowingBooksByUser(userId);
    if (loans.empty()) {
        std::cout << "该用户没有当前借阅记录。" << std::endl;
    } else {
        printLoans(loans);
    }
    pause();
}

void LoanMonitorMenu::displayStatistics()
{
    std::cout << "\n=== 借阅统计概览 ===" << std::endl;
    std::cout << "当前在借图书数量: " << loanService::getInstance().getTotalBorrowingBooks() << std::endl;
    std::cout << "总借阅量: " << loanService::getInstance().getTotalBorrowedBooks() << std::endl;
    pause();
}

void LoanMonitorMenu::displayMostBorrowed()
{
    std::cout << "\n=== 最受欢迎图书排行 ===" << std::endl;
    std::cout << std::left << std::setw(20) << "ISBN" << std::setw(20) << "书名" << std::setw(20) << "借阅次数" << std::endl;
    for (const auto& entry : loanService::getInstance().getMostBorrowedBooks(10)) {
        std::cout << std::left << std::setw(20) << entry.first << std::setw(20) << BookService::getInstance().getBookTitleByISBN(entry.first) << std::setw(20) << entry.second << std::endl;
    }
    pause();
}

void LoanMonitorMenu::displayMostActiveUsers()
{
    std::cout << "\n=== 最活跃用户排行 ===" << std::endl;
    std::cout << std::left << std::setw(20) << "用户ID" << std::setw(20) << "借阅次数" << std::endl;
    for (const auto& entry : loanService::getInstance().getMostActiveUsers(10)) {
        std::cout << std::left << std::setw(20) << entry.first << std::setw(20) << entry.second << std::endl;
    }
    pause();
}

void LoanMonitorMenu::displayMonthlyStats()
{
    std::cout << "\n=== 每月借阅量统计 ===" << std::endl;
    std::cout << std::left << std::setw(20) << "月份" << std::setw(20) << "借阅量" << std::endl;
    for (const auto& entry : loanService::getInstance().getTotalBorrowVSMonth()) {
        std::cout << std::left << std::setw(20) << entry.first << std::setw(20) << entry.second << std::endl;
    }
    pause();
}

void LoanMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取借阅记录 ===" << std::endl;
    loanService::getInstance().readLoansFromFile();
    std::cout << "借阅记录已从文件读取。" << std::endl;
    pause();
}

void LoanMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存借阅记录到文件 ===" << std::endl;
    loanService::getInstance().writeLoansToFile();
    std::cout << "借阅记录已保存到文件。" << std::endl;
    pause();
}

void LoanMonitorMenu::printLoans(const std::vector<Loan> &loans)
{
    std::cout << std::left << std::setw(15) << "借阅ID"
              << std::setw(10) << "馆藏号"
              << std::setw(20) << "书名"
              << std::setw(15) << "用户ID"
              << std::setw(12) << "借阅日期"
              << std::setw(12) << "到期日期"
              << std::setw(12) << "归还日期"
              << std::setw(10) << "状态" << std::endl;
    for (const auto &loan : loans) {
        std::cout << std::left << std::setw(15) << loan.getId()
                  << std::setw(10) << loan.getLibCode()
                  << std::setw(20) << BookService::getInstance().getBookTitleByISBN(loan.getISBN())
                  << std::setw(15) << loan.getUserId()
                  << std::setw(12) << loan.getLoanDate().toString()
                  << std::setw(12) << loan.getDueDate().toString()
                  << std::setw(12) << (loan.getIsReturned() ? loan.getReturnDate().toString() : "未归还")
                  << std::setw(10) << (loan.getIsReturned() ? "已归还" : (loan.isOverdue() ? "逾期" : "借阅中"))
                  << std::endl;
    }
}
