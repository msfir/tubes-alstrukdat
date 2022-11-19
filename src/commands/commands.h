#include "adt.h"

extern Matrix map;
extern ResepList resepList;
extern FoodList foodlist;
extern Time program_time;
extern Simulator simulator;
extern Queue notifications;
extern PriorityQueue delivery_list;
extern Fridge fridge;
extern Stack undoS, redoS;

void add_program_time(int minute);
void execute_rekomendasi();
boolean execute_buy();
boolean execute_mix();
boolean execute_move(String arah);
boolean execute_fry();
boolean execute_chop();
boolean execute_boil();
boolean execute_fridge();
boolean execute_wait(int jam, int menit);
void execute_undo(infoState temp);
void execute_redo(infoState temp);
