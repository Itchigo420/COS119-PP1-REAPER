#include "Task.h"

#include <utility>

Task::Task(int id, std::string title, Priority priority)
    : id_(id), title_(std::move(title)), priority_(priority), complete_(false) {}

int Task::getId() const {
    return id_;
}

const std::string& Task::getTitle() const {
    return title_;
}

Priority Task::getPriority() const {
    return priority_;
}

bool Task::isComplete() const {
    return complete_;
}

void Task::markComplete() {
    complete_ = true;
}

std::string priorityToString(Priority priority) {
    switch (priority) {
        case Priority::Low:
            return "Low";
        case Priority::Medium:
            return "Medium";
        case Priority::High:
            return "High";
    }

    return "Unknown";
}
