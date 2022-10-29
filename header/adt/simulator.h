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
   Point location;
   Inventory inventory;
} Simulator;

/* *** Notasi Akses: selektor Simulator *** */
// clang-format off
#define Username(I)  (I).username
#define Location(I)  (I).location
#define Inventory(I) (I).inventory
#define Time(I) (I).time
// clang-format on

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, Point loc, Inventory inventory);
/* I.S. x sembarang
   F.S. x terdefinisi*/

void DisplaySimulator(Simulator x);
/* I.S. keterangan simulator sembarang
   F.S. Keterangan simulator muncul di layar*/

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator *x);
/* Mengirim true jika ada dinding di sekitar Simulator */

void SimulatorMove (Simulator *x, Point P, float deltaX, float deltaY);
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/

#endif