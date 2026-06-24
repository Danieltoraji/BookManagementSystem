#ifndef BORROW_H
#define BORROW_H
#include <string>
#include "date.h"

class Borrow
{
private:
    std::string id;
    std::string libCode;
    std::string userId;
    Date borrowDate;

public:
    Borrow();

    // Getters
    std::string getId() const;
    std::string getLibCode() const;
    std::string getUserId() const;
    Date getBorrowDate() const;

    // Setters
    void setId(const std::string &value);
    void setLibCode(const std::string &value);
    void setUserId(const std::string &value);
    void setBorrowDate(const Date &value);
};

#endif // BORROW_H