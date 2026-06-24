#include "bookcopy.h"

BookCopy::BookCopy()
    : ISBN(""), libCode(""), bookLocation()
{
}

// Getters
std::string BookCopy::getISBN() const { return ISBN; }
std::string BookCopy::getLibCode() const { return libCode; }
Location BookCopy::getBookLocation() const { return bookLocation; }

// Setters
void BookCopy::setISBN(const std::string &value) { ISBN = value; }
void BookCopy::setLibCode(const std::string &value) { libCode = value; }
void BookCopy::setBookLocation(const Location &loc) { bookLocation = loc; }
