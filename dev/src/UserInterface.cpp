#include "UserInterface.h"
#include "SystemMonitor.h"
#include "TaskStorage.h"

#include <iomanip>
#include <iostream>
#include <optional>
#include <utility>
#include <stdexcept>
#include <string>

namespace {

bool hasVisibleText(const std::string& text) {
    return text.find_first_not_of(" \t\r\n") != std::string::npos;
}

std::string trimWhitespace(const std::string& text) {
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }

    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

int parseWholeNumber(const std::string& input) {
    const std::string cleanedInput = trimWhitespace(input);
    std::size_t parsedCharacters = 0;
    const int value = std::stoi(cleanedInput, &parsedCharacters);

    if (parsedCharacters != cleanedInput.size()) {
        throw std::invalid_argument("unexpected characters");
    }

    return value;
}

std::optional<int> readIntegerInRange(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::cout << prompt;

        std::string input;
        if (!std::getline(std::cin, input)) {
            return std::nullopt;
        }

        try {
            const int value = parseWholeNumber(input);

            if (value >= minimum && value <= maximum) {
                return value;
            }

            std::cout << "Choose a number from " << minimum << " to "
                      << maximum << ".\n";
        } catch (const std::invalid_argument&) {
            std::cout << "Enter a valid whole number.\n";
        } catch (const std::out_of_range&) {
            std::cout << "That number is too large. Try again.\n";
        }
    }
}

std::optional<int> readPositiveInteger(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string input;
        if (!std::getline(std::cin, input)) {
            return std::nullopt;
        }

        try {
            const int value = parseWholeNumber(input);

            if (value > 0) {
                return value;
            }

            std::cout << "Enter a task ID greater than zero.\n";
        } catch (const std::invalid_argument&) {
            std::cout << "Enter a valid numeric task ID.\n";
        } catch (const std::out_of_range&) {
            std::cout << "That task ID is too large. Try again.\n";
        }
    }
}

}  // namespace

UserInterface::UserInterface(TaskManager& manager, std::string dataFile)
    : manager_(manager), dataFile_(std::move(dataFile)) {}

void UserInterface::run() {
    std::string message;
    const LoadResult result = TaskStorage::load(dataFile_, manager_, message);
    std::cout << message << '\n';
    const bool saveIsSafe = result != LoadResult::Error;
    if (!saveIsSafe) {
        std::cout << "Existing task file will not be overwritten.\n";
    }

    bool running = true;
    while (running) {
        printMenu();
        const std::optional<int> choice = readMenuChoice();
        if (!choice) {
            std::cout << "Input closed; ending REAPER session.\n";
            break;
        }
        switch (*choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                showSystemStatus();
                break;
            case 5:
                running = false;
                std::cout << "REAPER session ended.\n";
                break;
        }
    }
    if (saveIsSafe) {
        if (!TaskStorage::save(dataFile_, manager_, message)) {
            std::cerr << "WARNING: " << message << '\n';
        } else {
            std::cout << message << '\n';
        }
    } else {
        std::cerr << "WARNING: Changes in this session were not saved because "
                     "the original task file could not be loaded safely.\n";
    }
}

void UserInterface::printMenu() const {
    std::cout << "\n=== REAPER Task Console ===\n"
              << "Tasks: " << manager_.totalCount() << " total | "
              << manager_.activeCount() << " active | "
              << manager_.completedCount() << " complete\n"
              << "1. Add task\n"
              << "2. View tasks\n"
              << "3. Complete task\n"
              << "4. System status\n"
              << "5. Exit\n";
}

void UserInterface::addTask() {
    std::string title;
    while (true) {
        std::cout << "Task title: ";
        if (!std::getline(std::cin, title)) {
            return;
        }
        if (hasVisibleText(title)) {
            break;
        }

        std::cout << "Task title cannot be empty or only whitespace. Try again.\n";
    }

    const std::optional<int> priorityChoice = readIntegerInRange(
        "Priority (1 = Low, 2 = Medium, 3 = High): ", 1, 3);
    if (!priorityChoice) {
        return;
    }
    const Priority priority = static_cast<Priority>(*priorityChoice);

    const int id = manager_.addTask(title, priority);
    std::cout << "Added task #" << id << " with "
              << priorityToString(priority) << " priority.\n";
}

void UserInterface::listTasks() const {
    if (manager_.empty()) {
        std::cout << "No tasks yet. Add a task first.\n";
        return;
    }

    std::cout << "\nView tasks by status:\n"
              << "1. All tasks\n"
              << "2. Active tasks\n"
              << "3. Completed tasks\n";

    const std::optional<int> filterChoice = readIntegerInRange("Filter: ", 1, 3);
    if (!filterChoice) {
        return;
    }

    if (*filterChoice == 1) {
        printTasks(true, true);
    } else if (*filterChoice == 2) {
        printTasks(true, false);
    } else {
        printTasks(false, true);
    }
}

void UserInterface::printTasks(bool includeActive, bool includeCompleted) const {
    const std::vector<const Task*> tasks =
        manager_.getTasksByPriority(includeActive, includeCompleted);

    std::cout << "\nTasks (High to Low priority):\n";
    if (tasks.empty()) {
        std::cout << "No tasks match this filter.\n";
        return;
    }

    for (const Task* task : tasks) {
        std::cout << '[' << (task->isComplete() ? 'X' : ' ') << "] #"
                  << task->getId() << " [" << priorityToString(task->getPriority())
                  << "] - " << task->getTitle() << '\n';
    }
}

void UserInterface::completeTask() {
    if (manager_.empty()) {
        std::cout << "No tasks to complete. Add a task first.\n";
        return;
    }

    listTasks();
    const std::optional<int> id = readPositiveInteger("Task ID to complete: ");
    if (!id) {
        return;
    }

    switch (manager_.completeTask(*id)) {
        case CompleteTaskResult::Completed:
            std::cout << "Task #" << *id << " marked complete.\n";
            break;
        case CompleteTaskResult::AlreadyComplete:
            std::cout << "Task #" << *id << " is already complete.\n";
            break;
        case CompleteTaskResult::NotFound:
            std::cout << "Task #" << *id << " was not found. Check the list and try again.\n";
            break;
    }
}

void UserInterface::showSystemStatus() const {
    const SystemSnapshot snapshot = SystemMonitor{}.capture();

    std::cout << "\n=== REAPER System Status ===\n";
    if (snapshot.logicalProcessorCount > 0) {
        std::cout << "Logical processors: " << snapshot.logicalProcessorCount << '\n';
    } else {
        std::cout << "Logical processors: unavailable\n";
    }

    if (snapshot.totalMemoryBytes > 0) {
        std::cout << "Physical memory: "
                  << SystemMonitor::formatBytes(snapshot.totalMemoryBytes) << " total\n"
                  << "Available memory: "
                  << SystemMonitor::formatBytes(snapshot.availableMemoryBytes) << '\n'
                  << "Memory used: " << std::fixed << std::setprecision(1)
                  << snapshot.memoryUsedPercent() << "%\n" << std::defaultfloat;
    } else {
        std::cout << "Physical memory: unavailable on this platform\n";
    }
}

std::optional<int> UserInterface::readMenuChoice() const {
    return readIntegerInRange("Selection: ", 1, 5);
}
