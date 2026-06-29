#include "userservice.h"
#include <algorithm>

userService& userService::getInstance()
{
    static userService instance;
    return instance;
}

userService::userService() {}

bool userService::readUsersFromFile()
{
    // 释放旧数据
    for (User* user : users) {
        delete user;//因为users是基类
    }
    users.clear();

    users = UserDao::getInstance().loadUsersFromFile("data/users.txt");
    return !users.empty();
}

bool userService::writeUsersToFile() const
{
    return UserDao::getInstance().saveUsersToFile("data/users.txt", users);
}

std::vector<User*> userService::getAllUsers() const
{
    return users;
}

bool userService::addUser(User* user)
{
    auto it = std::find_if(users.begin(), users.end(),
    [&](User* u) { return u->getId() == user->getId(); });

    if (it == users.end()) {
        users.push_back(user);
        writeUsersToFile(); // 自动更新文件
        return true;
    }
    return false;
}

bool userService::removeUser(const std::string& id)
{
    auto it = std::find_if(users.begin(), users.end(),
    [&](User* u) { return u->getId() == id; });

    if (it == users.end()) {
        return false;
    }
    delete *it;
    users.erase(it);
    writeUsersToFile(); // 自动更新文件
    return true;
}

bool userService::updateUser(const std::string& id, User* user)
{
    auto it = std::find_if(users.begin(), users.end(), [&](User* u) {
        return u->getId() == id;
    });

    if (it != users.end()) {
        delete *it;
        *it = user;
        writeUsersToFile(); // 自动更新文件
        return true;
    }
    return false;
}

User* userService::getUserById(const std::string& id) const
{
    auto it = std::find_if(users.begin(), users.end(),
    [&](User* u) { return u->getId() == id; });

    if (it != users.end()) {
        return *it;
    }
    return nullptr;
}

User* userService::getUserByUsername(const std::string& username) const
{
    auto it = std::find_if(users.begin(), users.end(),
    [&](User* u) { return u->getUsername() == username; });

    if (it != users.end()) {
        return *it;
    }
    return nullptr;
}

User* userService::authenticate(const std::string& username) const
{
    return getUserByUsername(username);
}
