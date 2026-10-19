# Milestone 4 — Final Delivery
**Project:** REAPER C++ Task & System Console  
**Course:** Project & Portfolio I — Full Sail University  
**Final delivery:** Saturday, October 24, 2026, 11:59 PM ET

## Final project
REAPER is a focused C++17 console task manager with a read-only system-status screen. The project provides task creation, priorities, completion, filtering, sorting, progress counts, and safe numeric input. Week 4 adds **persistent task save/load**, so tasks survive application restarts.

## Object-oriented improvements
- `Task` owns each task's ID, title, priority, and completion flag.
- `TaskManager` owns `std::vector<Task>`, validates all records before restoring any, and maintains an ID counter that follows the highest restored task ID.
- A non-owning `Task*` lookup supports completion, while `std::vector<const Task*>` gives read-only views for filtering and sorting without duplicating task objects or allocating manually.
- `TaskStorage` handles text-file serialization/deserialization independently of the menu code.
- `UserInterface` uses a TaskManager reference for its operations, isolates console parsing, and handles EOF gracefully.
- `SystemMonitor` remains an intentionally small CPU/memory status feature.

## Persistence / reliability
- Tasks are saved when exiting the program, including exit on closed input.
- On startup a missing file starts a new task list.
- The save file is versioned (`REAPER_TASKS_V1`); escaped titles, stable IDs, priorities, and completion states are preserved.
- Invalid/duplicate task IDs, malformed records, invalid priorities, and unsupported file formats are rejected before any in-memory data is replaced.
- If a file cannot be read safely, the current session is **not** permitted to overwrite it.
- Saves first write to a temporary file, then replace the target; an existing file is protected with a recovery path when required by the platform.
- Errors are reported rather than silently ignored.

## Build and run
From the repository root:
```bash
cmake -S dev -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/reaper
```
On Windows, open `dev/REAPER.sln` in Visual Studio with C++17 support or run the CMake commands in the appropriate terminal. An optional path argument selects the task-file location:
```bash
./build/reaper ./my-tasks.txt
```

## Verification and evidence
- C++17 CMake build with `-Wall -Wextra -Wpedantic`: successful.
- Three CTest checks pass: original TaskManager/SystemMonitor tests, new persistence round-trip tests, and console integration tests.
- Verified missing files, multiple session restarts, completed-state restoration, ID continuity, malformed data, bad inputs, and EOF.
- Test details: `docs/WEEK4_TESTING.md`
- Proof images: `images/final-build.png`, `images/final-run.png`, `images/final-features.png`.

## Issue tracking and delivery
Week 4 work is tracked in #4 (save/load) and #23–#25 (safe task restoration, console reliability, persistence tests). Optional monitoring expansion #3 stays in Backlog. Completed development Issues should be Done on the established Project board.

This milestone intentionally avoids expansion into the full REAPER agent platform, following instructor advice to keep scope controlled.

## Final reflection
See the Week 4 final stand-up in `README.md`. The same stand-up is intended to be posted as a reply to the Week 4 Discord status post.
