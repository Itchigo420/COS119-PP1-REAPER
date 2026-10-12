#include "UserInterface.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

bool hasVisibleText(const std::string& text) {
    return text.find_first_not_of(" \t\r\n") != std::string::npos;
}

int readIntegerInRange(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::cout << prompt;

        int value = 0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (value >= minimum && value <= maximum) {
                return value;
            }

            std::cout << "Choose a number from " << minimum << " to "
                      << maximum << ".\n";
            continue;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a valid whole number.\n";
    }
}

int readPositiveInteger(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        int value = 0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (value > 0) {
                return value;
            }

            std::cout << "Enter a task ID greater than zero.\n";
            continue;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a valid numeric task ID.\n";
    }
}

}  // namespace

UserInterface::UserInterface(TaskManager& manager) : manager_(manager) {}

void UserInterface::run() {
    bool running = true;

    while (running) {
        printMenu();
        switch (readMenuChoice()) {
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
                running = false;
                std::cout << "REAPER session ended.\n";
                break;
        }
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
              << "4. Exit\n";
}

void UserInterface::addTask() {
    std::string title;
    while (true) {
        std::cout << "Task title: ";
        std::getline(std::cin, title);

        if (hasVisibleText(title)) {
            break;
        }

        std::cout << "Task title cannot be empty or only whitespace. Try again.\n";
    }

    const int priorityChoice = readIntegerInRange(
        "Priority (1 = Low, 2 = Medium, 3 = High): ", 1, 3);
    const Priority priority = static_cast<Priority>(priorityChoice);

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

    const int filterChoice = readIntegerInRange("Filter: ", 1, 3);

    if (filterChoice == 1) {
        printTasks(true, true);
    } else if (filterChoice == 2) {
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
    const int id = readPositiveInteger("Task ID to complete: ");

    switch (manager_.completeTask(id)) {
        case CompleteTaskResult::Completed:
            std::cout << "Task #" << id << " marked complete.\n";
            break;
        case CompleteTaskResult::AlreadyComplete:
            std::cout << "Task #" << id << " is already complete.\n";
            break;
        case CompleteTaskResult::NotFound:
            std::cout << "Task #" << id << " was not found. Check the list and try again.\n";
            break;
    }
}

int UserInterface::readMenuChoice() const {
    return readIntegerInRange("Selection: ", 1, 4);
}
