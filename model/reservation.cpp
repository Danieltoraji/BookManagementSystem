#include "reservation.h"

Reservation::Reservation(const std::string &id, const std::string &libCode, const std::string &ISBN, const std::string &userId, const Date &reservationDate)
    : id(id), libCode(libCode), ISBN(ISBN), userId(userId), reservationDate(reservationDate)
{
}

// Getters
std::string Reservation::getId() const { return id; }
std::string Reservation::getLibCode() const { return libCode; }
std::string Reservation::getISBN() const { return ISBN; }
std::string Reservation::getUserId() const { return userId; }
Date Reservation::getReservationDate() const { return reservationDate; }

// Setters
void Reservation::setId(const std::string &value) { id = value; }
void Reservation::setLibCode(const std::string &value) { libCode = value; }
void Reservation::setISBN(const std::string &value) { ISBN = value; }
void Reservation::setUserId(const std::string &value) { userId = value; }
void Reservation::setReservationDate(const Date &value) { reservationDate = value; }
