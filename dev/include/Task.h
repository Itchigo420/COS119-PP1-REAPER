#pragma once

#include <string>

class Task {
public:
    Task(int id, std::string title);

    int getId() const;
    const std::string& getTitle() const;
    bool isComplete() const;
    void markComplete();

private:
    int id_;
    std::string title_;
    bool complete_;
};
