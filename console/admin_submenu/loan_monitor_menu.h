#ifndef LOAN_MONITOR_MENU_H
#define LOAN_MONITOR_MENU_H

#include "../menu_base.h"
#include "model/loan.h"
#include "services/loanservice.h"
#include "services/bookservice.h"
#include "services/userservice.h"
#include "services/bookcopyservice.h"
#include <vector>
#include <iostream>
#include <iomanip>


// 借阅监控菜单：查看、搜索借阅记录，统计分析，文件读写
class LoanMonitorMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void displayAllLoans();
    void searchByUser();
    void searchByISBN();
    void searchByLibCode();
    void displayAllCurrentBorrowing();
    void displayUserCurrentBorrowing();
    void displayStatistics();
    void displayMostBorrowed();
    void displayMostActiveUsers();
    void displayMonthlyStats();
    void readFromFile();
    void saveToFile();

    // 辅助：打印借阅记录列表
    void printLoans(const std::vector<Loan> &loans);
};

#endif // LOAN_MONITOR_MENU_H
