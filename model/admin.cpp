#include "admin.h"
#include <iostream>

Admin::Admin() {}

Admin::Admin(const std::string &id, const std::string &username, const std::string &phone,
             const std::string &email, const std::string &password)
    : User(id, username, phone, email, password)
{
}

void Admin::displayInfo() const {
    std::cout << "ID: " << id << ", Username: " << username << ", Phone: " << phone << ", Email: " << email << " (Admin)" << std::endl;
}
