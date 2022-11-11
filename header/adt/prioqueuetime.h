/* File : prioqueuetime.h */
/* Definisi ADT INVENTORY dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan rata kiri*/
/* Elemen queue terurut membesar berdasarkan waktu kadaluwarsa makanan */

#ifndef prioqueuetime_H
#define prioqueuetime_H

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "foodlist.h"

#define IDX_UNDEF -1
#define VAL_UNDEF -999

/* Deklarasi ElTypeQueue */
typedef struct {
    Food food;
    Time time;
} PQInfo;

/* Definisi PrioQueueTime (Dinamis) */
typedef struct PrioQueue {
    PQInfo *buffer;
    int idxHead;
    int idxTail;
    int capacity;
} PriorityQueue;

/* ********* Selektor ********* */
/* Jika pq adalah PrioQueue, maka akses elemen : */
#define ELMTQUEUE(pq, i)     (pq).buffer[i]
#define PQ_IDX_HEAD(pq)      (pq).idxHead
#define PQ_IDX_TAIL(pq)      (pq).idxTail
#define PQ_HEAD(pq)          (pq).buffer[(pq).idxHead]
#define PQ_TAIL(pq)          (pq).buffer[(pq).idxTail]
#define CAP_PRIOQUEUE(pq)    (pq).capacity
#define BUFFER_INVENTORY(pq) (pq).buffer

/* *** Konstruktor *** */
void CreatePrioQueue(PriorityQueue *pq, int capacity);
/* I.S. pq sembarang, CAPACITY_INVENTORY > 0 */
/* F.S. Terbentuk pq kosong dengan kapasitas CAPACITY_INVENTORY */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */

void dealocatePrioQueue(PriorityQueue *pq);
/* I.S. pq terdefinisi */
/* F.S. pq dikembalikan ke system, idxHead = IDX_UNDEF, idxTail = IDX_UNDEF */

boolean isEmptyPrioQueue(PriorityQueue pq);
/* Mengirim true jika pq kosong: lihat definisi di atas */

boolean isFullPrioQueue(PriorityQueue pq);
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai PQ_CAPACITY-1 */

int lengthPrioQueue(PriorityQueue pq);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */

/*** Primitif Add/Delete ***/
void enqueuePrioQueue(PriorityQueue *pq, PQInfo val);
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi PQ_TAIL yang baru, PQ_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi PQ_TAIL baru  */

void dequeuePrioQueue(PriorityQueue *pq, Food *val);
/* Proses: Menghapus val pada pq dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen PQ_HEAD. PQ_HEAD dan PQ_IDX_HEAD "mundur";
        pq mungkin kosong */

void displayPrioqueue(PriorityQueue pq);
/* Display inventory yang ada */

/*
 * Menghapus elemen dari buffer pada indeks idx
 */
void removeAtPrioqueue(PriorityQueue *pq, int idx, Food *val);

/* 
 * Mendapatkan elemen queue pada indeks ke-idx relatif terhadap idxHead
 */
PQInfo getElmtAtIdxPrioqueue(PriorityQueue pq, int idx);

/*
 * Menghapus elemen dari buffer pada indeks idx
 */
int getFirstFoundFoodPrioqueue(PriorityQueue pq, int foodid);


/*
 * Apakah elemen yang mengandung foodid ada di prioqueue
 */
boolean isInPrioqueue(PriorityQueue pq, int foodId);


/*
 * Apakah elemen yang mengandung foodid ada di prioqueue
 */
void deepcopyPrioQueue(PriorityQueue *dest, PriorityQueue src);

#endif
