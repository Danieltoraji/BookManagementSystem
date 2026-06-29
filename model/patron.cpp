#include "patron.h"

Patron::Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
               int borrowLimit, const std::list<std::string> &currentBorrowBooks)
    : User(id, username, phone, email), borrowLimit(borrowLimit), currentBorrowBooks(currentBorrowBooks)
{
}

// Getters
int Patron::getBorrowLimit() const { return borrowLimit; }
std::list<std::string> Patron::getCurrentBorrowBooks() const { return currentBorrowBooks; }
// Setters
void Patron::setBorrowLimit(int limit) { borrowLimit = limit; }
void Patron::setCurrentBorrowBooks(const std::list<std::string> &books) { currentBorrowBooks = books; }