#ifndef FINE_H
#define FINE_H
#include <string>

class Fine
{
private:
    std::string id;
    std::string userId;
    double amount;
    bool isPaid;

public:
    Fine(std::string id, std::string userId, double amount, bool isPaid = false);

    // Getters
    std::string getId() const;
    std::string getUserId() const;
    double getAmount() const;
    bool getisPaid() const;

    // Setters
    void setId(const std::string &value);
    void setUserId(const std::string &value);
    void setAmount(double value);
    void setisPaid(bool value);
};

#endif // FINE_H
