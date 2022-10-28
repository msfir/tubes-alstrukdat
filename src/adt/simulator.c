#include "../boolean.h"
#include "point.h"
#include "string.h"
#include "prioqueuetime.h"
#include "time.h"
#include "simulator.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator (Simulator *x, Point *p, Time *t){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   //Inventory i;
   Time t;
   Point p;
   //CreatePoint();
   //NewString();
   //CreatePoint();
   //CreateTime();
   //CreateNotification();
   //CreateInventory();
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
// boolean IsTherePlace (Simulator *x);
/* Mengirim true jika ada tempat (M, T, F, C, B) di sekitar Simulator */

// boolean IsThereWall (Simulator *x);
/* Mengirim true jika ada dinding di sekitar Simulator */

// void SimulatorMove (Simulator *x, string direct);
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/

// void SimulatorCommand (Simulator *x, string command);
/* I.S. Simulator terdefinisi
   F.S. Simulator melakukan command dengan tipe data string*/
