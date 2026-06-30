#ifndef LOANDAO_H
#define LOANDAO_H
#include <string>
#include <vector>
#include "model/loan.h"
class LoanDao
{
public:
    // 单例实现
    static LoanDao& getInstance();
    LoanDao(const LoanDao&) = delete;
    LoanDao& operator=(const LoanDao&) = delete;
    LoanDao(LoanDao&&) = delete;
    LoanDao& operator=(LoanDao&&) = delete;

    // 文件更新
    std::vector<Loan> loadLoansFromFile(const std::string& filename);
    bool saveLoansToFile(const std::string& filename, const std::vector<Loan>& loans) const;

private:
    LoanDao();

    // 序列化辅助函数
    std::string loanToString(const Loan& loan) const;
    Loan stringToLoan(const std::string& loanStr) const;
};

#endif // LOANDAO_H

/*
借阅记录文件设计格式：
每行一个借阅信息，字段之间用|分隔
id|libCode|ISBN|userId|loanDate|dueDate|returnDate|isReturned
20260600001|LIB001|978-7-121-12345-6|p001|2023-06-01|2023-06-15|2023-06-10|1
*/