#include "db/StorageManager.h"

thread_local std::unordered_map<std::string, Storage> StorageManager::cache;

Storage& StorageManager::get(const std::string& path) {
    auto iter = cache.find(path);

    if (iter != cache.end()) {
        return iter->second;
    }

    cache.emplace(path, createStorage(path));
    return cache.at(path);
}
