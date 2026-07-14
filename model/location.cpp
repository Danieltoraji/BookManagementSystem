#include "location.h"
#include <ostream>
#include <sstream>
#include <vector>


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

void Location::setLocation(const std::string &locFields){
    std::vector<std::string> fields;
    std::stringstream ss(locFields);
    std::string field;
    while (std::getline(ss, field, '-')) {
        fields.push_back(field);
    }
    if (fields.size() >= 5) {
        lib = fields[0];
        floor = std::stoi(fields[1]);
        row = std::stoi(fields[2]);
        unit = std::stoi(fields[3]);
        level = std::stoi(fields[4]);
    }
}

std::ostream& operator<<(std::ostream& os, const Location &l){
    os << l.lib << "," << l.floor << "层" << l.row << "排" << l.unit << "架" << l.level << "层";
    return os;
}

std::string Location::toString() const {
    return lib + "-" + std::to_string(floor) + "-"
           + std::to_string(row) + "-" + std::to_string(unit) + "-"
           + std::to_string(level);
}
