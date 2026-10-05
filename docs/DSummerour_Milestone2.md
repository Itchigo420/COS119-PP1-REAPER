> Use this worksheet to plan the next phase of your project **before you begin coding**.
> Be clear, specific, and intentional—this will guide your development this week.

---
## 📌 Project Overview

**Project Name:**
→ REAPER Task Console

**What does your program currently do? (1–3 sentences)**
→ The program currently lets the user add tasks, view the task list, mark tasks complete, and exit through a console menu. The program uses separate `Task`, `TaskManager`, and `UserInterface` classes with a `vector<Task>` to store task objects.

---
## 🔍 Current Progress Check

**What is working right now?**
→ The main menu loop, task creation, task listing, task completion, basic numeric input validation, and class structure are working. The project also builds through the Visual Studio solution created in Week 1.

**What is NOT working or incomplete?**
→ Tasks do not currently have priority levels, the task list cannot be filtered by completion status, and some invalid input returns the user to the menu instead of giving them a clear retry prompt.

**What feels confusing or messy in your code?**
→ Input validation is spread across multiple UI functions. I want the interaction to be more consistent so every invalid entry gives the user a clear message and another chance to enter the correct value.

---
## 🚀 Feature Planning

### Feature 1
**Name:**
→ Task Priority Levels

**What does this feature do?**
→ It allows each task to be assigned a Low, Medium, or High priority and displays that priority when tasks are listed.

**Why is this feature important?**
→ Priority makes the task manager more useful because users can quickly see which work needs attention first.

---
### Feature 2
**Name:**
→ Improved Input Validation and Feedback

**What does this feature do?**
→ It improves menu and task-entry validation, rejects whitespace-only task names, and gives clear retry instructions when the user enters an invalid value.

**Why is this feature important?**
→ This makes the console easier to understand and prevents unexpected input from creating confusing program behavior.

---
### Feature 3 (optional)
**Name:**
→ Task Status Filtering

**What does this feature do?**
→ It lets the user display all tasks, only active tasks, or only completed tasks.

**Why is this feature important?**
→ Filtering keeps the output readable as more tasks are added and helps the user focus on the information they need.

---
## 🧩 System Design Updates

**Will you need to create any new classes? If so, which ones?**
→ No new class is required for the planned Week 2 features. The existing class responsibilities are already separated well enough for this stage of the project.

**Will you modify any existing classes? How?**
→ `Task` will store and report a priority value. `TaskManager` will accept priority when creating tasks and support status-based task access. `UserInterface` will collect the new input, display priority/status choices, and provide stronger validation and feedback.

**What data structures will you use (vectors, 2D vectors, etc.)?**
→ The program will continue using `std::vector<Task>` as the main container because it fits the current number of tasks and supports simple iteration, filtering, and updates.

---## 🔄 Program Flow

**Describe how a user interacts with your program:**

1. Program starts → REAPER Task Console creates the task manager and displays the main menu.
2. User chooses → The user selects an action such as adding, viewing, completing, or filtering tasks.
3. Program responds → The program validates the input, updates the task collection when needed, and prints clear feedback/output.
4. Loop/next step → The main menu returns after each action until the user chooses Exit.

---
## 🎯 Usability Improvements

How will you make your program easier to use this week?

- Clearer prompts:
→ Prompts will tell the user exactly what values are accepted, including numbered priority and status options.

- Better error handling:
→ Invalid menu choices, invalid task IDs, bad numeric input, and blank/whitespace-only task titles will produce helpful messages and allow the user to retry safely.

- Improved menu/navigation:
→ Menu options and task displays will stay consistently numbered and formatted, and status filtering will reduce clutter in longer task lists.

---
## ⚠️ Potential Challenges

**What do you think will be the hardest part this week?**
→ The hardest part will be expanding the task data and UI behavior without making the existing class responsibilities messy or duplicating validation logic.

**What is your plan if you get stuck?**
→ I will test one feature at a time, use the debugger and compiler messages to isolate problems, review the course examples, and simplify/refactor the code before adding more functionality.

---
## 📈 Level Up Goal

**What skill are you focusing on improving this week?**
→ Input validation and class design.

**What will you do to improve it?**
→ I will practice centralizing repeated validation behavior, test edge cases intentionally, review lecture/course examples, and use debugging to verify that each class is handling only its intended responsibility.

---
## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

- [ ] Add task priority levels (#11)
- [ ] Improve menu input validation and feedback (#12)
- [ ] Add task status filtering (#13)
- [ ] Test invalid input and edge cases (#6)

---
## 🔥 Final Check

Before you start coding, ask yourself:

- [x] Do I know what I’m building this week?
- [x] Do I know where to start?
- [x] Did I break my work into small tasks?

If yes → start coding 🚀
If no → refine your plan first

---
## 😈 Final Thought

> Plan it now… or debug it later.
