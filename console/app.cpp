#include "app.h"
#include "menu_base.h"
#include "admin_menu.h"
#include "user_menu.h"
#include "services/userservice.h"
#include "model/admin.h"
#include "model/patron.h"
#include <iostream>
#include <sstream>

void App::run()
{
    while (true) {
        if (!loginFlow()) {
            break;
        }
        // 根据角色分发菜单
        User *user = UserService::getInstance().currentUser;
        if (!user) {
            std::cout << "登录状态异常，请重新登录。" << std::endl;
            continue;
        }

        if (dynamic_cast<Admin *>(user)) {
            AdminMenu menu;
            menu.show();
        } else if (dynamic_cast<Patron *>(user)) {
            UserMenu menu;
            menu.show();
        }

        // 退出菜单后清除当前用户
        UserService::getInstance().currentUser = nullptr;
    }
    std::cout << "感谢使用图书管理系统，再见！" << std::endl;
    std::cout << "按回车键退出...";
    std::cin.get();
}

bool App::loginFlow()
{
    while (true) {
        int choice = showLoginMenu();
        switch (choice) {
            case 1: // 登录
                if (doLogin()) {
                    return true;
                }
                break;
            case 2: // 注册
                doRegister();
                break;
            case 3: // 关于
                About();
                break;
            case 0: // 退出
                return false;
        }
    }
}

int App::showLoginMenu()
{
    MenuBase::clearScreen();
    MenuBase::printSeparator('=');
    std::cout << "  图书管理系统 - 登录" << std::endl;
    MenuBase::printSeparator('=');
    std::cout << "  1. 登录" << std::endl;
    std::cout << "  2. 注册新用户" << std::endl;
    std::cout << "  3. 关于" << std::endl;
    std::cout << "  0. 退出系统" << std::endl;
    MenuBase::printSeparator('-');

    while (true) {
        std::string line;
        std::cout << "请选择操作: ";
        if (!std::getline(std::cin, line)) {
            return 0;
        }
        int choice = 0;
        std::istringstream iss(line);
        if (iss >> choice && choice >= 0 && choice <= 3) {
            return choice;
        }
        std::cout << "输入无效，请重新输入。" << std::endl;
    }
}

bool App::doLogin()
{
    std::cout << "\n--- 登录 ---" << std::endl;
    std::string id = MenuBase::readLine("请输入用户id: ");
    std::string password = MenuBase::readLine("请输入密码: ");

    User *user = UserService::getInstance().authenticate(id, password);
    if (user) {
        UserService::getInstance().currentUser = user;
        std::cout << "登录成功！欢迎，" << user->getUsername() << "。" << std::endl;
        MenuBase::pause();
        return true;
    } else {
        std::cout << "用户id或密码错误，登录失败。" << std::endl;
        MenuBase::pause();
        return false;
    }
}

void App::doRegister()
{
    std::cout << "\n--- 注册新用户 ---" << std::endl;
    std::string id = MenuBase::readLine("请输入用户ID: ");
    std::string username = MenuBase::readLine("请输入用户名: ");
    std::string phone = MenuBase::readLine("请输入电话: ");
    std::string email = MenuBase::readLine("请输入邮箱: ");
    std::string password = MenuBase::readLine("请输入密码: ");

    if (id.empty() || username.empty() || password.empty()) {
        std::cout << "用户ID、用户名和密码不能为空！" << std::endl;
        MenuBase::pause();
        return;
    }

    if (UserService::getInstance().getUserById(id)) {
        std::cout << "该用户ID已存在，注册失败。" << std::endl;
        MenuBase::pause();
        return;
    }

    if (UserService::getInstance().addPatron(id, username, phone, email, password)) {
        std::cout << "注册成功！请登录使用系统。" << std::endl;
    } else {
        std::cout << "注册失败，请重试。" << std::endl;
    }
    MenuBase::pause();
}

void App::About()
{
    AboutMenu aboutMenu;
    aboutMenu.show();
}