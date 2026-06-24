#ifndef DATE_H
#define DATE_H

class Date
{
private:
    short year;
    short month;
    short day;

public:
    Date();

    // Getters
    short getYear() const;
    short getMonth() const;
    short getDay() const;

    // Setters
    void setYear(short value);
    void setMonth(short value);
    void setDay(short value);
    void setDate(short year, short month, short day);
};

#endif // DATE_H
