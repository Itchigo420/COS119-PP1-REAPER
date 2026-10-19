cmake_minimum_required(VERSION 3.16)
project(REAPER_Task_Console LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(reaper
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/TaskStorage.cpp
    src/UserInterface.cpp
    src/SystemMonitor.cpp
)

target_include_directories(reaper PRIVATE include)

enable_testing()
add_executable(reaper_tests
    tests/TaskManagerTests.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/TaskStorage.cpp
    src/SystemMonitor.cpp
)
target_include_directories(reaper_tests PRIVATE include)
add_test(NAME reaper_task_manager_tests COMMAND reaper_tests)

add_executable(reaper_storage_tests
    tests/TaskStorageTests.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/TaskStorage.cpp
)
target_include_directories(reaper_storage_tests PRIVATE include)
add_test(NAME reaper_storage_roundtrip_tests COMMAND reaper_storage_tests)

find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
    add_test(NAME reaper_console_integration_tests
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/ConsoleFlowTests.py" "$<TARGET_FILE:reaper>")
endif()
