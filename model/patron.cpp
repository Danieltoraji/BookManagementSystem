#include "patron.h"

Patron::Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
               int borrowLimit, const std::list<std::string> &currentBorrowBooks, const std::list<std::string> &unfinishedFineList, const std::list<std::string> &currentReservations)
    : User(id, username, phone, email), borrowLimit(borrowLimit), currentBorrowBooks(currentBorrowBooks), unfinishedFineList(unfinishedFineList), currentReservations(currentReservations)
{
}

// Getters
int Patron::getBorrowLimit() const { return borrowLimit; }
std::list<std::string> Patron::getCurrentBorrowBooks() const { return currentBorrowBooks; }
std::list<std::string> Patron::getUnfinishedFineList() const { return unfinishedFineList; }
std::list<std::string> Patron::getCurrentReservations() const { return currentReservations; }
// Setters
void Patron::setBorrowLimit(int limit) { borrowLimit = limit; }
void Patron::setCurrentBorrowBooks(const std::list<std::string> &books) { currentBorrowBooks = books; }
void Patron::setUnfinishedFineList(const std::list<std::string> &fines) { unfinishedFineList = fines; }
void Patron::setCurrentReservations(const std::list<std::string> &reservations) { currentReservations = reservations; }