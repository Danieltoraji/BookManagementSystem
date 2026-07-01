#include "loanservice.h"
#include <algorithm>
#include "bookservice.h"
#include "userservice.h"
#include "bookcopyservice.h"
#include "dao/loandao.h"


loanService::loanService() {}

 loanService& loanService::getInstance(){
    static loanService instance;
    return instance;
}

bool loanService::readLoansFromFile() {
    loans = LoanDao::getInstance().loadLoansFromFile("data/loans.txt");
    return !loans.empty();
}

bool loanService::writeLoansToFile() const {
    return LoanDao::getInstance().saveLoansToFile("data/loans.txt", loans);
}

bool loanService::borrowBook(const std::string& userId, const std::string& ISBN, const std::string& libCode, std::string& errorMessage) {
    //检查
    //0.书的信息和用户的信息对不对？
    //1.该用户是否已借阅该书？
    //2.该书是否被别人借阅/无效？
    //3.该用户的在借数量达到上限没有？
    //4.该用户是否有未归还的逾期书籍？
    //操作
    //1.更改用户、图书各状态
    //2.添加借阅记录
}