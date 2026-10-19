#pragma once

#include "TaskManager.h"

#include <optional>
#include <string>

class UserInterface {
public:
    explicit UserInterface(TaskManager& manager, std::string dataFile = "reaper-tasks.txt");
    void run();

private:
    TaskManager& manager_;
    std::string dataFile_;

    void printMenu() const;
    void addTask();
    void listTasks() const;
    void printTasks(bool includeActive, bool includeCompleted) const;
    void completeTask();
    void showSystemStatus() const;
    std::optional<int> readMenuChoice() const;
};
