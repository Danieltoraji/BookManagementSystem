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
    long toJulianDay() const; // 转为儒略日编号，用于日期差值计算

public:
    Date(const short &year, const short &month, const short &day);
    static Date fromString(const std::string &dateStr);
    static Date today(); // 获取当前系统日期

    // Getters
    short getYear() const;
    short getMonth() const;
    short getDay() const;

    // Setters
    void setYear(short value);
    void setMonth(short value);
    void setDay(short value);
    void setDate(short year, short month, short day);

    // Serialization
    std::string toString() const;

    // Operators
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>=(const Date &other) const;
    friend std::ostream& operator<<(std::ostream &os, const Date &date);
    Date operator+(const int days) const;
    int operator-(const Date &other) const; // 返回天数差 (*this - other)
};

#endif // DATE_H
