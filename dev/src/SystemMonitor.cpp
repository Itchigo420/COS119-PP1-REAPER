#include "SystemMonitor.h"

#include <iomanip>
#include <sstream>
#include <thread>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#elif defined(__linux__)
#include <fstream>
#endif

double SystemSnapshot::memoryUsedPercent() const {
    if (totalMemoryBytes == 0 || availableMemoryBytes > totalMemoryBytes) {
        return 0.0;
    }

    const std::uint64_t usedBytes = totalMemoryBytes - availableMemoryBytes;
    return (static_cast<double>(usedBytes) / static_cast<double>(totalMemoryBytes)) * 100.0;
}

SystemSnapshot SystemMonitor::capture() const {
    SystemSnapshot snapshot;
    snapshot.logicalProcessorCount = std::thread::hardware_concurrency();

#ifdef _WIN32
    MEMORYSTATUSEX status{};
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        snapshot.totalMemoryBytes = status.ullTotalPhys;
        snapshot.availableMemoryBytes = status.ullAvailPhys;
    }
#elif defined(__linux__)
    std::ifstream memInfo("/proc/meminfo");
    std::string key;
    std::uint64_t valueKiB = 0;
    std::string unit;

    while (memInfo >> key >> valueKiB >> unit) {
        if (key == "MemTotal:") {
            snapshot.totalMemoryBytes = valueKiB * 1024ULL;
        } else if (key == "MemAvailable:") {
            snapshot.availableMemoryBytes = valueKiB * 1024ULL;
        }

        if (snapshot.totalMemoryBytes > 0 && snapshot.availableMemoryBytes > 0) {
            break;
        }
    }
#endif

    return snapshot;
}

std::string SystemMonitor::formatBytes(std::uint64_t bytes) {
    static const char* units[] = {"B", "KiB", "MiB", "GiB", "TiB"};
    double value = static_cast<double>(bytes);
    std::size_t unitIndex = 0;

    while (value >= 1024.0 && unitIndex < 4) {
        value /= 1024.0;
        ++unitIndex;
    }

    std::ostringstream output;
    output << std::fixed << std::setprecision(value >= 10.0 ? 1 : 2)
           << value << ' ' << units[unitIndex];
    return output.str();
}
