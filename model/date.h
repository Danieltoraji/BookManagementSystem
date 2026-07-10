#ifndef DATE_H
#define DATE_H
#include <string>

class Date
{
private:
    short year;
    short month;
    short day;
    bool isLeapYear(const short &year) const;
    short dayInMonth(const short &year, const short &month) const;

public:
    Date(const short &year, const short &month, const short &day);
    static Date fromString(const std::string &dateStr);
    // Getters
    short getYear() const;
    short getMonth() const;
    short getDay() const;

    // Setters
    void setYear(short value);
    void setMonth(short value);
    void setDay(short value);
    void setDate(short year, short month, short day);

    // Operators
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator>(const Date &other) const;
    friend std::ostream& operator<<(std::ostream &os, const Date &date);
    Date operator+(const int days) const;
};

#endif // DATE_H
