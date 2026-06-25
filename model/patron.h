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
    std::list<std::string> currentReservations;

public:
    Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
        int borrowLimit = 5, const std::list<std::string> &currentBorrowBooks = {},
        const std::list<std::string> &unfinishedFineList = {}, const std::list<std::string> &currentReservations = {});

    // Getters
    int getBorrowLimit() const;
    std::list<std::string> getCurrentBorrowBooks() const;
    std::list<std::string> getUnfinishedFineList() const;
    std::list<std::string> getCurrentReservations() const;

    // Setters
    void setBorrowLimit(int limit);
    void setCurrentBorrowBooks(const std::list<std::string> &books);
    void setUnfinishedFineList(const std::list<std::string> &fines);
    void setCurrentReservations(const std::list<std::string> &reservations);

    // Business methods
    std::string displayInfo();
    std::list<std::string> getBorrowBooks();
    void payFine();
    void addFine();
    bool canBorrow();
};

#endif // PATRON_H
