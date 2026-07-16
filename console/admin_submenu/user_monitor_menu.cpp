#include "user_monitor_menu.h"

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
    printUsers(UserService::getInstance().getAllUsers());
    pause();
}

void UserMonitorMenu::searchById()
{
    std::cout << "\n=== 按ID查询用户 ===" << std::endl;
    std::string id = readLine("请输入用户ID: ");
    User* user = UserService::getInstance().getUserById(id);
    if (user) {
        printUsers({user});
    } else {
        std::cout << "未找到ID为 " << id << " 的用户。" << std::endl;
    }
    pause();
}

void UserMonitorMenu::searchByUsername()
{
    std::cout << "\n=== 按用户名查询用户 ===" << std::endl;
    std::string username = readLine("请输入用户名: ");
    User* user = UserService::getInstance().getUserByUsername(username);
    if (user) {
        printUsers({user});
    } else {
        std::cout << "未找到用户名为 " << username << " 的用户。" << std::endl;
    }
    pause();
}

void UserMonitorMenu::addPatron()
{
    std::cout << "\n=== 添加读者 ===" << std::endl;
    std::string id = readLine("请输入读者ID: ");
    if (UserService::getInstance().getUserById(id)) {
        std::cout << "ID已存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    std::string username = readLine("请输入用户名: ");
    std::string phone = readLine("请输入电话: ");
    std::string email = readLine("请输入邮箱: ");
    std::string password = readLine("请输入密码: ");
    int borrowLimit = readInt("请输入借阅上限（默认5）: ");
    UserService::getInstance().addPatron(id, username, phone, email, password, borrowLimit);
    std::cout << "读者添加成功。" << std::endl;
    pause();
}

void UserMonitorMenu::addAdmin()
{
    std::cout << "\n=== 添加管理员 ===" << std::endl;
    std::string id = readLine("请输入管理员ID: ");
    if (UserService::getInstance().getUserById(id)) {
        std::cout << "ID已存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    std::string username = readLine("请输入用户名: ");
    std::string phone = readLine("请输入电话: ");
    std::string email = readLine("请输入邮箱: ");
    std::string password = readLine("请输入密码: ");
    UserService::getInstance().addAdmin(id, username, phone, email, password);
    std::cout << "管理员添加成功。" << std::endl;
    pause();
}

void UserMonitorMenu::updateUserInfo()
{
    std::cout << "\n=== 修改用户信息 ===" << std::endl;
    std::string id = readLine("请输入要修改的用户ID: ");
    User* user = UserService::getInstance().getUserById(id);
    if (!user) {
        std::cout << "未找到ID为 " << id << " 的用户。" << std::endl;
        pause();
        return;
    } else if (dynamic_cast<Patron*>(user)) {
        std::cout << "请输入新的用户信息。留空表示不变。" << std::endl;
        std::string username = readLine("请输入新的用户名: ");
        username = username.empty() ? user->getUsername() : username;
        std::string phone = readLine("请输入新的电话: ");
        phone = phone.empty() ? user->getPhone() : phone;
        std::string email = readLine("请输入新的邮箱: ");
        email = email.empty() ? user->getEmail() : email;
        int borrowLimit = readInt("请输入新的借阅上限: ");
        borrowLimit = (borrowLimit == 0) ? dynamic_cast<Patron*>(user)->getBorrowLimit() : borrowLimit;
        UserService::getInstance().updatePatron(id, username, phone, email, borrowLimit);
        std::cout << "读者信息修改成功。" << std::endl;
    } else if (dynamic_cast<Admin*>(user)) {
        std::cout << "请输入新的用户信息。留空表示不变。" << std::endl;
        std::string username = readLine("请输入新的用户名: ");
        username = username.empty() ? user->getUsername() : username;
        std::string phone = readLine("请输入新的电话: ");
        phone = phone.empty() ? user->getPhone() : phone;
        std::string email = readLine("请输入新的邮箱: ");
        email = email.empty() ? user->getEmail() : email;
        UserService::getInstance().updateAdmin(id, username, phone, email);
        std::cout << "管理员信息修改成功。" << std::endl;
    }
      else {
        std::cout << "未知用户类型，无法修改。" << std::endl;
    }
    pause();
}

void UserMonitorMenu::updatePassword()
{
    std::cout << "\n=== 修改用户密码 ===" << std::endl;
    std::string id = readLine("请输入要修改的用户ID: ");
    User* user = UserService::getInstance().getUserById(id);
    if (!user) {
        std::cout << "未找到ID为 " << id << " 的用户。" << std::endl;
        pause();
        return;
    }
    std::string newPassword = readLine("请输入新密码: ");
    if (dynamic_cast<Patron*>(user)) {
        std::string confirmation = readLine("您正在免认证修改读者密码。请确保您得到了该读者的授权。输入'y'确认: ");
        if (confirmation != "y" && confirmation != "Y") {
            std::cout << "操作已取消。" << std::endl;
            pause();
            return;
        }
        UserService::getInstance().updatePatronPassword(id, newPassword);
        std::cout << "修改成功。" << std::endl;
    } else if (dynamic_cast<Admin*>(user)) {
        std::string originalPassword = readLine("修改管理员密码需要验证。请输入原密码: ");
        if (UserService::getInstance().encryptPassword(originalPassword, id) != user->getPassword()) {
            std::cout << "原密码错误，无法修改。" << std::endl;
            pause();
            return;
        }
        else {
            UserService::getInstance().updateAdminPassword(id, newPassword);
            std::cout << "修改成功。" << std::endl;
        }
    }   
    else {
        std::cout << "未知用户类型，无法修改密码。" << std::endl;
        pause();
        return;
    }
    std::cout << "密码修改成功。" << std::endl;
    pause();
}

void UserMonitorMenu::removeUser()
{
    std::cout << "\n=== 删除用户 ===" << std::endl;
    std::string id = readLine("请输入要删除的用户ID: ");
    if (!UserService::getInstance().getUserById(id)) {
        std::cout << "未找到ID为 " << id << " 的用户。" << std::endl;
        pause();
        return;
    }
    std::string confirmation = readLine("确认删除用户 " + id + " 吗？(y/n): ");
    if (confirmation != "y" && confirmation != "Y") {
        std::cout << "操作已取消。" << std::endl;
        pause();
        return;
    }
    if (UserService::getInstance().getCurrentUser() && UserService::getInstance().getCurrentUser()->getId() == id) {
        std::cout << "你不能删除你自己。否则可能会导致再无管理员账户。" << std::endl;
        pause();
        return;
    }
    std::string errorMessage;
    if (UserService::getInstance().removeUser(id, errorMessage)) {
        std::cout << "用户删除成功。" << std::endl;
    } else {
        std::cout << "用户删除失败：" << errorMessage << std::endl;
    }
    pause();
}

void UserMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取用户 ===" << std::endl;
    UserService::getInstance().readUsersFromFile();
    std::cout << "用户已从文件读取。" << std::endl;
    pause();
}

void UserMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存用户到文件 ===" << std::endl;
    UserService::getInstance().writeUsersToFile();
    std::cout << "用户已保存到文件。" << std::endl;
    pause();
}

void UserMonitorMenu::printUsers(const std::vector<User*> &users)
{
    std::cout<< std::left << std::setw(10) << "类型" 
             << std::setw(15) << "ID" 
             << std::setw(20) << "用户名" 
             << std::setw(15) << "电话" 
             << std::setw(30) << "邮箱" 
             << std::setw(10) << "借阅上限" 
             << std::endl;
    for (const User* user : users) {
        if (user) {
            std::string type = dynamic_cast<const Patron*>(user) ? "读者" : "管理员";
            std::string borrowLimit = dynamic_cast<const Patron*>(user) ? std::to_string(dynamic_cast<const Patron*>(user)->getBorrowLimit()) : "-";
            std::cout << std::left << std::setw(10) << type
                      << std::setw(15) << user->getId()
                      << std::setw(20) << user->getUsername()
                      << std::setw(15) << user->getPhone()
                      << std::setw(30) << user->getEmail()
                      << std::setw(10) << borrowLimit
                      << std::endl;
        }
    }
}
