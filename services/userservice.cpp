#include "userservice.h"
#include "model/admin.h"
#include "model/patron.h"
#include <algorithm>
#include <cstdio>

userService& userService::getInstance()
{
    static userService instance;
    return instance;
}

userService::userService()
{
    readUsersFromFile();
}

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
    // 这里采用了异或加密，key是用户的 id，保证每个用户的密码加密方式不同。
    // 然后为了防止.txt打不开，将结果转换为十六进制字符串存储。
    std::string hex;
    hex.reserve(password.length() * 2);
    for (size_t i = 0; i < password.length(); ++i) {
        unsigned char xored = static_cast<unsigned char>(password[i]) ^ static_cast<unsigned char>(key[i % key.length()]);
        char buf[3];
        std::snprintf(buf, sizeof(buf), "%02x", xored);
        hex += buf;
    }
    return hex;
}

std::string userService::decryptPassword(const std::string& encryptedPassword, const std::string& key) const
{
    // 从十六进制字符串还原 XOR 结果，再异或解密
    std::string decrypted;
    decrypted.reserve(encryptedPassword.length() / 2);
    for (size_t i = 0; i + 1 < encryptedPassword.length(); i += 2) {
        unsigned char xored = static_cast<unsigned char>(std::stoi(encryptedPassword.substr(i, 2), nullptr, 16));
        decrypted += static_cast<char>(xored ^ static_cast<unsigned char>(key[(i / 2) % key.length()]));
    }
    return decrypted;
}

User* userService::authenticate(const std::string& id, const std::string& password) const
{
    User* user = getUserById(id);
    if (user && encryptPassword(password, user->getId()) == user->getPassword()) {
        currentUser = user;
        return user;
    }//先查找用户名，再比对加密后的密码对不对。加密密钥是用户id.
    return nullptr;
}