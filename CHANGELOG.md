# Changelog

## Week 2 - Milestone 2

### Added
- Low, Medium, and High task priority levels.
- Priority labels in task-list output.
- Filters for all, active, and completed tasks.

### Improved
- Menu input now retries invalid text and out-of-range values.
- Task titles reject empty and whitespace-only input.
- Priority selection validates accepted values and retries invalid input.
- Task ID input validates numeric and positive values.
- User feedback now gives clearer instructions after invalid input or missing task IDs.

### Verified
- CMake C++17 build completed successfully.
- Manual console testing covered priority creation, completion, filtering, invalid input, and exit behavior.

## Week 3 - Refinement and System Status

- Refactored task lookup and completion feedback.
- Added safe non-owning pointer use in `TaskManager`.
- Added total, active, and completed task counts.
- Added High-to-Low priority ordering.
- Added a cross-platform processor/memory System Status screen.
- Added automated CTest regression coverage and expanded integration testing.
- Added Milestone 3 design/refactoring documentation and Week 3 testing notes.
