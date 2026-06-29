#include "userdao.h"
#include "model/admin.h"
#include "model/patron.h"
#include <algorithm>
#include <fstream>
#include <sstream>

UserDao& UserDao::getInstance()
{
    static UserDao instance;
    return instance;
}

std::string UserDao::userToString(User* user) const
{
    std::ostringstream stream;
    // 通过 dynamic_cast 判断用户类型
    if (dynamic_cast<Admin*>(user)) {
        stream << "Admin|"
               << user->getId() << '|'
               << user->getUsername() << '|'
               << user->getPhone() << '|'
               << user->getEmail();
    } else if (dynamic_cast<Patron*>(user)) {
        Patron* patron = dynamic_cast<Patron*>(user);
        stream << "Patron|"
               << patron->getId() << '|'
               << patron->getUsername() << '|'
               << patron->getPhone() << '|'
               << patron->getEmail() << '|'
               << patron->getBorrowLimit() << '|';
        bool first = true;
        for (const auto& book : patron->getCurrentBorrowBooks()) {
            if (!first) stream << ',';
            stream << book;
            first = false;
        }
    }
    return stream.str();
}

User* UserDao::stringToUser(const std::string& userStr) const
{
    std::istringstream stream(userStr);
    std::string field;
    std::vector<std::string> fields;
    while (std::getline(stream, field, '|')) {
        fields.push_back(field);
    }
    if (fields.empty()) return nullptr;

    if (fields[0] == "Admin" && fields.size() >= 5) {
        return new Admin();
        // Admin 使用默认构造，字段信息暂不设置（Admin 无额外属性）
    } else if (fields[0] == "Patron" && fields.size() >= 7) {
        std::list<std::string> borrowBooks;
        if (!fields[6].empty()) {
            std::istringstream bookStream(fields[6]);
            std::string bookCode;
            while (std::getline(bookStream, bookCode, ',')) {
                borrowBooks.push_back(bookCode);
            }
        }
        return new Patron(fields[1], fields[2], fields[3], fields[4],
                          std::stoi(fields[5]), borrowBooks);
    }
    return nullptr;
}

std::vector<User*> UserDao::loadUsersFromFile(const std::string& filename)
{
    std::vector<User*> users;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        User* user = stringToUser(line);
        if (user) {
            users.push_back(user);
        }
    }
    return users;
}

bool UserDao::saveUsersToFile(const std::string& filename, const std::vector<User*>& users) const
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    for (User* user : users) {
        file << userToString(user) << '\n';
    }
    return true;
}
