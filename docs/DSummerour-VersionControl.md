# Instructions

This document has been completed as a reference for terminal commands, Git, GitHub, and version-control practices used during Project & Portfolio I.

<br>

## COS119-O — Project & Portfolio I: Computer Science

- **Dustin Summerour**
- **October 4, 2026**

This paper addresses some of the topic matter covered in research and activity this week. Reference links to the resources used are included at the bottom of the document.

## Topic: Terminal

Professional developers use Terminal daily. It is important to understand fundamental commands so files, folders, repositories, and development tools can be managed efficiently.

### 1. Essential Terminal Commands

- `clear`: Clear the screen.
- `pwd`: Print the current working directory.
- `ls`: List files and folders in the current directory.
- `ls -a`: List files and folders, including hidden or invisible files.
- `ls -lah`: List all files and folders in long, human-readable form, including hidden files.
- `cd <directory>`: Change to another directory.
- `cd /`: Change to the root directory.
- `cd ~`: Change to the current user's home directory.
- `cd ..`: Move up one folder level.
- `cd ../..`: Move up two folder levels.
- `cd ~/Desktop`: Change to the Desktop directory when using a Unix-style shell with a Desktop folder in the home directory.

### 2. Folder Drop

Typing `cd ` with a trailing space and then dragging a folder into a terminal inserts that folder's full path into the command line. After pressing Enter, the terminal changes the current working directory to that folder. This is useful because it avoids manually typing a long path and reduces mistakes caused by spaces or unusual folder names. I can verify the new location afterward with `pwd`.
