#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"

class Admin : public User
{
public:
    Admin();
    Admin(const std::string &id, const std::string &username, const std::string &phone,
          const std::string &email, const std::string &password);
};

#endif // ADMIN_H
