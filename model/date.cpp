#include "date.h"
#include <string>
#include <sstream>
#include <ctime>


Date::Date(const short &year, const short &month, const short &day)
    : year(year), month(month), day(day)
{
}
Date Date::fromString(const std::string &dateStr)
{
    std::istringstream iss(dateStr);
    short year, month, day;
    char dash1, dash2;
    iss >> year >> dash1 >> month >> dash2 >> day;
    return Date(year, month, day);
}

Date Date::today()
{
    std::time_t t = std::time(nullptr);
    std::tm now;
#ifdef _MSC_VER
    localtime_s(&now, &t);
#else
    now = *std::localtime(&t);
#endif
    return Date(static_cast<short>(now.tm_year + 1900),
                static_cast<short>(now.tm_mon + 1),
                static_cast<short>(now.tm_mday));
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
std::ostream& operator<<(std::ostream &os, const Date &date)
{
    os << date.year << '-' << (date.month < 10 ? "0" : "") << date.month
       << '-' << (date.day < 10 ? "0" : "") << date.day;
    return os;
}

std::string Date::toString() const
{
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

std::string Date::toYearMonthString() const
{
    std::ostringstream oss;
    oss << year << '-' << (month < 10 ? "0" : "") << month;
    return oss.str();
}

bool Date::operator<=(const Date &other) const
{
    return !(*this > other);
}
bool Date::operator>=(const Date &other) const
{
    return !(*this < other);
}

int Date::operator-(const Date &other) const
{
    return static_cast<int>(this->toJulianDay() - other.toJulianDay());
}

long Date::toJulianDay() const
{
    long a = (14 - month) / 12;
    long y = year + 4800 - a;
    long m = month + 12 * a - 3;
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
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