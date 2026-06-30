#include "loandao.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

LoanDao::LoanDao() {}

LoanDao& LoanDao::getInstance()
{
    static LoanDao instance;
    return instance;
}

std::string LoanDao::loanToString(const Loan& loan) const
{
    std::ostringstream stream;
    stream << loan.getId() << '|'
           << loan.getLibCode() << '|'
           << loan.getISBN() << '|'
           << loan.getUserId() << '|'
           << loan.getLoanDate() << '|'
           << loan.getDueDate() << '|'
           << loan.getReturnDate() << '|'
           << (loan.getIsReturned() ? '1' : '0');
    return stream.str();
}

Loan LoanDao::stringToLoan(const std::string& loanStr) const
{
    std::istringstream stream(loanStr);
    std::string field;
    std::vector<std::string> fields;
    while (std::getline(stream, field, '|')) {
        fields.push_back(field);
    }
    if (fields.size() < 8) {
        return Loan("", "", "", "", Date(0, 0, 0), Date(0, 0, 0), Date(0, 0, 0), false);
    }
    return Loan(fields[0], fields[1], fields[2], fields[3],
                Date::fromString(fields[4]), Date::fromString(fields[5]),
                Date::fromString(fields[6]), fields[7] == "1");
}

std::vector<Loan> LoanDao::loadLoansFromFile(const std::string& filename)
{
    std::vector<Loan> loans;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return loans;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        loans.push_back(stringToLoan(line));
    }
    return loans;
}

bool LoanDao::saveLoansToFile(const std::string& filename, const std::vector<Loan>& loans) const
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }
    for (const auto& loan : loans) {
        file << loanToString(loan) << '\n';
    }
    return true;
}