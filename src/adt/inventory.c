#include <stdio.h>
#include "inventory.h"

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq) {
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */
    PQ_IDX_HEAD(*pq) = PQ_IDX_TAIL(*pq) = IDX_UNDEF;
}

boolean isEmptyQueue(PrioQueue pq) {
/* Mengirim true jika pq kosong: lihat definisi di atas */
    return (PQ_IDX_HEAD(pq) == IDX_UNDEF && PQ_IDX_TAIL(pq) == IDX_UNDEF);
}

boolean isFullQueue(PrioQueue pq) {
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai PQ_CAPACITY-1 */
    return (PQ_IDX_HEAD(pq) == 0 && PQ_IDX_TAIL(pq) == PQ_CAPACITY - 1);
}

int lengthQueue(PrioQueue pq) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
    if (isEmptyQueue(pq)) {
        return 0;
    } else {
        return (PQ_IDX_TAIL(pq) - PQ_IDX_HEAD(pq) + 1);
    }
}

/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElTypeQueue val) {
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi PQ_TAIL yang baru, PQ_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi PQ_TAIL baru  */
    int i, j;
    ElTypeQueue t;
    boolean found;
    if (isEmptyQueue(*pq)) { // Add casually if empty
        PQ_IDX_HEAD(*pq) = PQ_IDX_TAIL(*pq) = 0;
        PQ_TAIL(*pq) = val;
    } else { // Do insertion sort based on score and time
        // Move everything to the left
        if (PQ_IDX_TAIL(*pq) == PQ_CAPACITY - 1) {
            for (i = PQ_IDX_HEAD(*pq); i <= PQ_IDX_TAIL(*pq); i++) {
                (*pq).buffer[i-PQ_IDX_HEAD(*pq)] = (*pq).buffer[i];
            }
            PQ_IDX_TAIL(*pq) -= PQ_IDX_HEAD(*pq);
            PQ_IDX_HEAD(*pq) = 0;
        }
        // Add tail to element addition
        PQ_IDX_TAIL(*pq)++;
        // Insertion sort, we only care about current val because
        // guaranteed element was sorted already (O(N))
        found = false;
        for (i = PQ_IDX_HEAD(*pq); i < PQ_IDX_TAIL(*pq); i++) {
            t = (*pq).buffer[i];
            if (val->timePickUp < t->timePickUp) { // If i score < current score
                for (j = PQ_IDX_TAIL(*pq) - 1; j >= i; j--) { // move everything to right
                    (*pq).buffer[j+1] = (*pq).buffer[j];
                }
                (*pq).buffer[i] = val; // Assign val
                found = true;
                break;
            }
        }
        if (!found) { // If not found, set Tail to val
            PQ_TAIL(*pq) = val;
        }
    }
}

void dequeue(PrioQueue * pq, ElTypeQueue *val) {
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen PQ_HEAD pd
I.S., PQ_HEAD dan PQ_IDX_HEAD "mundur"; 
        pq mungkin kosong */
    *val = PQ_HEAD(*pq);
    if (PQ_IDX_HEAD(*pq) == PQ_IDX_TAIL(*pq)) {
        PQ_IDX_HEAD(*pq) = PQ_IDX_TAIL(*pq) = IDX_UNDEF; // Set empty
    } else {
        PQ_IDX_HEAD(*pq)++; // Move head
    }
}

void displayQueue(PrioQueue q) {
    if (!isEmptyQueue(q)) {
        int i;
        printf("List Makanan di Inventory");
        printf("(nama - waktu sisa kedaluwarsa)");
        for (i = PQ_IDX_HEAD(q); i <= PQ_IDX_TAIL(q); i++) {
            printf("%d %c %c %c\n",
                q.buffer[i]->NAME,
                q.buffer[i]->pickUp->letter,
                q.buffer[i]->dropOff->letter,
                q.buffer[i]->type
            );
        }
    }
}