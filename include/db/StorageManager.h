#pragma once

#include <string>
#include <unordered_map>

#include "db/storage.h"

class StorageManager {
    static thread_local std::unordered_map<std::string, Storage> cache;

public:
    static Storage& get(const std::string& path = "research.db");

    StorageManager() = delete;
};
