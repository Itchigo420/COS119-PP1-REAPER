# REAPER — Final Showcase Recording Script
**Due:** Friday, October 23, 2026 by 11:59 PM EDT  
**Required:** 3–5 minutes; audio narration; clearly running console demonstration.

## 0:00–0:30 — Opening
"Hi, I'm Dustin Summerour. For Project and Portfolio I, I built REAPER, a C++ task and system monitoring console. The goal was to create a small, working application with solid object-oriented structure, safe user input, and a practical task manager I could continue building later."

## 0:30–1:20 — Four concepts
"The first skill was **classes and objects**: Task holds data, TaskManager handles the decisions, and UserInterface handles the console. Second, I improved my **pointers and references** by using non-owning pointers to view tasks without copying them or manually managing memory. Third, I improved **input validation and error handling**, especially using getline, stoi, and try/catch for menu choices. Fourth, I improved my **GitHub workflow** by organizing work as Issues, tracking it on a Project board, committing changes, and using dev-to-main pull requests. These choices made the program easier to debug and extend."

## 1:20–1:45 — Development evolution
"I started with a basic task menu. I added priorities and status filtering, then completed task counts, sorting, and a small CPU and memory status screen. My instructor encouraged me to keep the scope focused, so I did not try to build the entire REAPER platform. Week 4 added task persistence, final tests, and cleanup."

## 1:45–3:25 — Live demo (keep actual console on screen)
"Here's the application running. I can add a task, choose its priority, and see task totals. When I view the task list, high priority comes first. I can complete a task and filter active or completed tasks. The system-status option shows the processor and memory snapshot. If I enter letters or an out-of-range choice, the program asks me to retry instead of crashing. Now I'll exit. My tasks save to disk. When I run REAPER again using the same task file, it restores the tasks, their IDs, priorities, and completion flags. That was my main Week 4 improvement."

## 3:25–4:10 — What I learned, and next
"The biggest challenge was improving the application without losing the structure I already had. I had to think about safe task restoration, corrupt files, and edge cases instead of just adding features. Automated tests now verify the task manager, file I/O, and console flow. Next time I'd write the persistence tests earlier and keep the scope even tighter from Week 1. After this course, I'd like to expand the system monitoring features and connect this project to the larger REAPER architecture. Thanks for watching."

## Recording checklist
- Start the console application on screen; never substitute slides alone for the demo.
- Capture audible narration (you do not need to appear on camera).
- Show adding tasks, filtering, completing, system status, input error recovery, exit, and restart with restored data.
- Keep final video between **3:00 and 5:00**, and verify the link or upload is accessible.
