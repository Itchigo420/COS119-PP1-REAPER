# Milestone 2 - REAPER Task Console

## Features Added

### Task Priority Levels
Tasks now store a priority value using the `Priority` enum. When a task is created, the user selects Low, Medium, or High priority. The selected priority is stored in the `Task` object and displayed whenever tasks are listed.

### Improved Input Validation and Feedback
The console now retries invalid input instead of immediately dropping the user back to the main menu. The Week 2 build handles:

- non-numeric menu input
- menu values outside the valid range
- empty or whitespace-only task titles
- invalid priority selections
- non-numeric and non-positive task IDs
- task IDs that do not exist

The prompts explain what went wrong and what the user should enter next.

### Task Status Filtering
The View Tasks option now lets the user display all tasks, only active tasks, or only completed tasks. This keeps the task list easier to read as more tasks are added.

## Code Structure Changes

`Task` now stores a `Priority` value in addition to its ID, title, and completion state. A `priorityToString` helper converts the enum into readable console output.

`TaskManager` now accepts the priority value when it creates a task while continuing to own the `std::vector<Task>` collection and completion logic.

`UserInterface` contains the Week 2 interaction changes. Reusable input helpers centralize numeric validation, task-title validation rejects whitespace-only input, and task display logic can include active tasks, completed tasks, or both.

No new class was required because the existing separation between task data, task-management logic, and console interaction still fits the project scope.

## Usability Improvements

The main usability improvement is consistent input validation with clear retry behavior. The user no longer has to restart an action because of a single bad numeric entry. Priority and filter choices are numbered, task output includes both completion state and priority, and error messages explain the expected input.

These changes make the console easier to navigate without increasing the project scope beyond the task-management foundation.

## What Changed and Why

Week 1 established the basic add, view, complete, and exit workflow. Week 2 expands that foundation in three small, testable ways: priority adds useful task metadata, filtering makes task output easier to manage, and stronger validation improves reliability and usability.

The implementation intentionally stays within the existing `Task`, `TaskManager`, and `UserInterface` design instead of adding unnecessary classes or unrelated REAPER system features.

## Testing

The Week 2 build was compiled with CMake using C++17 and completed a manual test pass covering:

- invalid text at the main menu
- invalid menu ranges
- whitespace-only titles
- invalid priority ranges
- Low and High priority task creation
- task completion
- all-task filtering
- active-task filtering
- completed-task filtering
- normal program exit

The build completed successfully and the tested flows produced the expected console output.
