#ifndef USER_H
#define USER_H

#include <string>

class User
{
protected:
    std::string id;
    std::string username;
    std::string phone;
    std::string email;
    std::string password; // 当然是加密后的！

public:
    User(std::string id = "", std::string username = "", std::string phone = "", std::string email = "", std::string password = "");
    virtual ~User() = default;

    // Getters
    std::string getId() const;
    std::string getUsername() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Setters
    void setId(const std::string &value);
    void setUsername(const std::string &value);
    void setPhone(const std::string &value);
    void setEmail(const std::string &value);
    void setPassword(const std::string &value);
}; 

#endif // USER_H
