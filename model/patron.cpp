#include "patron.h"

Patron::Patron(const std::string &id, const std::string &username, const std::string &phone, const std::string &email,
               const std::string &password,
               int borrowLimit)
    : User(id, username, phone, email, password), borrowLimit(borrowLimit)
{
}

// Getters
int Patron::getBorrowLimit() const { return borrowLimit; }
// Setters
void Patron::setBorrowLimit(int limit) { borrowLimit = limit; }
// Display
void Patron::displayInfo() const {
    std::cout << "ID: " << id << ", Username: " << username << ", Phone: " << phone << ", Email: " << email << ", Borrow Limit: " << borrowLimit << std::endl;
}