#include "userservice.h"
#include "model/admin.h"
#include "model/patron.h"
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

bool userService::addPatron(const std::string& id, const std::string& username, const std::string& phone,
                            const std::string& email, const std::string& plainPassword, int borrowLimit)
{
    if (getUserById(id)) {
        return false; // ID 已存在
    }
    std::string encrypted = encryptPassword(plainPassword, id);
    User* user = new Patron(id, username, phone, email, encrypted, borrowLimit);
    users.push_back(user);
    writeUsersToFile();
    return true;
}

bool userService::addAdmin(const std::string& id, const std::string& username, const std::string& phone,
                           const std::string& email, const std::string& plainPassword)
{
    if (getUserById(id)) {
        return false; // ID 已存在
    }
    std::string encrypted = encryptPassword(plainPassword, id);
    User* user = new Admin(id, username, phone, email, encrypted);
    users.push_back(user);
    writeUsersToFile();
    return true;
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

bool userService::updatePatron(const std::string& id, const std::string& username, const std::string& phone,
                               const std::string& email, const std::string& plainPassword, int borrowLimit)
{
    auto it = std::find_if(users.begin(), users.end(), [&](User* u) {
        return u->getId() == id;
    });

    if (it == users.end()) {
        return false;
    }
    delete *it;
    std::string encrypted = encryptPassword(plainPassword, id);
    *it = new Patron(id, username, phone, email, encrypted, borrowLimit);
    writeUsersToFile();
    return true;
}

bool userService::updateAdmin(const std::string& id, const std::string& username, const std::string& phone,
                              const std::string& email, const std::string& plainPassword)
{
    auto it = std::find_if(users.begin(), users.end(), [&](User* u) {
        return u->getId() == id;
    });

    if (it == users.end()) {
        return false;
    }
    delete *it;
    std::string encrypted = encryptPassword(plainPassword, id);
    *it = new Admin(id, username, phone, email, encrypted);
    writeUsersToFile();
    return true;
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

std::string userService::encryptPassword(const std::string& password, const std::string& key) const
{
    // 
    std::string encrypted = password;
    for (size_t i = 0; i < encrypted.length(); ++i) {
        encrypted[i] ^= key[i % key.length()];
    }
    return encrypted;
}

std::string userService::decryptPassword(const std::string& encryptedPassword, const std::string& key) const
{
    // 这是简单的异或算法，解密与加密相同
    return encryptPassword(encryptedPassword, key);
}

User* userService::authenticate(const std::string& username, const std::string& password) const
{
    User* user = getUserByUsername(username);
    if (user && encryptPassword(password, user->getId()) == user->getPassword()) {
        currentUser = user;
        return user;
    }//先查找用户名，再比对加密后的密码对不对。加密密钥是用户id.
    return nullptr;
}