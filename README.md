# Project & Portfolio I - REAPER

## Student

Dustin Summerour - Simulation Engineering student at Full Sail University.

## Project Overview

REAPER is a C++ console application being developed throughout Project & Portfolio I. The project uses a small task-management console as the Week 1 foundation so the application has a clear object-oriented structure that can be expanded into additional REAPER system-management features during later milestones.

The final Week 4 build supports prioritized task management, status filtering, safe task completion, task summaries, High-to-Low sorting, focused processor/memory monitoring, robust `getline + stoi + try/catch` validation, and versioned save/load persistence across sessions.

## Current Features

- Add tasks with Low, Medium, or High priority.
- View all tasks, active tasks, or completed tasks.
- Mark tasks complete by task ID with separate completed/already-complete/not-found feedback.
- Display task totals and sort tasks from High to Low priority.
- Display a focused system-status snapshot for logical processors and physical memory.
- Reject invalid, partial, decimal, oversized, and out-of-range numeric input using `getline`, `stoi`, and exception handling.
- Keep task data, management logic, system monitoring, persistence, and console interaction separated across focused classes.
- Save and reload task IDs, priorities, titles, and completion states between console sessions.
- Reject corrupt save files without overwriting them; end cleanly if terminal input closes.

Week 4 verification details are recorded in `docs/WEEK4_TESTING.md`, with final design/delivery details in `docs/Milestone4.md` and release notes in `CHANGELOG.md`.

## Repository Structure

- `dev/` - C++ source, Visual Studio / CMake builds, and automated tests
- `docs/` - course documentation, milestones, tests, dated Week 4 drafts
- `images/` - verified final build and application proof images
- `README.md` - project overview and weekly stand-ups

## Build

The source uses C++17 and can be built with CMake or a C++17 compiler.

```bash
cmake -S dev -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or with g++:

```bash
g++ -std=c++17 -Idev/include dev/src/*.cpp -o reaper
```

## Persistence
Tasks are stored in `reaper-tasks.txt` in the current working directory and loaded on the next start. The path can be changed by supplying a file path argument (for example `./build/reaper ./tasks.txt`). The runtime data file is ignored by Git. Invalid save files are not overwritten automatically.

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
**Overview:** This week I focused on delivering a stable version of REAPER instead of expanding its scope. I finished task save/load, reviewed the console flow, and ran final verification.

**Project Wrap-Up:** The finished C++ console now supports task priorities, task filters, completion status, sorted lists, task counts, a focused CPU/memory snapshot, and persistence between runs. I separated the file I/O code into a TaskStorage component, strengthened TaskManager's object/data-structure handling, updated Visual Studio and CMake files, and documented the final tests.

**Challenges:** A major challenge was preserving task IDs and states safely while protecting existing data if a save file is corrupted. I solved this by validating the complete restored task list before changing live data and avoiding overwrites when loading fails. Another challenge was handling unexpected end-of-input; the menu now exits cleanly instead of looping.

**Biggest Takeaway:** I improved at keeping C++ class responsibilities separate, validating assumptions, testing edge cases, and using GitHub Issues/PRs to track actual development. A smaller, verified application is more useful than a giant unfinished feature list.

**Future Development:** Outside this course, I'd expand REAPER with more system diagnostics, service health monitoring, and secure integration with the larger REAPER platform. Those ideas are intentionally left in Backlog rather than being misrepresented as finished.
