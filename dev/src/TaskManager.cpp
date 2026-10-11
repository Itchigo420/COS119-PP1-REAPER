#include "TaskManager.h"

int TaskManager::addTask(const std::string& title, Priority priority) {
    tasks_.emplace_back(nextId_, title, priority);
    return nextId_++;
}

CompleteTaskResult TaskManager::completeTask(int id) {
    Task* task = findTaskById(id);
    if (task == nullptr) {
        return CompleteTaskResult::NotFound;
    }

    if (task->isComplete()) {
        return CompleteTaskResult::AlreadyComplete;
    }

    task->markComplete();
    return CompleteTaskResult::Completed;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks_;
}

bool TaskManager::empty() const {
    return tasks_.empty();
}

Task* TaskManager::findTaskById(int id) {
    for (Task& task : tasks_) {
        if (task.getId() == id) {
            return &task;
        }
    }

    return nullptr;
}
