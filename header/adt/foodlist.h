/* File: foodlist.h */
/* Definisi ADT List Statik Makanan */
#ifndef FOODLIST_H
#define FOODLIST_H

#include <stdio.h>
#include "food.h"
#include "boolean.h"
#include "time.h"
#include "cstring.h"

/*  Kamus Umum */
#define CAPACITY 100
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK -9999
/* Nilai elemen tak terdefinisi*/

/* DEFINISI */
typedef struct {
    Food buffer[CAPACITY];  // Makanan diurutkan berdasarkan ID secara ascending
} FoodList;

/* SELEKTOR */
#define ELMT(L, i) (L).buffer[(i)]
// #define NEFF(L) (L).NEFF

/* **************KONSTRUKTOR************** */
void CreateFoodList (FoodList *L);
/* I.S L sembarang */
/* F.S Terbentuk list L kosong dengan kapasitas CAPACITY */

/* **************SELEKTOR TAMBAHAN************** */
/* *** Banyaknya elemen *** */
int listLength(ListStatik l);
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  
int getFirstIdx (FoodList L);
/* Menghasilkan indeks pertama elemen list L, jika L kosong menghasilkan IDX_UNDEF */

int getLastIdx (FoodList L);
/* Menghasilkan indeks elemen terakhir list L, jika L kosong menghasilkan IDX_UNDEF */

/* **************PRIMITIF LAIN************** */
boolean isEmptyFood (FoodList L);
/* Menghasilkan True jika L kosong. False jika tidak */
boolean isFullFood (FoodList L);
/* Menghasilkan True jika L penuh. False jika tidak */

void addFood (FoodList *L, Food M);
/* I.S L terdefinisi dan tidak penuh. M terdefinisi */
/* F.S Menambahkan M sebagai elemen terakhir list L. NEFF L bertambah 1 */

/* **************PRIMITIF LAIN UNTUK LIST BAHAN MAKANAN************** */
void printBuyList (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dibeli beserta waktu delivery-nya. L tidak berubah */

void printFryList (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa digoreng. L tidak berubah */

void printMixList (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dimix. L tidak berubah */

void printBoilList (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa direbus. L tidak berubah */

void printChopList (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dipotong. L tidak berubah */

void printCatalog (FoodList L);
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan, waktu kadaluwarsa, aksi yang bisa dilakukan, dan waktu delivery */

Food getFoodWithIdxAction (FoodList L, char action, int idx);
/* Mengembalikan elemen Makanan ke-idx pada List yang memiliki elemen lokasiAksi = lokasiAksi */

#endif