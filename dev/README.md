# REAPER Development

The current PP1 C++ implementation lives in this directory.

## Layout

- `include/Task.h` - task model
- `include/TaskManager.h` - task collection and operations
- `include/UserInterface.h` - console interface
- `include/SystemMonitor.h` - focused processor/memory monitoring interface
- `src/` - class implementations and `main.cpp`
- `tests/` - regression tests for task-management and monitoring behavior
- `CMakeLists.txt` - CMake build and CTest configuration

## Build with Visual Studio

Open `REAPER.sln` in Visual Studio and build the `Debug|x64` or `Release|x64` configuration. The solution includes the current source and header files used by the project.

## Build with CMake

```bash
cmake -S dev -B build
cmake --build build
```

## Build with g++

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Idev/include dev/src/*.cpp -o reaper
```

Development changes are made on the `dev` branch and merged into `main` through a pull request.


## Week 4 final functionality

Tasks now persist in `reaper-tasks.txt` across runs using the dedicated `TaskStorage` class.
Use a command-line argument to set the file path (`reaper ./my-tasks.txt`). Invalid or
unreadable files are reported and never overwritten automatically. The storage tests and
console integration tests run under CTest. See `../docs/WEEK4_TESTING.md`.
