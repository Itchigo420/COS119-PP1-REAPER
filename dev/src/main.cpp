#include "TaskManager.h"
#include "UserInterface.h"

int main(int argc, char* argv[]) {
    TaskManager manager;
    const std::string taskFile = argc > 1 ? argv[1] : "reaper-tasks.txt";
    UserInterface ui(manager, taskFile);
    ui.run();
    return 0;
}
