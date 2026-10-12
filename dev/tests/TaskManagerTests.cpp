#include "SystemMonitor.h"
#include "TaskManager.h"

#include <cassert>
#include <iostream>

int main() {
    TaskManager manager;
    assert(manager.empty());
    assert(manager.totalCount() == 0);
    assert(manager.activeCount() == 0);
    assert(manager.completedCount() == 0);

    const int lowId = manager.addTask("Low priority", Priority::Low);
    const int highId = manager.addTask("High priority", Priority::High);
    const int mediumId = manager.addTask("Medium priority", Priority::Medium);

    assert(lowId == 1);
    assert(highId == 2);
    assert(mediumId == 3);
    assert(manager.totalCount() == 3);
    assert(manager.activeCount() == 3);

    const auto ordered = manager.getTasksByPriority(true, true);
    assert(ordered.size() == 3);
    assert(ordered[0]->getId() == highId);
    assert(ordered[1]->getId() == mediumId);
    assert(ordered[2]->getId() == lowId);

    assert(manager.completeTask(999) == CompleteTaskResult::NotFound);
    assert(manager.completeTask(highId) == CompleteTaskResult::Completed);
    assert(manager.completeTask(highId) == CompleteTaskResult::AlreadyComplete);
    assert(manager.activeCount() == 2);
    assert(manager.completedCount() == 1);

    const auto active = manager.getTasksByPriority(true, false);
    const auto completed = manager.getTasksByPriority(false, true);
    assert(active.size() == 2);
    assert(completed.size() == 1);
    assert(completed[0]->getId() == highId);

    assert(SystemMonitor::formatBytes(1024) == "1.00 KiB");
    const SystemSnapshot snapshot = SystemMonitor{}.capture();
    if (snapshot.totalMemoryBytes > 0) {
        assert(snapshot.availableMemoryBytes <= snapshot.totalMemoryBytes);
        assert(snapshot.memoryUsedPercent() >= 0.0);
        assert(snapshot.memoryUsedPercent() <= 100.0);
    }

    std::cout << "Week 3 TaskManager/SystemMonitor tests passed.\n";
    return 0;
}
