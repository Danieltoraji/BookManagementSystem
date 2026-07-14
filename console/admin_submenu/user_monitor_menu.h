#ifndef USER_MONITOR_MENU_H
#define USER_MONITOR_MENU_H

#include "../menu_base.h"
#include "services/userservice.h"
#include "model/user.h"
#include "model/patron.h"
#include "model/admin.h"
#include <vector>
#include <iostream>
#include <iomanip>

// 用户监控菜单：查看、搜索、增删改用户，文件读写
class UserMonitorMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void displayAllUsers();
    void searchById();
    void searchByUsername();
    void addPatron();
    void addAdmin();
    void updateUserInfo();
    void updatePassword();
    void removeUser();
    void readFromFile();
    void saveToFile();

    // 辅助：打印用户列表
    void printUsers(const std::vector<User*> &users);
};

#endif // USER_MONITOR_MENU_H
