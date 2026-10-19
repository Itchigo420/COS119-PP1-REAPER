#include "TaskStorage.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

namespace {

constexpr const char* kHeader = "REAPER_TASKS_V1";
constexpr std::size_t kMaxTasks = 100000;

bool writeTasks(const std::string& path, const TaskManager& manager) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        return false;
    }
    out << kHeader << '\n';
    for (const Task& task : manager.getTasks()) {
        out << task.getId() << ' ' << static_cast<int>(task.getPriority()) << ' '
            << (task.isComplete() ? 1 : 0) << ' '
            << std::quoted(task.getTitle()) << '\n';
    }
    out.flush();
    const bool ok = out.good();
    out.close();
    return ok && !out.fail();
}

}  // namespace

LoadResult TaskStorage::load(
    const std::string& path, TaskManager& manager, std::string& message) {
    namespace fs = std::filesystem;
    std::error_code errorCode;
    if (!fs::exists(path, errorCode) && !errorCode) {
        message = "No existing task file found; starting a new task list.";
        return LoadResult::NotFound;
    }
    if (errorCode) {
        message = "Could not check the task file: " + errorCode.message();
        return LoadResult::Error;
    }

    std::ifstream input(path, std::ios::binary);
    if (!input) {
        message = "Could not open the task file for reading.";
        return LoadResult::Error;
    }
    std::string header;
    if (!std::getline(input, header) || header != kHeader) {
        message = "Task file is invalid or uses an unsupported format.";
        return LoadResult::Error;
    }

    std::vector<Task> restored;
    std::string line;
    std::size_t lineNumber = 1;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (restored.size() >= kMaxTasks) {
            message = "Too many tasks in the saved file.";
            return LoadResult::Error;
        }
        int id = 0, priority = 0, completed = 0;
        std::string title;
        std::istringstream row(line);
        if (!(row >> id >> priority >> completed)) {
            message = "Invalid saved task on line " + std::to_string(lineNumber) + '.';
            return LoadResult::Error;
        }
        row >> std::ws;
        if (row.peek() != '"' || !(row >> std::quoted(title))) {
            message = "Invalid saved task on line " + std::to_string(lineNumber) + '.';
            return LoadResult::Error;
        }
        row >> std::ws;
        if (!row.eof() || (completed != 0 && completed != 1)) {
            message = "Invalid saved task on line " + std::to_string(lineNumber) + '.';
            return LoadResult::Error;
        }
        Task task(id, title, static_cast<Priority>(priority));
        if (completed == 1) {
            task.markComplete();
        }
        restored.push_back(task);
    }
    if (input.bad()) {
        message = "An I/O error occurred while reading saved tasks.";
        return LoadResult::Error;
    }

    std::string validationError;
    if (!manager.restoreTasks(restored, validationError)) {
        message = "Task file rejected: " + validationError;
        return LoadResult::Error;
    }
    message = "Loaded " + std::to_string(restored.size()) + " task(s) from " + path + '.';
    return LoadResult::Loaded;
}

bool TaskStorage::save(
    const std::string& path, const TaskManager& manager, std::string& message) {
    namespace fs = std::filesystem;
    const std::string temporary = path + ".tmp";
    const std::string backup = path + ".bak";
    if (!writeTasks(temporary, manager)) {
        std::error_code ignored;
        fs::remove(temporary, ignored);
        message = "Could not write the temporary task file.";
        return false;
    }

    std::error_code ec;
    fs::rename(temporary, path, ec);
    if (ec) {
        // Some Windows filesystems cannot rename over an existing destination.
        // Preserve the original file in a backup until the new file is in place.
        ec.clear();
        const bool exists = fs::exists(path, ec);
        if (ec || !exists) {
            message = "Could not replace the task file; original data was left untouched.";
            return false;
        }
        // Refuse to overwrite an old backup instead of risking silent data loss.
        ec.clear();
        if (fs::exists(backup, ec) || ec) {
            message = "Could not safely replace the file: a backup already exists.";
            return false;
        }
        fs::rename(path, backup, ec);
        if (ec) {
            message = "Could not back up the original task file.";
            return false;
        }
        fs::rename(temporary, path, ec);
        if (ec) {
            std::error_code restoreError;
            fs::rename(backup, path, restoreError);
            message = "Could not finalize the new file; old data recovery " +
                      std::string(restoreError ? "needs attention." : "succeeded.");
            return false;
        }
        std::error_code ignored;
        fs::remove(backup, ignored);
    }
    message = "Saved " + std::to_string(manager.totalCount()) + " task(s) to " + path + '.';
    return true;
}
