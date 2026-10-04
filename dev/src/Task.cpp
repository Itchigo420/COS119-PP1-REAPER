#include "Task.h"

#include <utility>

Task::Task(int id, std::string title)
    : id_(id), title_(std::move(title)), complete_(false) {}

int Task::getId() const {
    return id_;
}

const std::string& Task::getTitle() const {
    return title_;
}

bool Task::isComplete() const {
    return complete_;
}

void Task::markComplete() {
    complete_ = true;
}
