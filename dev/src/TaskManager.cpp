#include "TaskManager.h"

int TaskManager::addTask(const std::string& title, Priority priority) {
    tasks_.emplace_back(nextId_, title, priority);
    return nextId_++;
}

bool TaskManager::completeTask(int id) {
    for (Task& task : tasks_) {
        if (task.getId() == id) {
            task.markComplete();
            return true;
        }
    }
    return false;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks_;
}

bool TaskManager::empty() const {
    return tasks_.empty();
}
