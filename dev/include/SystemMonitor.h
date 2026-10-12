#pragma once

#include <cstdint>
#include <string>

struct SystemSnapshot {
    unsigned int logicalProcessorCount = 0;
    std::uint64_t totalMemoryBytes = 0;
    std::uint64_t availableMemoryBytes = 0;

    double memoryUsedPercent() const;
};

class SystemMonitor {
public:
    SystemSnapshot capture() const;
    static std::string formatBytes(std::uint64_t bytes);
};
