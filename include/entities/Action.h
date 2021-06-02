#pragma once

#include <string>
#include <vector>

#include "entities/Sensor.h"
#include "numtypes.h"

struct Action {
    i64 id;
    i64 ordinal;
    std::string title;
    bool isRequired;
    bool isChecked;
    i64 researchId;
};
