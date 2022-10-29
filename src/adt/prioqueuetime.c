#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "prioqueuetime.h"

/* *** Konstruktor *** */
void CreateInventory(Inventory *pq, int CAPACITY_INVENTORY){
/* I.S. pq sembarang, CAPACITY_INVENTORY > 0 */
/* F.S. Terbentuk pq kosong dengan kapasitas CAPACITY_INVENTORY */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */
   BUFFER_INVENTORY(*pq) = (ElTypeQueue *) malloc (CAPACITY_INVENTORY * sizeof(ElTypeQueue));
   PQ_IDX_HEAD(*pq) = IDX_UNDEF;
   PQ_IDX_TAIL(*pq) = IDX_UNDEF;
   CAP_INVENTORY(*pq) = CAPACITY_INVENTORY;
}

void dealocateINVENTORY(Inventory *pq){
/* I.S. pq terdefinisi */
/* F.S. pq dikembalikan ke system, idxHead = IDX_UNDEF, idxTail = IDX_UNDEF */
   free(BUFFER_INVENTORY(*pq));
   PQ_IDX_HEAD(*pq) = IDX_UNDEF;
   PQ_IDX_TAIL(*pq) = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmptyINVENTORY(Inventory pq){
/* Mengirim true jika pq kosong: lihat definisi di atas */
   return ((PQ_IDX_HEAD(pq) == IDX_UNDEF) && (PQ_IDX_TAIL(pq) == IDX_UNDEF));
}

boolean isFullINVENTORY(Inventory pq){
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai PQ_CAPACITY-1 */
   return (lengthINVENTORY(pq) == CAP_INVENTORY(pq));
}

int lengthINVENTORY(Inventory pq){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
   if (isEmptyINVENTORY(pq)) {
      return 0;
   } else {
      return (PQ_IDX_TAIL(pq) - PQ_IDX_HEAD(pq) + 1);
   }
}

void enqueueINVENTORY(Inventory *pq, ElTypeQueue val){
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi PQ_TAIL yang baru, PQ_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi PQ_TAIL baru  */
   ElTypeQueue t;
   boolean found;
   
   if (isEmptyINVENTORY(*pq)) { // Kondisi kalau kosong
      PQ_IDX_HEAD(*pq) = 0;
      PQ_IDX_TAIL(*pq) = 0;
      PQ_TAIL(*pq) = val;
   } else {
      // Pindahkan seluruhnya ke paling kiri
      if (PQ_IDX_TAIL(*pq) == (CAP_INVENTORY(*pq) - 1)) {
         for (int i = PQ_IDX_HEAD(*pq); i <= PQ_IDX_TAIL(*pq); i++) {
            pq->bufferInventory[i - PQ_IDX_HEAD(*pq)] = pq->bufferInventory[i];
         }
         PQ_IDX_TAIL(*pq) -= PQ_IDX_HEAD(*pq);
         PQ_IDX_HEAD(*pq) = 0;
      }
      PQ_IDX_TAIL(*pq)++; // Menambahkan index tail
      // insertion sort
      found = false;
      for (int i = PQ_IDX_HEAD(*pq); i < PQ_IDX_TAIL(*pq); i++) {
         t = (*pq).bufferInventory[i];
         if (val->ExpirationTime < t->ExpirationTime) {
            for (int j = PQ_IDX_TAIL(*pq) - 1; j >= i; j--) {
               (*pq).bufferInventory[j+1] = (*pq).bufferInventory[j];
            }
            (*pq).bufferInventory[i] = val;
            found = true;
            break;
         }
      }
      if (!found) {
         PQ_TAIL(*pq) = val;
      }
   }
}

void dequeueINVENTORY(Inventory *pq, ElTypeQueue *val){
/* Proses: Menghapus val pada pq dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen PQ_HEAD. PQ_HEAD dan PQ_IDX_HEAD "mundur"; 
        pq mungkin kosong */
   *val = PQ_HEAD(*pq);
   if (PQ_IDX_HEAD(*pq) == PQ_IDX_TAIL(*pq)) {
      PQ_IDX_HEAD(*pq) = IDX_UNDEF;
      PQ_IDX_TAIL(*pq) = IDX_UNDEF;
   } else {
      PQ_IDX_HEAD(*pq)++;
   }
}

void displayInventory(Inventory pq){
/* Display inventory yang ada */
   if (isEmptyINVENTORY(pq)) {
      printf("Tidak ada makanan");
   } else {
      int i,j = 0;
      for (i = 0; i < lengthINVENTORY(pq); i++) {
         j++;
         printf("%d. %c - %c", j, NAME(ELMT(L, i)), ExpirationTime((ELMT(L, i))));
      }
   } 
}

