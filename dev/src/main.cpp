#include "TaskManager.h"
#include "UserInterface.h"

int main() {
    TaskManager manager;
    UserInterface ui(manager);
    ui.run();
    return 0;
}
