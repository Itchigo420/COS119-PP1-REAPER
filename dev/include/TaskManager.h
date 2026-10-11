#pragma once

#include "Task.h"

#include <string>
#include <vector>

enum class CompleteTaskResult {
    Completed,
    AlreadyComplete,
    NotFound
};

class TaskManager {
public:
    int addTask(const std::string& title, Priority priority);
    CompleteTaskResult completeTask(int id);
    const std::vector<Task>& getTasks() const;
    bool empty() const;

private:
    Task* findTaskById(int id);

    std::vector<Task> tasks_;
    int nextId_ = 1;
};
