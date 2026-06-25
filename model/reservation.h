#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
#include "date.h"

class Reservation
{
private:
    std::string id;
    std::string libCode;
    std::string ISBN;
    std::string userId;
    Date reservationDate;

public:
    Reservation(const std::string &id, const std::string &libCode, const std::string &ISBN, const std::string &userId, const Date &reservationDate);

    // Getters
    std::string getId() const;
    std::string getLibCode() const;
    std::string getISBN() const;
    std::string getUserId() const;
    Date getReservationDate() const;

    // Setters
    void setId(const std::string &value);
    void setLibCode(const std::string &value);
    void setISBN(const std::string &value);
    void setUserId(const std::string &value);
    void setReservationDate(const Date &value);
};

#endif // RESERVATION_H
