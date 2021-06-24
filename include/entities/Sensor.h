#pragma once

#include <string>

#include "numtypes.h"

struct Sensor {
    i64 id;
    std::string label;
    std::string type;
    std::string unit;

    [[nodiscard]] std::string description() const;
};
