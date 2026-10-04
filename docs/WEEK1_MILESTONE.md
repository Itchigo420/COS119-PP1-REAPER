# Week 1 Milestone - REAPER

## Project Proposal

REAPER is a C++ console application inspired by a larger system-management project. For Project & Portfolio I, the scope is intentionally limited so each milestone can add one testable layer at a time.

The Week 1 version is a task console. It establishes the program loop and object-oriented structure that later REAPER features can build on.

## Week 1 Goals

- Create a working C++ console application under `/dev`.
- Use multiple classes with separated responsibilities.
- Provide a repeatable menu/program loop.
- Accept and validate user input.
- Create, display, and complete tasks.
- Use the `dev` branch for development before merging to `main`.
- Track later development through GitHub Issues and the Project board.

## Class Design

### Task

Represents one task with an ID, title, and completion state.

### TaskManager

Owns the task collection and handles operations such as adding a task and marking a task complete.

### UserInterface

Handles console output, menu input, input validation, and interaction with `TaskManager`.

## Future Scope

Later milestones can extend the application with simulated system-status information, file persistence, pointer/reference or dynamic-memory features, more testing, and refactoring. Those features remain tracked as backlog Issues instead of being forced into Week 1.

## Week 1 Verification

The Week 1 build was compiled using C++17 with warnings enabled and manually exercised through the full menu flow: add task, view tasks, complete a task, view the updated state, and exit.
