#ifndef PATRON_H
#define PATRON_H
#include "user.h"
#include <list>
#include <string>

class Patron : public User
{
private:
    int borrowLimit;
    std::list<std::string> currentBorrowBooks;

public:
    Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
        const std::string &password,
        int borrowLimit = 5, const std::list<std::string> &currentBorrowBooks = {});

    // Getters
    int getBorrowLimit() const;
    std::list<std::string> getCurrentBorrowBooks() const;
    std::list<std::string>& getCurrentBorrowBooks();

    // Setters
    void setBorrowLimit(int limit);
    void setCurrentBorrowBooks(const std::list<std::string> &books);

};

#endif // PATRON_H
