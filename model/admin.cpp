#include "admin.h"

Admin::Admin() {}

Admin::Admin(const std::string &id, const std::string &username, const std::string &phone,
             const std::string &email, const std::string &password)
    : User(id, username, phone, email, password)
{
}
