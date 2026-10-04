#include "UserInterface.h"

#include <iostream>
#include <limits>
#include <string>

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
            default:
                std::cout << "Invalid option. Choose 1-4.\n";
                break;
        }
    }
}

void UserInterface::printMenu() const {
    std::cout << "\n=== REAPER Task Console ===\n"
              << "1. Add task\n"
              << "2. View tasks\n"
              << "3. Complete task\n"
              << "4. Exit\n"
              << "Selection: ";
}

void UserInterface::addTask() {
    std::cout << "Task title: ";
    std::string title;
    std::getline(std::cin, title);

    if (title.empty()) {
        std::cout << "Task title cannot be empty.\n";
        return;
    }

    const int id = manager_.addTask(title);
    std::cout << "Added task #" << id << ".\n";
}

void UserInterface::listTasks() const {
    if (manager_.empty()) {
        std::cout << "No tasks yet.\n";
        return;
    }

    std::cout << "\nCurrent tasks:\n";
    for (const Task& task : manager_.getTasks()) {
        std::cout << '[' << (task.isComplete() ? 'X' : ' ') << "] #"
                  << task.getId() << " - " << task.getTitle() << '\n';
    }
}

void UserInterface::completeTask() {
    if (manager_.empty()) {
        std::cout << "No tasks to complete.\n";
        return;
    }

    listTasks();
    std::cout << "Task ID to complete: ";

    int id = 0;
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a valid numeric task ID.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (manager_.completeTask(id)) {
        std::cout << "Task #" << id << " marked complete.\n";
    } else {
        std::cout << "Task #" << id << " was not found.\n";
    }
}

int UserInterface::readMenuChoice() const {
    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}
