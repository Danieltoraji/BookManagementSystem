#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <string>
#include <vector>
#include "model/user.h"
#include "dao/userdao.h"

/*密码加密约定：
明文：add和update函数的形参。
加密：add和update函数内部。加密方法：以用户ID为密钥的异或加密。
密文：构造函数的形参，文件的存储，主存的数据。
*/
class UserService
{
public:
    static UserService& getInstance();
    UserService(const UserService&) = delete;
    UserService& operator=(const UserService&) = delete;
    UserService(UserService&&) = delete;
    UserService& operator=(UserService&&) = delete;

    // 强制存写
    bool readUsersFromFile();
    bool writeUsersToFile() const;

    // 用户管理
    std::vector<User*> getAllUsers() const;
    bool addPatron(const std::string& id, const std::string& username, const std::string& phone,
                   const std::string& email, const std::string& plainPassword, int borrowLimit = 5);
    bool addAdmin(const std::string& id, const std::string& username, const std::string& phone,
                  const std::string& email, const std::string& plainPassword);
    bool removeUser(const std::string& id);
    bool updatePatron(const std::string& id, const std::string& username, const std::string& phone,
                      const std::string& email, int borrowLimit = 5);
    bool updatePatronPassword(const std::string& id, const std::string& plainPassword);
    bool updateAdmin(const std::string& id, const std::string& username, const std::string& phone,
                     const std::string& email);
    bool updateAdminPassword(const std::string& id, const std::string& plainPassword);

    // 用户查询

    User* getUserById(const std::string& id) const;
    User* getUserByUsername(const std::string& username) const;

    // 用户验证
    User* authenticate(const std::string& id, const std::string& password) const;
    std::string encryptPassword(const std::string& password, const std::string& key) const;
    std::string decryptPassword(const std::string& encryptedPassword, const std::string& key) const;
    User* getCurrentUser() const;
    
    // 数据主存
    std::vector<User*> users;
    mutable User* currentUser = nullptr; // 当前登录用户
private:
    UserService();
};

#endif // USERSERVICE_H
