/* File: simulator.h */
/* Definisi ADT Simulator */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "boolean.h"
#include "point.h"
#include "prioqueuetime.h"
#include "time.h"
#include "cstring.h"

/* *** Definisi TYPE Simulator *** */
typedef struct {
<<<<<<< HEAD
   String username;
   Point location;
   Inventory inventory;
   Time time;
=======
    String username;
    POINT location;
    Inventory inventory;
>>>>>>> 5b4365b0f491fb6c3d01d5e9f84d622c73c8b3d3
} Simulator;

/* *** Notasi Akses: selektor Simulator *** */
// clang-format off
#define Username(I)  (I).username
#define Location(I)  (I).location
#define Inventory(I) (I).inventory
#define Time(I) (I).time
// clang-format on

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, Point location, Inventory inventory, Time time);
/* I.S. x sembarang
   F.S. x terdefinisi*/

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow);
/* Mengirim true jika ada dinding di sekitar Simulator */

void SimulatorMove (Simulator *x, Point P, float deltaX, float deltaY);
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/

<<<<<<< HEAD
#endif
=======
// void SimulatorCommand (Simulator *x, string command);
/* I.S. Simulator terdefinisi
   F.S. Simulator melakukan command dengan tipe data string*/

#endif
>>>>>>> 5b4365b0f491fb6c3d01d5e9f84d622c73c8b3d3
