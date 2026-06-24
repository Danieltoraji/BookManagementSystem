#include "borrow.h"

Borrow::Borrow()
    : id(""), libCode(""), userId(""), borrowDate()
{
}

// Getters
std::string Borrow::getId() const { return id; }
std::string Borrow::getLibCode() const { return libCode; }
std::string Borrow::getUserId() const { return userId; }
Date Borrow::getBorrowDate() const { return borrowDate; }

// Setters
void Borrow::setId(const std::string &value) { id = value; }
void Borrow::setLibCode(const std::string &value) { libCode = value; }
void Borrow::setUserId(const std::string &value) { userId = value; }
void Borrow::setBorrowDate(const Date &value) { borrowDate = value; }