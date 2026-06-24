#include "user.h"

User::User()
    : id(""), username(""), phone(""), email("")
{
}

// Getters
std::string User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPhone() const { return phone; }
std::string User::getEmail() const { return email; }

// Setters
void User::setId(const std::string &value) { id = value; }
void User::setUsername(const std::string &value) { username = value; }
void User::setPhone(const std::string &value) { phone = value; }
void User::setEmail(const std::string &value) { email = value; }
