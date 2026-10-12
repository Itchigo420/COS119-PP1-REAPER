#pragma once

#include "Task.h"

#include <cstddef>
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
    std::vector<const Task*> getTasksByPriority(bool includeActive, bool includeCompleted) const;
    std::size_t totalCount() const;
    std::size_t activeCount() const;
    std::size_t completedCount() const;
    bool empty() const;

private:
    Task* findTaskById(int id);

    std::vector<Task> tasks_;
    int nextId_ = 1;
};
