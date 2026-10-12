# Week 3 Testing Notes

## Build Verification

The project was configured with warnings enabled:

```bash
cmake -S dev -B /tmp/pp1-build -DCMAKE_CXX_FLAGS='-Wall -Wextra -Wpedantic'
cmake --build /tmp/pp1-build
```

Result: build completed successfully with no reported compiler warnings.

## Automated Regression Test

```bash
ctest --test-dir /tmp/pp1-build --output-on-failure
```

Result:

```text
1/1 Test #1: reaper_task_manager_tests ... Passed
100% tests passed, 0 tests failed out of 1
```

The C++ regression test verifies task IDs, task counts, priority ordering, completion results, active/completed filtering, memory formatting, and the SystemMonitor snapshot range.

## Console Integration Cases

| Case | Expected behavior | Result |
|---|---|---|
| Non-numeric menu input | Reject and ask for a whole number | Pass |
| Menu choice outside 1-5 | Reject and show valid range | Pass |
| Whitespace-only title | Reject and ask for a title | Pass |
| Non-numeric priority | Reject and ask for a whole number | Pass |
| Priority outside 1-3 | Reject and show valid range | Pass |
| Invalid filter | Reject and show valid range | Pass |
| Task ID 0 | Reject because IDs must be positive | Pass |
| Missing task ID | Report task not found | Pass |
| Complete valid task | Mark task complete | Pass |
| Complete same task twice | Report already complete | Pass |
| Priority ordering | High, Medium, Low | Pass |
| System status | Display processors and memory | Pass |
| Exit | End session normally | Pass |

## Observed System Snapshot

On the REAPER development host during testing, the System Status screen successfully reported logical processor count and physical-memory statistics. Values are collected at runtime, so they will change between systems and runs.
