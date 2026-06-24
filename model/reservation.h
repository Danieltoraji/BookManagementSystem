#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
#include "date.h"

class Reservation
{
private:
    std::string id;
    std::string libCode;
    std::string userId;
    Date reservationDate;

public:
    Reservation();

    // Getters
    std::string getId() const;
    std::string getLibCode() const;
    std::string getUserId() const;
    Date getReservationDate() const;

    // Setters
    void setId(const std::string &value);
    void setLibCode(const std::string &value);
    void setUserId(const std::string &value);
    void setReservationDate(const Date &value);
};

#endif // RESERVATION_H
