#include "commands.h"

boolean execute_wait(int jam, int menit) {
    int deltaTime = 60 * jam + menit;

    if (deltaTime > 0 && jam >= 0 && menit >= 0) {
        add_program_time(deltaTime);
        return true;
    }

    return false;
}
