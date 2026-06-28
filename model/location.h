#ifndef LOCATION_H
#define LOCATION_H
#include <string>

class Location
{
private:
    std::string lib;
    short floor;
    short row;
    short unit;
    short level;

public:
    Location(std::string lib = "", short floor = 0, short row = 0, short unit = 0, short level = 0);

    // Getters
    std::string getLib() const;
    short getFloor() const;
    short getRow() const;
    short getUnit() const;
    short getLevel() const;

    // Setters
    void setLib(const std::string &value);
    void setFloor(short value);
    void setRow(short value);
    void setUnit(short value);
    void setLevel(short value);
    void setLocation(const std::string &lib, short floor,
                     short row, short unit, short level);

    // operators
    friend std::ostream& operator<<(std::ostream& os, const Location& l);
};
#endif // LOCATION_H
