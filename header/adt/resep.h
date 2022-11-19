/* File: resep.h */
/* Definisi ADT resep */

#ifndef RESEP_H
#define RESEP_H

#include "node.h"
#include "tree.h"
#include "foodlist.h"

#include "simulator.h"

/*  Kamus Umum */
#define CAPACITY 100
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
/* Nilai elemen tak terdefinisi*/


typedef Tree Resep;
typedef struct
{
    Resep buffer[CAPACITY];
} ResepList;

/* SELEKTOR */
//return Resep
#define ResepListElmt(rl, i) (rl).buffer[(i)]

/*
* Mengembalikan panjang resepList
*/
int resepListLength(ResepList rl);

/* ***  CONSTRUCTOR *** */

/*
* Melakukan Construct pada Resep
*/
void CreateResep(Resep* r, Tree t);

/*
* Melakukan Construct pada ResepList
*/
void CreateResepList(ResepList* rl);

/* ***  FUNCTIONS *** */
/*
* Eksekusi COMMAND COOKBOOK pada program
*/
void printCookbook(ResepList rl, FoodList fl);

/*
* Melakukan cek apakah program bisa membuat makanan berdasarkan resep
*/
boolean canMakeFromResep(Resep r, Simulator s);

/*
* Melakukan cek apakah resep terdaftar pada list
*/
boolean hasResep(ResepList rl, Food f); 

/*
* Mencari resep yang tepat berdasarkan masukan contoh food
*/
boolean getResepWithFood(Resep* resep, ResepList rl, Food f);



#endif