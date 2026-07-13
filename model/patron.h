#ifndef PATRON_H
#define PATRON_H
#include "user.h"
#include <list>
#include <string>
#include <iostream>

class Patron : public User
{
private:
    int borrowLimit;

public:
    Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
        const std::string &password,
        int borrowLimit = 5);

    // Getters
    int getBorrowLimit() const;

    // Setters
    void setBorrowLimit(int limit);

    // Display
    void displayInfo() const override;
};

#endif // PATRON_H
