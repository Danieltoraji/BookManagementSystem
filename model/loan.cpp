#include "loan.h"

Loan::Loan(std::string id, std::string libCode, std::string ISBN, std::string userId,
           Date loanDate, Date dueDate, Date returnDate, bool isReturned):
    id(id), libCode(libCode), ISBN(ISBN), userId(userId),
    loanDate(loanDate), dueDate(dueDate), returnDate(returnDate), isReturned(isReturned)
{
}

// Getters
std::string Loan::getId() const { return id; }
std::string Loan::getLibCode() const { return libCode; }
std::string Loan::getUserId() const { return userId; }
std::string Loan::getISBN() const { return ISBN; }
Date Loan::getLoanDate() const { return loanDate; }
Date Loan::getDueDate() const { return dueDate; }
Date Loan::getReturnDate() const { return returnDate; }
bool Loan::getIsReturned() const { return isReturned; }

// Setters
void Loan::setId(const std::string &value) { id = value; }
void Loan::setLibCode(const std::string &value) { libCode = value; }
void Loan::setUserId(const std::string &value) { userId = value; }
void Loan::setISBN(const std::string &value) { ISBN = value; }
void Loan::setLoanDate(const Date &value) { loanDate = value; }
void Loan::setDueDate(const Date &value) { dueDate = value; }
void Loan::setReturnDate(const Date &value) { returnDate = value; }
void Loan::setIsReturned(bool value) { isReturned = value; }
