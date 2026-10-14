# Project & Portfolio I - REAPER

## Student

Dustin Summerour - Simulation Engineering student at Full Sail University.

## Project Overview

REAPER is a C++ console application being developed throughout Project & Portfolio I. The project uses a small task-management console as the Week 1 foundation so the application has a clear object-oriented structure that can be expanded into additional REAPER system-management features during later milestones.

The current Week 3 build supports prioritized task management, status filtering, safe task completion, task summaries, High-to-Low sorting, focused processor/memory system monitoring, regression testing, and robust `getline + stoi + try/catch` input validation.

## Current Features

- Add tasks with Low, Medium, or High priority.
- View all tasks, active tasks, or completed tasks.
- Mark tasks complete by task ID with separate completed/already-complete/not-found feedback.
- Display task totals and sort tasks from High to Low priority.
- Display a focused system-status snapshot for logical processors and physical memory.
- Reject invalid, partial, decimal, oversized, and out-of-range numeric input using `getline`, `stoi`, and exception handling.
- Keep task data, management logic, system monitoring, and console interaction separated across focused classes.

Week 3 verification details are recorded in `docs/WEEK3_TESTING.md`, and implementation changes are summarized in `CHANGELOG.md`.

## Repository Structure

- `dev/` - C++ source code and build configuration
- `docs/` - course documentation and milestone planning
- `README.md` - project overview and weekly stand-ups

## Build

The source uses C++17 and can be built with CMake or a C++17 compiler.

```bash
cmake -S dev -B build
cmake --build build
```

Or with g++:

```bash
g++ -std=c++17 -Idev/include dev/src/*.cpp -o reaper
```

## Weekly Stand Up

### Week 1

**Overview:** This week I set up the GitHub repository, development workflow, Project board, and the first working C++ foundation for REAPER. I organized the application around `Task`, `TaskManager`, and `UserInterface` classes and created a menu loop that can add, display, and complete tasks.

**Challenges:** The biggest challenge was deciding how much of the larger REAPER idea should be included in the first milestone without making the project too large too early. I addressed that by keeping Week 1 focused on a small working console foundation with clear class responsibilities and leaving later features in the backlog.

**Accomplishments:** I improved the project structure by separating data, application logic, and console interaction into different classes. I also used the GitHub `dev` workflow and verified that the current build compiles and runs successfully.

**Next Steps:** Next week I plan to expand the REAPER features while keeping the code organized. The current backlog includes simulated system-status monitoring, file save/load support, pointer and memory-management work, testing, and refactoring.

### Week 2

**Overview:** This week I expanded the REAPER Task Console from the Week 1 foundation into a more usable task-management prototype. I focused on task priority, task filtering, stronger input validation, testing, and keeping the existing class structure organized.

**Challenges:** The main challenge was improving the user flow without increasing the project scope too much. I also wanted invalid input to be handled consistently instead of forcing the user to restart an action.

**Accomplishments:** I added Low, Medium, and High task priorities, filters for all, active, and completed tasks, and clearer retry behavior for invalid menu choices, blank task titles, priority values, and task IDs. I also completed a CMake build, documented the test cases, updated the Milestone 2 documentation, and closed the three Week 2 GitHub Issues.

**Next Steps:** I plan to keep the project scope controlled, continue testing and refactoring as needed, and use the remaining backlog features only when they match the next course milestone requirements.

### Week 3

**Overview:** This week I focused on refining the REAPER task console instead of expanding the project too far. I improved the task-management core, added a small system-status feature, and added repeatable regression testing.


**Improvements:** I refactored task lookup and completion so `TaskManager` owns the decision logic and can distinguish completed, already-complete, and missing task IDs. I added task totals, active/completed counts, High-to-Low priority ordering, and a `SystemMonitor` component that reports logical processors and physical-memory usage.


**Challenges:** The main challenge was adding system monitoring without turning the four-week course project into the full REAPER platform. I kept the feature intentionally narrow and separated platform-specific monitoring code from the task-management and UI classes. I also tested several bad-input paths to make sure the refactor did not break the existing console flow.


**Feedback:** Earlier instructor feedback emphasized keeping the project scope under control and building a few monitoring features thoroughly. I used that feedback by keeping the task manager as the foundation and adding only a focused processor/memory snapshot this week.


**Accomplishments:** I improved my code organization and pointer use by adding a safe non-owning `Task*` lookup helper rather than using manual dynamic allocation. I also added CTest coverage, and the Week 3 build passes all automated tests with warnings enabled.


**Next Steps:** For Week 4, my primary goal is file save/load support so tasks persist between sessions, followed by final cleanup, verification, and submission preparation.


### Week 4

Final stand-up will be added after the Week 4 milestone is complete.
