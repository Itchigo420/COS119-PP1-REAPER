# Milestone 3 - Refinement, System Design, and Code Quality

## Week 3 Scope

Week 3 keeps the existing REAPER task-management foundation and improves it instead of expanding into the full REAPER platform. The system-monitoring work is intentionally limited to one read-only system snapshot so the application remains manageable within the course timeline.

## Features Added

- Added task summary counts for total, active, and completed tasks.
- Added High-to-Low priority ordering when tasks are displayed.
- Added separate feedback for a missing task ID and a task that is already complete.
- Added a lightweight system-status screen that reports logical processor count, total physical memory, available memory, and memory-use percentage.
- Added CTest regression coverage for TaskManager behavior and SystemMonitor formatting/snapshot behavior.

## System Design Updates

### TaskManager

Task lookup and completion decisions now live inside `TaskManager` instead of being spread across the user interface. A private `Task* findTaskById(int id)` helper returns a non-owning pointer to an existing task stored in the manager's `std::vector`. This uses pointers without introducing manual allocation or `new`/`delete` ownership.

`TaskManager` now also owns task filtering, counts, and priority ordering. The UI requests data from the manager instead of rebuilding the same logic itself.

### SystemMonitor

System monitoring was separated into its own `SystemMonitor` component. The class creates a small `SystemSnapshot` and hides platform-specific code behind one interface. Windows uses `GlobalMemoryStatusEx`, while Linux reads `/proc/meminfo`. Processor count uses the C++ standard library.

This keeps operating-system details out of `main()` and `UserInterface` and makes the feature easier to extend later.

### UserInterface

The menu remains responsible for user interaction only. It now shows task counts, displays sorted task results, handles the expanded completion result, and exposes a dedicated System Status option.

## Refactoring Improvements

### Completion Logic

**Before:** `completeTask()` returned only `true` or `false`, so the UI could not distinguish a missing task from one that had already been completed.

**After:** `CompleteTaskResult` returns `Completed`, `AlreadyComplete`, or `NotFound`. This makes the behavior clearer and avoids misleading success messages.

### Task Lookup

**Before:** `completeTask()` looped directly through the vector and immediately changed the first matching task.

**After:** task lookup is isolated in `findTaskById()`. The completion function now reads like a sequence of decisions: find the task, check its state, then update it.

### Filtering and Sorting

**Before:** the UI looped through every task and decided which tasks should be displayed.

**After:** `TaskManager::getTasksByPriority()` returns only matching tasks and sorts them by priority. The UI only prints the results. This reduces duplicated business logic in the presentation layer.

## Testing and Debugging

The project was configured and built with `-Wall -Wextra -Wpedantic` on Linux with no compiler warnings reported.

CTest result:

```text
1/1 Test #1: reaper_task_manager_tests ... Passed
100% tests passed, 0 tests failed out of 1
```

The console was also tested with invalid and edge-case input, including:

- Non-numeric and out-of-range main-menu input
- Blank or whitespace-only task titles
- Non-numeric and out-of-range priority input
- Invalid filter input
- Zero and missing task IDs
- Completing the same task twice
- Mixed-priority ordering
- Task summary counts before and after completion
- System-status display

All tested paths returned controlled feedback and the application exited normally.

## GitHub Work Tracked This Week

- #15 Refactor task lookup and completion feedback
- #16 Add task summary and priority sorting
- #17 Add lightweight system status dashboard
- #18 Expand Week 3 regression and edge-case testing

## What Changed and Why

The largest Week 3 change was moving more responsibility out of the console UI and into focused classes. The goal was not to make REAPER much larger; it was to make the existing application easier to understand, test, and maintain while adding one system-monitoring feature that fits the original project direction.

## Remaining Scope

File save/load remains planned for Week 4. The broader system-monitoring concept (CPU load, storage, network, services, and additional management features) remains in the backlog rather than being forced into Milestone 3.
