#ifndef LOAN_H
#define LOAN_H
#include <string>
#include "date.h"

class Loan
{
private:
    std::string id;
    std::string libCode;
    std::string ISBN;
    std::string userId;
    Date loanDate;
    Date dueDate;
    Date returnDate;

public:
    Loan(std::string id, std::string libCode, std::string ISBN, std::string userId,
         Date loanDate, Date dueDate, Date returnDate);

    // Getters
    std::string getId() const;
    std::string getLibCode() const;
    std::string getUserId() const;
    std::string getISBN() const;
    Date getLoanDate() const;
    Date getDueDate() const;
    Date getReturnDate() const;

    // Setters
    void setId(const std::string &value);
    void setLibCode(const std::string &value);
    void setUserId(const std::string &value);
    void setISBN(const std::string &value);
    void setLoanDate(const Date &value);
    void setDueDate(const Date &value);
    void setReturnDate(const Date &value);
};

#endif // LOAN_H
