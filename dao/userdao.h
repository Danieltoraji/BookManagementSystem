#ifndef USERDAO_H
#define USERDAO_H
#include <string>
#include <vector>
#include "model/user.h"

class UserDao
{
public:
    // 单例实现
    static UserDao& getInstance();
    UserDao(const UserDao&) = delete;
    UserDao& operator=(const UserDao&) = delete;
    UserDao(UserDao&&) = delete;
    UserDao& operator=(UserDao&&) = delete;

    // 文件更新
    std::vector<User*> loadUsersFromFile(const std::string& filename);
    bool saveUsersToFile(const std::string& filename, const std::vector<User*>& users) const;

private:
    UserDao() = default;

    // 序列化辅助函数
    std::string userToString(User* user) const;
    User* stringToUser(const std::string& userStr) const;
};

#endif // USERDAO_H

/*
用户文件设计格式：
每行一个用户信息，字段之间用|分隔，第一个字段为用户类型
Admin|id|username|phone|email|password
Patron|id|username|phone|email|password|borrowLimit
其中password为已加密的密文
Admin|admin|admin|12345678901|admin@library.com|<encrypted>
Patron|p001|张三|13800138000|zhangsan@example.com|<encrypted>|5
*/
