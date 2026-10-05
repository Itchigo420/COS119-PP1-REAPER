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

## Topic: Version Control & Git

Version control records changes to files over time so developers can review history, recover earlier versions, and collaborate without constantly overwriting one another's work. Git is the distributed version-control system used for this course.

### 1. Three Types of Version Control

1. **Local version control** stores file revisions on one computer. It can track previous versions for one developer, but it does not provide the collaboration or redundancy of networked systems.
2. **Centralized version control** stores the main repository on a central server. Developers check files in and out or synchronize changes with that server. This gives a team one shared source of truth, but the central server can become a single point of failure.
3. **Distributed version control** gives each developer a complete local copy of the repository and its history. Git uses this model. Developers can commit locally, create branches, work offline, and then synchronize changes with a remote repository such as GitHub.

### 2. Essential Git Commands

- `git clone <https-url>`: Clone a remote repository to the local computer.
- `git config --global user.name "Dustin Summerour"`: Set the global Git user name.
- `git config --global user.email "your-github-email@example.com"`: Set the global Git email address to the email associated with the GitHub account.
- `git status`: Show the current state of the working directory and staging area.
- `git add <file>` or `git add .`: Stage modified files for the next commit.
- `git commit -m "message"`: Create a commit with a meaningful message describing the change.
- `git log`: Display commit history.
- `git help` or `git help <command>`: Display Git help information.

### 3. Connecting to GitHub Using Terminal

For this course, I use HTTPS to connect Git to GitHub. The basic process is:

1. Open the GitHub repository in a browser and copy its HTTPS clone URL from the **Code** menu.
2. Open Terminal and move to the folder where I want the repository stored.
3. Run `git clone https://github.com/USERNAME/REPOSITORY.git` to download the repository.
4. Enter the new repository folder with `cd REPOSITORY`.
5. Confirm the remote with `git remote -v`.
6. Make changes locally, stage them with `git add`, and commit them with `git commit`.
7. Use `git push` to send local commits to GitHub. If GitHub requires authentication, sign in through the credential manager or use an approved personal access token instead of a GitHub account password.
8. Use `git pull` before new work when necessary so the local branch is synchronized with the remote branch.

This workflow keeps the local repository connected to GitHub while preserving a clear commit history.

### 4. Using `.gitignore` and Why It Is Important

- **What is the purpose of this file?**  
  A `.gitignore` file tells Git which untracked files or folders should not be added to version control. It helps keep repositories clean by excluding generated files, local settings, build output, temporary files, credentials, and other content that should not be shared.

- **What is the `.DS_Store` file and why would you want to ignore it?**  
  `.DS_Store` is a hidden metadata file created by macOS Finder to store folder-view preferences such as icon positions and display settings. It has nothing to do with the source code, can create unnecessary repository changes, and is different for each user's machine, so it should normally be ignored.

- **What other file or folder would you want to add to a `.gitignore` file and why?**  
  For a Visual Studio C++ project, I would ignore folders such as `.vs/`, `Debug/`, `Release/`, `x64/`, and compiled files such as `*.obj` and `*.exe`. These are generated automatically during development and builds, so tracking them would make the repository larger and create unnecessary changes. I would also ignore files such as `.env` if they contain local configuration or secrets.
