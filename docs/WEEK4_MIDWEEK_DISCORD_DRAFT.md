# Week 4 — Mid-Week Progress Check (POST WEDNESDAY, OCTOBER 21)
**Discord channel:** #cos1-week4-check-in  
**FSO submission:** One screenshot of the completed Discord post with embedded GitHub Issues and Project board screenshots.

**Project Progress:** REAPER has a stable C++ task-management foundation with priorities, completion tracking, filtering, sorted lists, and a focused CPU/memory status screen. This final week I implemented task save/load between sessions, improved error handling for damaged files and closed input, and ran CMake/CTest verification. All three test groups pass. My remaining delivery steps are checking the final documentation, updating the GitHub board/PR, capturing the Showcase presentation, and uploading the required evidence.

**Reflection & Growth — Surprising accomplishment:** I was surprised how much cleaner the program became once I separated task objects, business logic, storage, and console interactions. I can now test file persistence and invalid input without rewriting the task manager or introducing manual memory ownership.

**Reflection & Growth — Goal after this course:** I want to continue improving my code organization, testing discipline, and ability to design larger systems in small, reliable components.

**Something I'm Exploring:** I worked with versioned file I/O and transactional restoration in C++17. I learned that parsing data into temporary objects and validating the full set before replacing live state is safer than modifying application data line-by-line while reading a file.

**Attach inside this Discord post:** (1) authentic GitHub Issues screenshot, (2) authentic GitHub Project board screenshot with Backlog / Ready / In Progress / Done visible. Then screenshot your finished post and upload it to FSO.
