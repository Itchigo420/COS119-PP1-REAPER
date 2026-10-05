# REAPER Development

The Week 1 C++ implementation lives in this directory.

## Layout

- `include/Task.h` - task model
- `include/TaskManager.h` - task collection and operations
- `include/UserInterface.h` - console interface
- `src/` - class implementations and `main.cpp`
- `CMakeLists.txt` - CMake build configuration

## Build with Visual Studio

Open `REAPER.sln` in Visual Studio and build the `Debug|x64` or `Release|x64` configuration. The solution includes all Week 1 source and header files.

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
