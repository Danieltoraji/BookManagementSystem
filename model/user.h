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

public:
    User(std::string id = "", std::string username = "", std::string phone = "", std::string email = "");
    virtual ~User() = default;

    // Getters
    std::string getId() const;
    std::string getUsername() const;
    std::string getPhone() const;
    std::string getEmail() const;

    // Setters
    void setId(const std::string &value);
    void setUsername(const std::string &value);
    void setPhone(const std::string &value);
    void setEmail(const std::string &value);
};

#endif // USER_H
