#include "commands.h"

void execute_undo(infoState temp) {
    Point prev_loc = simulator.location;

    PriorityQueue inv = simulator.inventory;
    PriorityQueue deliv = delivery_list;

    // dealocatePrioQueue(&Inventory(simulator));

    simulator = ElmtSimulator(temp);

    float deltaX = Absis(simulator.location) - Absis(prev_loc);
    float deltaY = Ordinat(simulator.location) - Ordinat(prev_loc);
    SimulatorMove(&simulator, prev_loc, &map, deltaX, deltaY);
    delivery_list = ElmtDelivery(temp);
    program_time = ElmtTime(temp);
    fridge = temp.fridge;

    dealocatePrioQueue(&inv);
    dealocatePrioQueue(&deliv);
}
