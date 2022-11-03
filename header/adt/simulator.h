/* File: simulator.h */
/* Definisi ADT Simulator */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "boolean.h"
#include "point.h"
#include "prioqueuetime.h"
#include "time.h"
#include "cstring.h"

#include "matrix.h"

/* *** Definisi TYPE Simulator *** */
typedef struct {
   String username;
   Point location;
   PriorityQueue inventory;
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
void CreateSimulator(Simulator *x, String username, Point location);
/* I.S. x sembarang
   F.S. x terdefinisi*/

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow);
/* Mengirim true jika ada dinding di sekitar Simulator */

void SimulatorMove (Simulator *x, Point P, Matrix* map, float deltaX, float deltaY);
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/



////////////////////// TOLONG PINDAHIN NTAR
char getSymbol(Matrix map, Point P);

/*Mengembalikan true jika point P merupakan space kosong*/
boolean IsEmptySpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan tempat Buy*/
boolean IsBuySpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan tempat Mix*/
boolean IsMixSpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan tempat Boil*/
boolean IsBoilSpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan tempat Fry*/
boolean IsFrySpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan tempat Chop*/
boolean IsChopSpace(Matrix map, Point P);
/*Mengembalikan true jika di sekitar point P merupakan Refrigerator*/
boolean IsFridgeSpace(Matrix map, Point P);



#endif
