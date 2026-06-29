#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <string>
#include <vector>
#include "model/user.h"
#include "dao/userdao.h"

class userService
{
public:
    static userService& getInstance();
    userService(const userService&) = delete;
    userService& operator=(const userService&) = delete;
    userService(userService&&) = delete;
    userService& operator=(userService&&) = delete;

    // 强制存写
    bool readUsersFromFile();
    bool writeUsersToFile() const;

    // 用户管理
    std::vector<User*> getAllUsers() const;
    bool addUser(User* user);
    bool removeUser(const std::string& id);
    bool updateUser(const std::string& id, User* user);

    // 用户查询
    User* getUserById(const std::string& id) const;
    User* getUserByUsername(const std::string& username) const;

    // 用户验证
    User* authenticate(const std::string& username) const;

    // 数据主存
    std::vector<User*> users;
private:
    userService();
};

#endif // USERSERVICE_H
