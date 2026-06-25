#include "bookcopy.h"

BookCopy::BookCopy(const std::string &isbn, const std::string &libCode, const Location &location, const bookstatus &status)
    : ISBN(isbn), libCode(libCode), bookLocation(location), status(status)
{
}

// Getters
std::string BookCopy::getISBN() const { return ISBN; }
std::string BookCopy::getLibCode() const { return libCode; }
Location BookCopy::getBookLocation() const { return bookLocation; }
bookstatus BookCopy::getStatus() const { return status; }

// Setters
void BookCopy::setISBN(const std::string &value) { ISBN = value; }
void BookCopy::setLibCode(const std::string &value) { libCode = value; }
void BookCopy::setBookLocation(const Location &loc) { bookLocation = loc; }
void BookCopy::setStatus(const bookstatus &sta) { status = sta; }