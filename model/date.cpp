#include "date.h"

Date::Date()
    : year(0), month(0), day(0)
{
}

// Getters
short Date::getYear() const { return year; }
short Date::getMonth() const { return month; }
short Date::getDay() const { return day; }

// Setters
void Date::setYear(short value) { year = value; }
void Date::setMonth(short value) { month = value; }
void Date::setDay(short value) { day = value; }
void Date::setDate(short year, short month, short day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}
