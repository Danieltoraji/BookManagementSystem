#include "patron.h"

Patron::Patron()
    : User(), borrowLimit(0), currentBorrowBooks(), unfinishedFineList()
{
}

// Getters
int Patron::getBorrowLimit() const { return borrowLimit; }
std::list<std::string> Patron::getCurrentBorrowBooks() const { return currentBorrowBooks; }
std::list<std::string> Patron::getUnfinishedFineList() const { return unfinishedFineList; }

// Setters
void Patron::setBorrowLimit(int limit) { borrowLimit = limit; }
void Patron::setCurrentBorrowBooks(const std::list<std::string> &books) { currentBorrowBooks = books; }
void Patron::setUnfinishedFineList(const std::list<std::string> &fines) { unfinishedFineList = fines; }
