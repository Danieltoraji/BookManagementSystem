#include "admin_menu.h"
#include <iostream>

void AdminMenu::show()
{
    std::vector<std::string> options = {
        "用户监控",
        "图书监控",
        "图书副本监控",
        "借阅监控",
        "退出登录"
    };

    while (true) {
        int choice = displayMenu("管理员系统", options);
        switch (choice) {
            case 1: UserMonitorMenu().show(); break;
            case 2: BookMonitorMenu().show(); break;
            case 3: BookCopyMonitorMenu().show(); break;
            case 4: LoanMonitorMenu().show(); break;
            case 5: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}