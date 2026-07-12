#include "loan_monitor_menu.h"
#include "services/loanservice.h"
#include <iostream>
#include <iomanip>

void LoanMonitorMenu::show()
{
    std::vector<std::string> options = {
        "查看所有借阅记录",
        "按用户查询借阅历史",
        "按ISBN查询借阅历史",
        "查看用户当前借阅",
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
            case 4: displayCurrentBorrowing(); break;
            case 5: displayStatistics(); break;
            case 6: displayMostBorrowed(); break;
            case 7: displayMostActiveUsers(); break;
            case 8: displayMonthlyStats(); break;
            case 9: readFromFile(); break;
            case 10: saveToFile(); break;
            case 11: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void LoanMonitorMenu::displayAllLoans()
{
    std::cout << "\n=== 查看所有借阅记录 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::searchByUser()
{
    std::cout << "\n=== 按用户查询借阅历史 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::searchByISBN()
{
    std::cout << "\n=== 按ISBN查询借阅历史 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::displayCurrentBorrowing()
{
    std::cout << "\n=== 查看用户当前借阅 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::displayStatistics()
{
    std::cout << "\n=== 借阅统计概览 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::displayMostBorrowed()
{
    std::cout << "\n=== 最受欢迎图书排行 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::displayMostActiveUsers()
{
    std::cout << "\n=== 最活跃用户排行 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::displayMonthlyStats()
{
    std::cout << "\n=== 每月借阅量统计 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取借阅记录 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存借阅记录到文件 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void LoanMonitorMenu::printLoans(const std::vector<Loan> &loans)
{
    (void)loans; // 框架阶段暂不使用
    std::cout << "此功能待实现。" << std::endl;
}
