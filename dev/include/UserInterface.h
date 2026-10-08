#pragma once

#include "TaskManager.h"

class UserInterface {
public:
    explicit UserInterface(TaskManager& manager);
    void run();

private:
    TaskManager& manager_;

    void printMenu() const;
    void addTask();
    void listTasks() const;
    void printTasks(bool includeActive, bool includeCompleted) const;
    void completeTask();
    int readMenuChoice() const;
};
