#include "../boolean.h"
#include "point.h"
#include "string.h"
#include "simulator.h"
#include "time.h"
// #include "simulator.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, POINT loc, Inventory inventory, Time second){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   copy_string(&Username(*x), username);
   Location(*x) = loc;
   Inventory(*x) = inventory;
   Time(*x) = second;
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow){
/* Mengirim true jika tidak ada dinding di sekitar Simulator */
   return (Absis(Location(x)) >= 0 &&  Absis(Location(x)) <= NCol) && (Ordinat(Location(x)) >= 0 && Ordinat(Location(x)) <= NRow);
}

void SimulatorMove (Simulator *x, POINT P, float deltaX, float deltaY){
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/
   Location(*x) = PlusDelta(P, deltaX, deltaY);
}

