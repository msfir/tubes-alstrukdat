/* File: resep.h */
/* Definisi ADT resep */

#ifndef RESEP_H
#define RESEP_H

#include "node.h"
#include "tree.h"

#include "simulator.h"

/*  Kamus Umum */
#define CAPACITY 100
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK -9999
/* Nilai elemen tak terdefinisi*/


typedef Tree Resep;
typedef struct
{
    Resep buffer[CAPACITY];
} ResepList;

/* SELEKTOR */
//return Resep
#define ResepListElmt(rl, i) (rl).buffer[(i)]

Resep undefinedResep(); // MARK Resep

int resepListLength(ResepList rl);

void CreateResep(Resep* r, Tree t);

void CreateResepList(ResepList* rl);

boolean canMakeFromResep(Resep r, Simulator s); //or inventory?
// watch for children that still has resep
// this will NOT recurse

// make another function that will recurse to its child!



// is this particular food has a resep in reseplist or not
boolean hasResep(ResepList rl, Food f); 

boolean getResepWithFood(Resep* resep, ResepList rl, Food f);

#endif