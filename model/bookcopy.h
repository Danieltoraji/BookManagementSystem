#ifndef BOOKCOPY_H
#define BOOKCOPY_H
#include <string>
#include "location.h"

enum bookstatus{available,borrowed,reserved,cancelled};
class BookCopy
{
private:
    std::string ISBN;
    std::string libCode;
    Location bookLocation;
    bookstatus status;

public:
    BookCopy(const std::string &isbn = "", const std::string &libCode = "", const Location &location = Location(), const bookstatus &status = available);

    // Getters
    std::string getISBN() const;
    std::string getLibCode() const;
    Location getBookLocation() const;
    bookstatus getStatus() const;

    // Setters
    void setISBN(const std::string &value);
    void setLibCode(const std::string &value);
    void setBookLocation(const Location &loc);
    void setStatus(const bookstatus &sta);
};

#endif // BOOKCOPY_H
