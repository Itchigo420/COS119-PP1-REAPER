# Project & Portfolio I - REAPER

## Student

Dustin Summerour - Simulation Engineering student at Full Sail University.

## Project Overview

REAPER is a C++ console application being developed throughout Project & Portfolio I. The project uses a small task-management console as the Week 1 foundation so the application has a clear object-oriented structure that can be expanded into additional REAPER system-management features during later milestones.

The Week 1 build supports creating tasks, viewing current tasks, marking tasks complete, and safely exiting the program.

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

My next stand-up will go here.

### Week 3

My Week 3 stand-up will go here.

### Week 4

My final stand-up will go here.
