#include "../boolean.h"
#include "point.h"
#include "string.h"
#include "prioqueuetime.h"
#include "time.h"
// #include "simulator.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
<<<<<<< HEAD
void CreateSimulator(Simulator *x, String username, Point loc, Inventory inventory, Time second){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   copy_string(&Username(*x), username);
   Location(*x) = loc;
   Inventory(*x) = inventory;
   Time(*x) = second;
}
=======
// void CreateSimulator (Simulator *x, Point *p, Time *t){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   //Inventory i;
   // Time t;
   // Point p;
   //CreatePoint();
   //NewString();
   //CreatePoint();
   //CreateTime();
   //CreateNotification();
   //CreateInventory();
// }
>>>>>>> 5b4365b0f491fb6c3d01d5e9f84d622c73c8b3d3

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

