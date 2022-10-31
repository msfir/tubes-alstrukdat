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
   String username;
   POINT location;
   Inventory inventory;
   Time time;
} Simulator;

/* *** Notasi Akses: selektor Simulator *** */
// clang-format off
#define Username(I)  (I).username
#define Location(I)  (I).location
#define Inventory(I) (I).inventory
#define Time(I) (I).time
// clang-format on

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, POINT location, Inventory inventory, Time time);
/* I.S. x sembarang
   F.S. x terdefinisi*/

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow);
/* Mengirim true jika ada dinding di sekitar Simulator */

void SimulatorMove (Simulator *x, POINT P, float deltaX, float deltaY);
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/

#endif
