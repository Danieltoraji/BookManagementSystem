#ifndef LOANSERVICE_H
#define LOANSERVICE_H
#include <string>
#include <vector>
#include <map>
#include "model/loan.h"

class loanService
{
public:
    // 单例实现
    static loanService& getInstance();
    loanService(const loanService&) = delete;
    loanService& operator=(const loanService&) = delete;
    loanService(loanService&&) = delete;
    loanService& operator=(loanService&&) = delete;

    // 强制存写
    bool readLoansFromFile();
    bool writeLoansToFile() const;

    // 借阅服务
    bool borrowBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage);
    bool returnBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage);
    bool renewBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage);

    // 批量归还（用于副本注销/删除、图书删除时的级联处理）
    bool returnBookByLibCode(const std::string& libCode, std::string& errorMessage);
    bool returnBooksByISBN(const std::string& ISBN, std::string& errorMessage);

    // 借阅记录查询
    std::vector<Loan> getBorrowingBooksByUser(const std::string& userId);
    std::vector<Loan> getBorrowHistoryByUser(const std::string& userId);
    std::vector<Loan> getBorrowHistoryByISBN(const std::string& ISBN);
    std::vector<Loan> getBorrowHistoryByLibCode(const std::string& libCode);
    std::vector<Loan> getAllCurrentBorrowing();

    //统计信息
    int getTotalBorrowedBooks() const;//总借阅量
    int getTotalBorrowingBooks() const;//当前出借数
    std::map<std::string, int> getMostBorrowedBooks(int topN) const;//最受欢迎图书
    std::map<std::string, int> getMostActiveUsers(int topN) const;//最活跃用户
    std::map<std::string, int> getTotalBorrowVSMonth() const;//每月借阅量
    std::map<std::string, int> getUserBorrowVSMonth(const std::string& userId) const;//每月用户借阅量
    
    // 数据主存
    std::vector<Loan> loans;


private:
    loanService();
};

#endif // LOANSERVICE_H
