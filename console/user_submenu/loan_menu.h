#ifndef LOAN_MENU_H
#define LOAN_MENU_H
#include "../menu_base.h"
#include "services/loanservice.h"
#include "services/bookservice.h"
#include "services/bookcopyservice.h"
#include "services/userservice.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

class LoanMenu : public MenuBase
{
public:
    void show();
private:
    void displayRecommendations();
    void borrowBook();
    void renewBook();
    void returnBook();
    void displayCurrentLoans();
    void displayUserLoanHistory();
    void displayBookLoanHistory();

    void printLoans(const std::vector<Loan>& loans);
};

#endif // LOAN_MENU_H