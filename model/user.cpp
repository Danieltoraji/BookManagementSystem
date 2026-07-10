#include "user.h"

User::User(std::string id, std::string username, std::string phone, std::string email, std::string password)
    : id(id), username(username), phone(phone), email(email), password(password)
{
}

// Getters
std::string User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPhone() const { return phone; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }

// Setters
void User::setId(const std::string &value) { id = value; }
void User::setUsername(const std::string &value) { username = value; }
void User::setPhone(const std::string &value) { phone = value; }
void User::setEmail(const std::string &value) { email = value; }
void User::setPassword(const std::string &value) { password = value; }
