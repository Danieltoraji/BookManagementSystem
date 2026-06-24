#include "fine.h"

Fine::Fine()
    : id(""), userId(""), amount(0.0)
{
}

// Getters
std::string Fine::getId() const { return id; }
std::string Fine::getUserId() const { return userId; }
double Fine::getAmount() const { return amount; }

// Setters
void Fine::setId(const std::string &value) { id = value; }
void Fine::setUserId(const std::string &value) { userId = value; }
void Fine::setAmount(double value) { amount = value; }
