#include "TaskManager.h"

#include <algorithm>
#include <limits>
#include <set>
#include <stdexcept>

namespace {

bool validPriority(Priority priority) {
    return priority == Priority::Low || priority == Priority::Medium ||
           priority == Priority::High;
}

bool hasVisibleText(const std::string& title) {
    return title.find_first_not_of(" \t\r\n") != std::string::npos;
}

}  // namespace

int TaskManager::addTask(const std::string& title, Priority priority) {
    if (!hasVisibleText(title) || !validPriority(priority)) {
        throw std::invalid_argument("Invalid task title or priority");
    }
    if (nextId_ <= 0 || nextId_ == std::numeric_limits<int>::max()) {
        throw std::overflow_error("Task ID limit reached");
    }
    tasks_.emplace_back(nextId_, title, priority);
    return nextId_++;
}

bool TaskManager::restoreTasks(const std::vector<Task>& savedTasks, std::string& error) {
    std::set<int> seenIds;
    int maxId = 0;

    for (const Task& task : savedTasks) {
        if (task.getId() <= 0 ||
            task.getId() == std::numeric_limits<int>::max() ||
            !hasVisibleText(task.getTitle()) || !validPriority(task.getPriority())) {
            error = "Saved task contains an invalid ID, title, or priority.";
            return false;
        }
        if (!seenIds.insert(task.getId()).second) {
            error = "Saved tasks contain duplicate IDs.";
            return false;
        }
        maxId = std::max(maxId, task.getId());
    }

    // Only commit the new data after the entire set has been validated.
    tasks_ = savedTasks;
    nextId_ = maxId + 1;
    error.clear();
    return true;
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

std::size_t TaskManager::totalCount() const { return tasks_.size(); }

std::size_t TaskManager::activeCount() const {
    return static_cast<std::size_t>(std::count_if(
        tasks_.begin(), tasks_.end(), [](const Task& task) { return !task.isComplete(); }));
}

std::size_t TaskManager::completedCount() const { return totalCount() - activeCount(); }

bool TaskManager::empty() const { return tasks_.empty(); }

Task* TaskManager::findTaskById(int id) {
    for (Task& task : tasks_) {
        if (task.getId() == id) {
            return &task;
        }
    }
    return nullptr;
}
