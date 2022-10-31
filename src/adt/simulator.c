#include "boolean.h"
#include "point.h"
#include "string.h"
#include "simulator.h"
#include "time.h"
#include "prioqueuetime.h"
// #include "simulator.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, Point loc){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   Username(*x) = username;
   Location(*x) = loc;
   CreatePrioQueue(&Inventory(*x), 100);
   CreateTime(&Time(*x), 0, 0, 0);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow){
/* Mengirim true jika tidak ada dinding di sekitar Simulator */
   return (Absis(Location(x)) >= 0 &&  Absis(Location(x)) <= NCol) && (Ordinat(Location(x)) >= 0 && Ordinat(Location(x)) <= NRow);
}

void SimulatorMove (Simulator *x, Point P, float deltaX, float deltaY){
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/
   Location(*x) = PlusDelta(P, deltaX, deltaY);
}

