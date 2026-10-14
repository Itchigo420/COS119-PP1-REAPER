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

## Instructor Feedback Follow-Up: getline + stoi Validation

After Week 3 instructor feedback, numeric console input was refactored to use the Day 3 lecture approach: `std::getline()` reads the complete line, `std::stoi()` performs conversion, and `try/catch` handles `std::invalid_argument` and `std::out_of_range` failures. The previous `std::cin >>` / `clear()` / `ignore()` numeric-input pattern was removed.

The parser also verifies that the entire trimmed input was consumed, so values such as `2abc` and `2.5` are rejected instead of being partially accepted. Leading and trailing whitespace around an otherwise valid whole number is allowed.

Additional unusual-input checks:

| Input | Expected behavior | Result |
|---|---|---|
| `abc` | Reject as non-numeric | Pass |
| `2abc` | Reject mixed numeric/text input | Pass |
| `2.5` | Reject decimal input where a whole number is required | Pass |
| Blank numeric input | Reject and reprompt | Pass |
| Very large integer | Catch `std::out_of_range` and reprompt | Pass |
| Menu `0` / `6` | Reject outside the 1-5 range | Pass |
| Priority `0` / `4` | Reject outside the 1-3 range | Pass |
| Task ID `0` / `-1` | Reject because IDs must be positive | Pass |
| `  2  ` | Accept valid number with surrounding whitespace | Pass |

A source search after the refactor confirmed there are no remaining `std::cin >>`, `std::cin.clear()`, or `std::cin.ignore()` calls in `dev/src` or `dev/include`.
