#include "about_menu.h"

void AboutMenu::show()
{   
    std::string title = "关于";
    std::vector<std::string> options = {
        "图书管理系统",
        "无52 丁一博",
        "清华大学电子工程系 计算机程序设计基础大作业",
        "返回上级菜单"
    };
    while (true){
        int choice = displayMenu(title, options);
        switch (choice) {
            case 1:
                std::cout << "大模型正在准备为您回答..." << std::endl;
                Sleep(3000);
                std::cout << R"( # 图书管理系统简介

                这是一个 **C++ 图书管理系统**，是**清华大学电子工程系计算机程序设计基础大作业**（作者：无52 丁一博）。

                ## 系统架构

                按**分层架构**设计，分为三层：

                ### 1. 模型层 (model)
                核心数据实体：
                - `Book` / `BookCopy` — 图书及副本
                - `User` / `Admin` / `Patron` — 用户、管理员、借阅者
                - `Loan` — 借阅记录
                - `Date` / `Location` — 日期与位置

                ### 2. 数据访问层 (dao)
                负责文件数据持久化：
                - `bookdao` / `bookcopydao` / `userdao` / `loandao`
                - 数据存储于 data 目录下的文本文件（`books.txt`、`users.txt`、`loans.txt`、`bookcopies.txt`）

                ### 3. 业务服务层 (services)
                封装核心业务逻辑：
                - `BookService` / `BookCopyService` — 图书管理
                - `UserService` — 用户管理
                - `LoanService` — 借还书
                - `TimeService` — 时间相关

                ### 4. 控制台界面 (console)
                - **主菜单**: `app.cpp` — 程序入口，区分用户/管理员
                - **用户菜单**: `user_menu.cpp` → `search_info_menu`、`loan_menu`、`personal_info_menu`
                - **管理员菜单**: `admin_menu.cpp` → `book_monitor_menu`、`bookcopy_monitor_menu`、`loan_monitor_menu`、`user_monitor_menu`
                - **关于**: `about_menu.cpp`

                ## 构建方式

                使用 **CMake** 构建，支持 Visual Studio 和 MinGW 编译器。)" << std::endl;
                break;
            case 2:
                std::cout << R"(关注小呆谢谢喵！
    Github:https://github.com/Danieltoraji
    公众号：钉小呆
                    )" << std::endl;
                break;
            case 3:
                std::cout << "不知课改后还有没有图书管理系统这个作业？" << std::endl;
                break;
            case 4:
                return; // 返回上级菜单
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
                break;
        }
    pause();
    }
    
}