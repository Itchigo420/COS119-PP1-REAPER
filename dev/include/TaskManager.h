#pragma once

#include "Task.h"

#include <string>
#include <vector>

class TaskManager {
public:
    int addTask(const std::string& title);
    bool completeTask(int id);
    const std::vector<Task>& getTasks() const;
    bool empty() const;

private:
    std::vector<Task> tasks_;
    int nextId_ = 1;
};
