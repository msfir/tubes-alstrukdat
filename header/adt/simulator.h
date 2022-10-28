/* File: makanan.h */
/* Definisi ADT Simulator */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../boolean.h"
#include "point.h"
#include "string.h"
#include "prioqueuetime.h"
#include "time.h"
// #include "notification.h"

/* *** Definisi TYPE Simulator *** */
typedef struct {
    string username[0xff];
    Time time;
    Point location;
    PrioQueueTime inventory;
} Simulator;

/* *** Notasi Akses: selektor Simulator *** */
// clang-format off
#define Username(I)  (I).username
#define Location(I)  (I).location
#define Inventory(I) (I).inventory
#define Time(I) (I).time
// clang-format on

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator (Simulator *x);
/* I.S. x sembarang
   F.S. x terdefinisi*/

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

#endif