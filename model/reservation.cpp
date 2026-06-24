#include "reservation.h"

Reservation::Reservation()
    : id(""), libCode(""), userId(""), reservationDate()
{
}

// Getters
std::string Reservation::getId() const { return id; }
std::string Reservation::getLibCode() const { return libCode; }
std::string Reservation::getUserId() const { return userId; }
Date Reservation::getReservationDate() const { return reservationDate; }

// Setters
void Reservation::setId(const std::string &value) { id = value; }
void Reservation::setLibCode(const std::string &value) { libCode = value; }
void Reservation::setUserId(const std::string &value) { userId = value; }
void Reservation::setReservationDate(const Date &value) { reservationDate = value; }
