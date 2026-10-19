#include "TaskStorage.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void check(bool condition, const std::string& what) {
    if (!condition) {
        throw std::runtime_error(what);
    }
}

void writeFile(const fs::path& path, const std::string& contents) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << contents;
    check(out.good(), "Failed to write test fixture");
}

int main() {
    const auto suffix = std::to_string(
        std::chrono::steady_clock::now().time_since_epoch().count());
    const fs::path file = fs::temp_directory_path() / ("reaper_week4_" + suffix + ".txt");
    std::string message;
    try {
        TaskManager manager;
        check(TaskStorage::load(file.string(), manager, message) == LoadResult::NotFound,
              "Missing file should be a clean first run");
        check(manager.empty(), "Missing file should not add records");
        check(TaskStorage::save(file.string(), manager, message), "Empty save failed");
        check(TaskStorage::load(file.string(), manager, message) == LoadResult::Loaded,
              "Empty save failed to reload");
        check(manager.empty(), "Empty round-trip has records");

        TaskManager original;
        const int first = original.addTask("Fix \"quoted\" name \\ and spaces", Priority::High);
        original.addTask("Second task", Priority::Low);
        check(original.completeTask(first) == CompleteTaskResult::Completed,
              "Completion setup failed");
        check(TaskStorage::save(file.string(), original, message), "Populated save failed");

        TaskManager restored;
        check(TaskStorage::load(file.string(), restored, message) == LoadResult::Loaded,
              "Populated load failed: " + message);
        check(restored.totalCount() == 2 && restored.completedCount() == 1,
              "Round-trip counts wrong");
        check(restored.getTasks()[0].getTitle() == "Fix \"quoted\" name \\ and spaces",
              "Quoted title lost");
        check(restored.getTasks()[0].getId() == first &&
                  restored.getTasks()[0].isComplete(),
              "Task ID or completion lost");
        check(restored.addTask("Third task", Priority::Medium) == 3,
              "Next task ID must not conflict");
        check(restored.getTasksByPriority(true, true)[0]->getPriority() == Priority::High,
              "Priority sorting changed");

        std::vector<Task> duplicate{
            Task(4, "Valid", Priority::Low),
            Task(4, "Duplicate", Priority::High)};
        check(!restored.restoreTasks(duplicate, message), "Duplicate ID was accepted");
        check(restored.totalCount() == 3, "Failed restore must not replace live data");

        std::vector<Task> invalidPriority{Task(4, "Bad priority", static_cast<Priority>(99))};
        check(!restored.restoreTasks(invalidPriority, message),
              "Invalid priority was accepted");
        check(restored.totalCount() == 3, "Invalid restore corrupted live data");

        std::vector<Task> nonSequential{Task(15, "Fifteen", Priority::Medium)};
        check(restored.restoreTasks(nonSequential, message), "Valid nonsequential IDs rejected");
        check(restored.addTask("Sixteen", Priority::Low) == 16,
              "Next ID should follow highest restored ID");

        const std::vector<std::string> brokenFiles{
            "wrong_header\\n",
            "REAPER_TASKS_V1\\n1 9 0 \"Invalid priority\"\\n",
            "REAPER_TASKS_V1\\n1 1 2 \"Invalid boolean\"\\n",
            "REAPER_TASKS_V1\\n1 1 0 \"Valid\"\\n1 2 0 \"Duplicate\"\\n",
            "REAPER_TASKS_V1\\n1 2 0 \"Good\" extra\\n",
            "REAPER_TASKS_V1\\n1 2 0 \"Good\"\\nBAD_RECORD\\n",
            "REAPER_TASKS_V1\\n1 2 0 MissingQuotes\\n",
            "REAPER_TASKS_V1\\n0 2 0 \"Bad ID\"\\n"
        };
        // The fixtures use literal escaped newlines so replace them with line breaks.
        for (std::string bad : brokenFiles) {
            std::string::size_type at = 0;
            while ((at = bad.find("\\n", at)) != std::string::npos) {
                bad.replace(at, 2, "\n");
                ++at;
            }
            writeFile(file, bad);
            check(TaskStorage::load(file.string(), restored, message) == LoadResult::Error,
                  "Malformed file should be rejected");
            check(restored.totalCount() == 2, "Corrupt file changed live data");
            check(restored.getTasks()[0].getId() == 15,
                  "Corrupt load replaced live records");
        }

        fs::remove(file);
        std::cout << "Week 4 task persistence tests passed.\n";
    } catch (...) {
        std::error_code ignored;
        fs::remove(file, ignored);
        throw;
    }
    return 0;
}
