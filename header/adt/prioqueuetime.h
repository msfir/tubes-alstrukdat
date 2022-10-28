/* File : prioqueuetime.h */
/* Definisi ADT Priority Queue Time dengan representasi array secara eksplisit
 * dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut membesar berdasarkan waktu kadaluwarsa makanan */

#ifndef prioqueuetime_H
#define prioqueuetime_H

#include <stdlib.h>
#include "boolean.h"
#include "food.h"

#define IDX_UNDEF -1

/* Konstanta */
#define PQ_CAPACITY TASK_CAP // Kl dinamis ini masih dipake?

/* Deklarasi ElTypeQueue */
typedef Food* ElTypeQueue; //bingung buat apa

/* Definisi PrioQueue */
typedef struct PrioQueue {
	ElTypeQueue buffer[PQ_CAPACITY];
	int idxHead;
	int idxTail;
} PrioQueueTime;

/* ********* AKSES (Selektor) ********* */
/* Jika pq adalah PrioQueue, maka akses elemen : */
#define PQ_IDX_HEAD(pq) (pq).idxHead
#define PQ_IDX_TAIL(pq) (pq).idxTail
#define     PQ_HEAD(pq) (pq).buffer[(pq).idxHead]
#define     PQ_TAIL(pq) (pq).buffer[(pq).idxTail]

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq);
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */

boolean isEmptyQueue(PrioQueue pq);
/* Mengirim true jika pq kosong: lihat definisi di atas */

boolean isFullQueue(PrioQueue pq);
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUE_CAPACITY-1 */

int lengthQueue(PrioQueue pq);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */

/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElTypeQueue val);
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi QUEUE_TAIL yang baru, QUEUE_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi QUEUE_TAIL baru  */

void dequeue(PrioQueue * pq, ElTypeQueue *val);
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen QUEUE_HEAD pd
I.S., QUEUE_HEAD dan QUEUE_IDX_HEAD "mundur"; 
        pq mungkin kosong */

void displayQueue(PrioQueue q);

#endif
