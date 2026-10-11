# Week 2 Testing Report

## Build Verification

The Week 2 REAPER Task Console was built with CMake using the existing C++17 configuration. The build completed successfully and produced the `reaper` executable.

## Manual Test Cases

| Test | Expected Result | Result |
| --- | --- | --- |
| Enter non-numeric menu input | Program rejects the input and asks again | Pass |
| Enter a menu number outside 1-4 | Program explains the valid range and asks again | Pass |
| Enter a blank or whitespace-only task title | Program rejects the title and asks again | Pass |
| Create a task with Low priority | Task is created and displays Low priority | Pass |
| Create a task with Medium priority | Task is created and displays Medium priority | Pass |
| Create a task with High priority | Task is created and displays High priority | Pass |
| Enter an invalid priority value | Program rejects the value and asks again | Pass |
| Complete an existing task | Task changes from active to completed | Pass |
| Enter a missing task ID | Program reports that the task was not found | Pass |
| Enter non-numeric task ID input | Program rejects the input and asks again | Pass |
| Filter active tasks | Only incomplete tasks are displayed | Pass |
| Filter completed tasks | Only completed tasks are displayed | Pass |
| Show all tasks | Active and completed tasks are displayed together | Pass |
| Exit program | Program ends cleanly | Pass |

## Week 2 Verification Summary

The Week 2 implementation passed the planned manual checks for task priorities, status filtering, task completion, and improved input validation. The test pass also confirmed that invalid input does not terminate the application or leave `std::cin` in a failed state.

No blocking defects were found during the final Week 2 console test.
