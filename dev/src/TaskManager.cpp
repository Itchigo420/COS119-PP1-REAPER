#include "TaskManager.h"

#include <algorithm>

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

std::vector<const Task*> TaskManager::getTasksByPriority(
    bool includeActive, bool includeCompleted) const {
    std::vector<const Task*> matches;

    for (const Task& task : tasks_) {
        const bool shouldInclude =
            (!task.isComplete() && includeActive) ||
            (task.isComplete() && includeCompleted);

        if (shouldInclude) {
            matches.push_back(&task);
        }
    }

    std::sort(matches.begin(), matches.end(), [](const Task* left, const Task* right) {
        const int leftPriority = static_cast<int>(left->getPriority());
        const int rightPriority = static_cast<int>(right->getPriority());
        if (leftPriority != rightPriority) {
            return leftPriority > rightPriority;
        }
        return left->getId() < right->getId();
    });

    return matches;
}

std::size_t TaskManager::totalCount() const {
    return tasks_.size();
}

std::size_t TaskManager::activeCount() const {
    return static_cast<std::size_t>(std::count_if(
        tasks_.begin(), tasks_.end(), [](const Task& task) { return !task.isComplete(); }));
}

std::size_t TaskManager::completedCount() const {
    return totalCount() - activeCount();
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
