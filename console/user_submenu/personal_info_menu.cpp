#include "personal_info_menu.h"

void PersonalInfoMenu::show() {
    std::vector<std::string> options = {
        "显示个人信息",
        "修改个人信息",
        "修改密码",
        "注销账户",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("个人信息管理", options);
        switch (choice) {
            case 1: displayPersonalInfo(); break;
            case 2: updatePersonalInfo(); break;
            case 3: changePassword(); break;
            case 4: deleteAccount(); break;
            case 5: return; // 返回上级菜单
            default: std::cout << "无效的选择，请重新输入。" << std::endl;break;
        }
    }
}

void PersonalInfoMenu::displayPersonalInfo() {
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法显示个人信息。" << std::endl;
        pause();
        return;
    }

    std::cout << "\n=== 个人信息 ===" << std::endl;
    std::cout << "用户ID: " << user->getId() << std::endl;
    std::cout << "用户名: " << user->getUsername() << std::endl;
    std::cout << "电话: " << user->getPhone() << std::endl;
    std::cout << "邮箱: " << user->getEmail() << std::endl;

    if (Patron* patron = dynamic_cast<Patron*>(user)) {
        std::cout << "借阅上限: " << patron->getBorrowLimit() << std::endl;
        std::cout << "当前借阅数: " << patron->getCurrentBorrowBooks().size() << std::endl;
    }

    pause();
}

void PersonalInfoMenu::updatePersonalInfo() {
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法修改个人信息。" << std::endl;
        pause();
        return;
    }

    std::cout << "\n=== 修改个人信息 ===" << std::endl;
    std::string newUsername = readLine("请输入新的用户名（留空表示不修改）: ");
    std::string newPhone = readLine("请输入新的电话（留空表示不修改）: ");
    std::string newEmail = readLine("请输入新的邮箱（留空表示不修改）: ");

    if (!newUsername.empty()) user->setUsername(newUsername);
    if (!newPhone.empty()) user->setPhone(newPhone);
    if (!newEmail.empty()) user->setEmail(newEmail);

    if (UserService::getInstance().updatePatron(user->getId(), user->getUsername(), user->getPhone(),
                                                user->getEmail())) {
        std::cout << "个人信息更新成功！" << std::endl;
    } else {
        std::cout << "个人信息更新失败！" << std::endl;
    }
    pause();
}

void PersonalInfoMenu::changePassword() {
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法修改密码。" << std::endl;
        pause();
        return;
    }

    std::cout << "\n=== 修改密码 ===" << std::endl;
    std::string oldPassword = readLine("请输入旧密码: ");
    if (user->getPassword() != UserService::getInstance().encryptPassword(oldPassword, user->getId())) {
        std::cout << "旧密码不正确！" << std::endl;
        pause();
        return;
    }

    std::string newPassword = readLine("请输入新密码: ");
    user->setPassword(UserService::getInstance().encryptPassword(newPassword, user->getId()));

    if (UserService::getInstance().updatePatron(user->getId(), user->getUsername(), user->getPhone(),
                                                user->getEmail(), user->getPassword())) {
        std::cout << "密码修改成功！" << std::endl;
    } else {
        std::cout << "密码修改失败！" << std::endl;
    }
    pause();
}

void PersonalInfoMenu::deleteAccount() {
    User* user = UserService::getInstance().getCurrentUser();
    if (!user) {
        std::cout << "未登录用户，无法注销账户。" << std::endl;
        pause();
        return;
    }

    std::cout << "\n=== 注销账户 ===" << std::endl;
    std::string confirmation = readLine("我真求你了，此操作不可逆！(yes/no): ");
    if (confirmation != "yes") {
        std::cout << "账户注销已取消。" << std::endl;
        pause();
        return;
    }
    confirmation = readLine("您确定要注销账户吗？这是最后一次警告。此操作不可逆！(YES/NO): ");
    if (confirmation == "YES") {
        if (UserService::getInstance().removeUser(user->getId())) {
            std::cout << "账户已成功注销！" << std::endl;
            // 退出登录
            UserService::getInstance().currentUser = nullptr;
        } else {
            std::cout << "账户注销失败！" << std::endl;
        }
    } else {
        std::cout << "账户注销已取消。" << std::endl;
    }
    pause();
}

