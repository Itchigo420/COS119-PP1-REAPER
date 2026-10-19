#pragma once

#include "TaskManager.h"

#include <string>

enum class LoadResult {
    Loaded,
    NotFound,
    Error
};

class TaskStorage {
public:
    // Files use a versioned, human-readable format with escaped task titles.
    static LoadResult load(const std::string& path, TaskManager& manager, std::string& message);
    static bool save(const std::string& path, const TaskManager& manager, std::string& message);
};
