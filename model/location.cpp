#include "location.h"
#include <ostream>

Location::Location(std::string lib, short floor, short row, short unit, short level)
    : lib(lib), floor(floor), row(row), unit(unit), level(level)
{
}

// Getters
std::string Location::getLib() const { return lib; }
short Location::getFloor() const { return floor; }
short Location::getRow() const { return row; }
short Location::getUnit() const { return unit; }
short Location::getLevel() const { return level; }

// Setters
void Location::setLib(const std::string &value) { lib = value; }
void Location::setFloor(short value) { floor = value; }
void Location::setRow(short value) { row = value; }
void Location::setUnit(short value) { unit = value; }
void Location::setLevel(short value) { level = value; }

void Location::setLocation(const std::string &lib, short floor,
                           short row, short unit, short level)
{
    this->lib = lib;
    this->floor = floor;
    this->row = row;
    this->unit = unit;
    this->level = level;
}

std::ostream& operator<<(std::ostream& os, const Location &l){
    os << l.lib << "," << l.floor << "," << l.row << "," << l.unit << "," << l.level;
    return os;
}
