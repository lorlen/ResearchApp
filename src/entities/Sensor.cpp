#include "entities/Sensor.h"

#include <sstream>

std::string Sensor::description() const {
    std::ostringstream stream;
    stream << label << " (" << type << "; " << unit << ")";
    return stream.str();
}