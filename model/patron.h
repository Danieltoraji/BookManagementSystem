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
    std::list<std::string> unfinishedFineList;

public:
    Patron();

    // Getters
    int getBorrowLimit() const;
    std::list<std::string> getCurrentBorrowBooks() const;
    std::list<std::string> getUnfinishedFineList() const;

    // Setters
    void setBorrowLimit(int limit);
    void setCurrentBorrowBooks(const std::list<std::string> &books);
    void setUnfinishedFineList(const std::list<std::string> &fines);

    // Business methods
    std::string displayInfo();
    std::list<std::string> getBorrowBooks();
    void payFine();
    void addFine();
    bool canBorrow();
};

#endif // PATRON_H
