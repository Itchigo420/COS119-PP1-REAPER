#pragma once

#include <string>

enum class Priority {
    Low = 1,
    Medium = 2,
    High = 3
};

std::string priorityToString(Priority priority);

class Task {
public:
    Task(int id, std::string title, Priority priority);

    int getId() const;
    const std::string& getTitle() const;
    Priority getPriority() const;
    bool isComplete() const;
    void markComplete();

private:
    int id_;
    std::string title_;
    Priority priority_;
    bool complete_;
};
