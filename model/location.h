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
    Location(std::string lib, short floor, short row, short unit, short level);

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

    // Convenience
    void setLocation(const std::string &lib, short floor,
                     short row, short unit, short level);
};

#endif // LOCATION_H
