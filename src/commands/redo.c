#include "commands.h"

void execute_redo(infoState temp) {
    PriorityQueue inv = simulator.inventory;
    PriorityQueue deliv = delivery_list;
    Point prev_loc = simulator.location;
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
