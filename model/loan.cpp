#include "loan.h"

Loan::Loan()
    : id(""), libCode(""), userId(""),
      loanDate(), dueDate(), returnDate()
{
}

// Getters
std::string Loan::getId() const { return id; }
std::string Loan::getLibCode() const { return libCode; }
std::string Loan::getUserId() const { return userId; }
Date Loan::getLoanDate() const { return loanDate; }
Date Loan::getDueDate() const { return dueDate; }
Date Loan::getReturnDate() const { return returnDate; }

// Setters
void Loan::setId(const std::string &value) { id = value; }
void Loan::setLibCode(const std::string &value) { libCode = value; }
void Loan::setUserId(const std::string &value) { userId = value; }
void Loan::setLoanDate(const Date &value) { loanDate = value; }
void Loan::setDueDate(const Date &value) { dueDate = value; }
void Loan::setReturnDate(const Date &value) { returnDate = value; }
