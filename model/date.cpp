#include "date.h"

Date::Date(const short &year, const short &month, const short &day)
    : year(year), month(month), day(day)
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

// Operators
bool Date::operator==(const Date &other) const
{
    return year == other.year && month == other.month && day == other.day;
}
bool Date::operator!=(const Date &other) const
{
    return !(*this == other);
}
bool Date::operator<(const Date &other) const
{
    if (year != other.year)
        return year < other.year;
    if (month != other.month)
        return month < other.month;
    return day < other.day;
}
bool Date::operator>(const Date &other) const
{
    return other < *this;
}
Date Date::operator+(const int days) const
{
    //handle all date addition logic here, considering month/year overflow,simplification not allowed
    Date newDate = *this;
    newDate.day += days;
    bool flag = false;
    while(!flag){
        flag = true;
        if(newDate.day > dayInMonth(newDate.year, newDate.month)){
            newDate.day -= dayInMonth(newDate.year, newDate.month);
            newDate.month++;
            flag = false;
        }
        if(newDate.month > 12){
            newDate.month -= 12;
            newDate.year++;
            flag = false;
        }
    }
    return newDate;
}

//Assistant functions
bool Date::isLeapYear(const short &year) const{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
short Date::dayInMonth(const short &year, const short &month) const{
    switch(month){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // Invalid month
    }
}