#pragma once

#include <optional>
#include <string>
#include <vector>

#include "numtypes.h"
#include "entities/Action.h"
#include "entities/User.h"
#include "utils/Date.h"

struct Research {
    i64 id;
    std::string title;
    Date startDate;
    Date endDate;
    std::string info;
    std::optional<i64> authorId;
};
