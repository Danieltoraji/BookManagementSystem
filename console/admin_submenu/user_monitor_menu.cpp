#include "user_monitor_menu.h"
#include "services/userservice.h"
#include "model/user.h"
#include "model/patron.h"
#include "model/admin.h"
#include <iostream>
#include <iomanip>

void UserMonitorMenu::show()
{
    std::vector<std::string> options = {
        "查看所有用户",
        "按ID查询用户",
        "按用户名查询用户",
        "添加读者",
        "添加管理员",
        "修改用户信息",
        "修改用户密码",
        "删除用户",
        "从文件读取用户",
        "保存用户到文件",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("用户监控", options);
        switch (choice) {
            case 1: displayAllUsers(); break;
            case 2: searchById(); break;
            case 3: searchByUsername(); break;
            case 4: addPatron(); break;
            case 5: addAdmin(); break;
            case 6: updateUserInfo(); break;
            case 7: updatePassword(); break;
            case 8: removeUser(); break;
            case 9: readFromFile(); break;
            case 10: saveToFile(); break;
            case 11: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void UserMonitorMenu::displayAllUsers()
{
    std::cout << "\n=== 查看所有用户 ===" << std::endl;
    for (const User* user : UserService::getInstance().getAllUsers()) {
        if (user) {
            std::cout << "ID: " << user->getId() << ", 用户名: " << user->getUsername() << std::endl;
        }
    }
    pause();
}

void UserMonitorMenu::searchById()
{
    std::cout << "\n=== 按ID查询用户 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::searchByUsername()
{
    std::cout << "\n=== 按用户名查询用户 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::addPatron()
{
    std::cout << "\n=== 添加读者 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::addAdmin()
{
    std::cout << "\n=== 添加管理员 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::updateUserInfo()
{
    std::cout << "\n=== 修改用户信息 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::updatePassword()
{
    std::cout << "\n=== 修改用户密码 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::removeUser()
{
    std::cout << "\n=== 删除用户 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取用户 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存用户到文件 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void UserMonitorMenu::printUsers(const std::vector<User*> &users)
{
    (void)users; // 框架阶段暂不使用
    std::cout << "此功能待实现。" << std::endl;
}
