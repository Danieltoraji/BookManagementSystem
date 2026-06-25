#include "fine.h"

Fine::Fine(std::string id, std::string userId, double amount, bool isPaid):
    id(id), userId(userId), amount(amount), isPaid(isPaid)
{
}

// Getters
std::string Fine::getId() const { return id; }
std::string Fine::getUserId() const { return userId; }
double Fine::getAmount() const { return amount; }
bool Fine::getisPaid() const { return isPaid; }
// Setters
void Fine::setId(const std::string &value) { id = value; }
void Fine::setUserId(const std::string &value) { userId = value; }
void Fine::setAmount(double value) { amount = value; }
void Fine::setisPaid(bool value) { isPaid = value; }