# Week 4 — Final Verification (October 19, 2026)

## Build results
```text
cmake -S dev -B /tmp/reaper-pp1-week4-build -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic"
cmake --build /tmp/reaper-pp1-week4-build -j4
ctest --test-dir /tmp/reaper-pp1-week4-build --output-on-failure

1/3 reaper_task_manager_tests ........... Passed
2/3 reaper_storage_roundtrip_tests ...... Passed
3/3 reaper_console_integration_tests .... Passed
100% tests passed, 0 tests failed out of 3
```

## Scenarios verified
| Test | Result |
| --- | --- |
| Empty task manager + initial save/load | Pass |
| New task with Low/Medium/High priority | Pass |
| Task completion state restored after restart | Pass |
| Status filtering and priority ordering after load | Pass |
| Escaped quotes, backslashes, and spacing in titles | Pass |
| ID counter continues after restored maximum ID | Pass |
| Missing file (first run) | Pass |
| Invalid header, malformed row, extra fields | Pass |
| Duplicate IDs, invalid priority, bad completion value | Pass |
| Transactional restore keeps live state on bad file | Pass |
| File reading failure avoids overwriting original | Pass |
| Read/write failure shows warning | Pass |
| Non-numeric menu choice and invalid number retries | Pass |
| EOF exits cleanly (no prompt loop) | Pass |
| System CPU/memory snapshot (existing tests) | Pass |

## Manual demo path
1. Launch `reaper` in a fresh directory or with an explicit task path.
2. Add a High-priority task and a Low-priority task.
3. Display and filter tasks; mark one complete.
4. Show the CPU/memory status screen.
5. Exit and restart using the **same task file**.
6. Confirm restored task IDs, priorities, completed flags, and next ID.
7. Submit invalid menu input to demonstrate graceful recovery.

The final evidence PNG files were captured directly from a real Windows Terminal window running the final C++17 application and CMake/CTest under WSL on October 24, 2026. They are genuine screen captures, not recreated terminal graphics.

## Remaining platform limitation
Tests ran in the Linux WSL development environment with C++17. The Visual Studio project files were updated to include TaskStorage, but a native MSBuild run on Windows is not claimed here.
