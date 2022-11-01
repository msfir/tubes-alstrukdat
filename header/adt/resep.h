/* File: resep.h */
/* Definisi ADT resep */

#ifndef RESEP_H
#define RESEP_H

#include "node.h"
#include "tree.h"

/*  Kamus Umum */
#define CAPACITY 100
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK -9999
/* Nilai elemen tak terdefinisi*/

Resep undefinedResep(); // MARK Resep

typedef Tree Resep;
typedef struct
{
    Resep buffer[CAPACITY];
} ResepList;

/* SELEKTOR */
//return Resep
#define ResepListElmt(rl, i) (rl).buffer[(i)]

int resepListLength(ResepList rl);

void CreateResep(Resep* r, Tree t);

void CreateResepList(ResepList* rl);

boolean canResepMade(Resep r, FoodList fl); //or inventory?
// watch for children that still has resep
// this will recurse

// is this particular food has a resep in reseplist or not
boolean hasResep(ResepList rl, Food f); 



#endif