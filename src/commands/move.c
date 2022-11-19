#include "commands.h"
#include "logger.h"

boolean execute_move(String arah) {
    printf("\n");
    Point temp = Location(simulator);
    if (is_string_equal(arah, StringFrom("NORTH"))) {
        SimulatorMove(&simulator, Location(simulator), &map, -1, 0);
        if (!EQ(temp, Location(simulator))) {
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("EAST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, 1);
        if (!EQ(temp, Location(simulator))) {
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("SOUTH"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 1, 0);
        if (!EQ(temp, Location(simulator))) {
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("WEST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, -1);
        if (!EQ(temp, Location(simulator))) {
            add_program_time(1);
            return true;
        }
    } else {
        log_error("Command tidak valid.\n");
    }

    return false;
}
