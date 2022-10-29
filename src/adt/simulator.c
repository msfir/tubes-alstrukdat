#include "../boolean.h"
#include "point.h"
#include "string.h"
#include "prioqueuetime.h"
#include "time.h"
#include "simulator.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, Point loc, Inventory inventory){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   copy_string(&Username(*x), username);
   Location(*x) = loc;
   Inventory(*x) = inventory;
}

void DisplaySimulator(Simulator x) {
   printf("BNMO di posisi: "); TulisPOINT(Location(x));
   printf("Waktu: "); /*TulisTIME(Time T)*/; printf("\n");
   printf("Notifikasi: ");
}
/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator *x){
/* Mengirim true jika ada dinding di sekitar Simulator */
   return (PlusDelta(Location(*x), 1.0, 0.0) == '*') || (PlusDelta(Location(*x), -1.0, 0.0) == '*') || (PlusDelta(Location(*x), 0.0, 1.0) == '*') || (PlusDelta(Location(*x), 0.0, -1.0) == '*');
}

void SimulatorMove (Simulator *x, Point P, float deltaX, float deltaY){
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/
   Location(*x) = PlusDelta(P, deltaX, deltaY);
}

// void SimulatorCommand (Simulator *x, string command);
/* I.S. Simulator terdefinisi
   F.S. Simulator melakukan command dengan tipe data string*/
