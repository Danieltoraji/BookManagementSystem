#include "user_menu.h"
#include "services/bookservice.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void UserMenu::show()
{
    std::vector<std::string> options = {
        "图书查找和搜索",
        "图书借还"
        "个人信息管理",
        "退出登录"
    };

    while (true) {
        int choice = displayMenu("用户系统", options);
        switch (choice) {
            case 1: SearchInfoMenu().show(); break;
            //case 2: searchBooks(); break;
            //case 3: searchCopies(); break;
            //case 4: borrowBook(); break;
            //case 5: returnBook(); break;
            case 3: return; // 退出登录
            default: std::cout << "无效的选择，请重新输入。" << std::endl;break;
        }
        
    }
}
