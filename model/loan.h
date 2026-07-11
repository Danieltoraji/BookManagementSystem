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
    Date loanDate;//借书
    Date dueDate;//到期
    Date returnDate;//还书
    bool isReturned; // 判断是否已归还

public:
    Loan(std::string id, std::string libCode, std::string ISBN, std::string userId,
         Date loanDate, Date dueDate, Date returnDate, bool isReturned = false);

    // Getters
    std::string getId() const;
    std::string getLibCode() const;
    std::string getUserId() const;
    std::string getISBN() const;
    Date getLoanDate() const;
    Date getDueDate() const;
    Date getReturnDate() const;
    bool getIsReturned() const;

    // Setters
    void setId(const std::string &value);
    void setLibCode(const std::string &value);
    void setUserId(const std::string &value);
    void setISBN(const std::string &value);
    void setLoanDate(const Date &value);
    void setDueDate(const Date &value);
    void setReturnDate(const Date &value);
    void setIsReturned(bool value);

    // 时间相关方法
    bool isOverdue() const;       // 是否逾期（未归还且当前日期超过应还日期）
    int getOverdueDays() const;   // 逾期天数（未逾期或已归还返回0）
};

#endif // LOAN_H
