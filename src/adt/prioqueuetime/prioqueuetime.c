#include <stdio.h>
#include <stdlib.h>

#include "adt.h"

/* *** Konstruktor *** */
void CreatePrioQueue(PriorityQueue *pq, int CAPACITY_INVENTORY) {
    /* I.S. pq sembarang, CAPACITY_INVENTORY > 0 */
    /* F.S. Terbentuk pq kosong dengan kapasitas CAPACITY_INVENTORY */
    /* - Index head bernilai IDX_UNDEF */
    /* - Index tail bernilai IDX_UNDEF */
    /* Proses : Melakukan alokasi, membuat sebuah pq kosong */
    BUFFER_INVENTORY(*pq) = (PQInfo *)malloc(CAPACITY_INVENTORY * sizeof(PQInfo));
    PQ_IDX_HEAD(*pq) = IDX_UNDEF;
    PQ_IDX_TAIL(*pq) = IDX_UNDEF;
    CAP_PRIOQUEUE(*pq) = CAPACITY_INVENTORY;
}

void dealocatePrioQueue(PriorityQueue *pq) {
    /* I.S. pq terdefinisi */
    /* F.S. pq dikembalikan ke system, idxHead = IDX_UNDEF, idxTail = IDX_UNDEF */
    free(BUFFER_INVENTORY(*pq));
    PQ_IDX_HEAD(*pq) = IDX_UNDEF;
    PQ_IDX_TAIL(*pq) = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmptyPrioQueue(PriorityQueue pq) {
    /* Mengirim true jika pq kosong: lihat definisi di atas */
    return ((PQ_IDX_HEAD(pq) == IDX_UNDEF) && (PQ_IDX_TAIL(pq) == IDX_UNDEF));
}

boolean isFullPrioQueue(PriorityQueue pq) {
    /* Mengirim true jika tabel penampung elemen pq sudah penuh */
    /* yaitu jika index head bernilai 0 dan index tail bernilai PQ_CAPACITY-1 */
    return (lengthPrioQueue(pq) == CAP_PRIOQUEUE(pq));
}

int lengthPrioQueue(PriorityQueue pq) {
    /* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
    if (isEmptyPrioQueue(pq)) {
        return 0;
    } else {
        return (PQ_IDX_TAIL(pq) - PQ_IDX_HEAD(pq) + 1);
    }
}

void enqueuePrioQueue(PriorityQueue *pq, PQInfo val) {
    /* Proses: Menambahkan val pada pq dengan aturan FIFO */
    /* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
    /* F.S. val menjadi PQ_TAIL yang baru, PQ_IDX_TAIL "mundur".
            Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
            menjadi rata kiri untuk membuat ruang kosong bagi PQ_TAIL baru  */
    PQInfo t;
    boolean found;

    if (isEmptyPrioQueue(*pq)) {  // Kondisi kalau kosong
        PQ_IDX_HEAD(*pq) = 0;
        PQ_IDX_TAIL(*pq) = 0;
        PQ_TAIL(*pq) = val;
    } else {
        // Pindahkan seluruhnya ke paling kiri
        if (PQ_IDX_TAIL(*pq) == (CAP_PRIOQUEUE(*pq) - 1)) {
            for (int i = PQ_IDX_HEAD(*pq); i <= PQ_IDX_TAIL(*pq); i++) {
                pq->buffer[i - PQ_IDX_HEAD(*pq)] = pq->buffer[i];
            }
            PQ_IDX_TAIL(*pq) -= PQ_IDX_HEAD(*pq);
            PQ_IDX_HEAD(*pq) = 0;
        }
        PQ_IDX_TAIL(*pq)++;  // Menambahkan index tail
        // insertion sort
        found = false;
        for (int i = PQ_IDX_HEAD(*pq); i < PQ_IDX_TAIL(*pq); i++) {
            t = (*pq).buffer[i];
            if (TIMEToMenit(val.time) < TIMEToMenit(t.time)) {
                for (int j = PQ_IDX_TAIL(*pq) - 1; j >= i; j--) {
                    (*pq).buffer[j + 1] = (*pq).buffer[j];
                }
                (*pq).buffer[i] = val;
                found = true;
                break;
            }
        }
        if (!found) {
            PQ_TAIL(*pq) = val;
        }
    }
}

void dequeuePrioQueue(PriorityQueue *pq, Food *val) {
    /* Proses: Menghapus val pada pq dengan aturan FIFO */
    /* I.S. pq tidak mungkin kosong */
    /* F.S. val = nilai elemen PQ_HEAD. PQ_HEAD dan PQ_IDX_HEAD "mundur";
            pq mungkin kosong */
    *val = PQ_HEAD(*pq).food;
    if (PQ_IDX_HEAD(*pq) == PQ_IDX_TAIL(*pq)) {
        PQ_IDX_HEAD(*pq) = IDX_UNDEF;
        PQ_IDX_TAIL(*pq) = IDX_UNDEF;
    } else {
        PQ_IDX_HEAD(*pq)++;
    }
}

void displayPrioqueue(PriorityQueue pq) {
    /* Display inventory yang ada */
    if (isEmptyPrioQueue(pq)) {
        printf("Tidak ada makanan\n");
    } else {
        int i, j = 0;
        for (i = 0; i < lengthPrioQueue(pq); i++) {
            j++;
            PQInfo info = getElmtAtIdxPrioqueue(pq, i);
            printf("%d. %s - ", j, STR_VALUE(Name(info.food)));
            TulisFoodTIME(info.time);
            printf("\n");
        }
    }
}

void removeAtPrioqueue(PriorityQueue *pq, int idx, Food *val) {
    if (idx != IDX_UNDEF) {
        *val = getElmtAtIdxPrioqueue(*pq, idx).food;
        for (int i = idx; i < lengthPrioQueue(*pq) - 1; i++) {
            ELMTQUEUE(*pq, i + pq->idxHead) = ELMTQUEUE(*pq, i + 1 + pq->idxHead);
        }
        if (lengthPrioQueue(*pq) == 1) {
            pq->idxHead = pq->idxTail = IDX_UNDEF;
        } else {
            PQ_IDX_TAIL(*pq)--;
        }
    }
}

PQInfo getElmtAtIdxPrioqueue(PriorityQueue pq, int idx) {
    return pq.buffer[pq.idxHead + idx];
}

// khusus food
int getFirstFoundFoodPrioqueue(PriorityQueue pq, int foodid) {
    for (int i = 0; i < lengthPrioQueue(pq); i++) {
        if (Id(getElmtAtIdxPrioqueue(pq, i).food) == foodid) {
            return i;
        }
    }

    return IDX_UNDEF;
}

boolean isInPrioqueue(PriorityQueue pq, int foodId) {
    int i;
    boolean found = false;
    for (i = 0; i < lengthPrioQueue(pq); i++) {
        if (Id(getElmtAtIdxPrioqueue(pq, i).food) == foodId) {
            found = true;
        }
    }

    return found;
}

void deepcopyPrioQueue(PriorityQueue *dest, PriorityQueue src) {
    CreatePrioQueue(dest, CAP_PRIOQUEUE(src));

    if (BUFFER_INVENTORY(*dest) != NULL) {
        Food temp;
        for (int i = src.idxHead; i <= src.idxTail; i++) {
            enqueuePrioQueue(dest, ELMTQUEUE(src, i));
        }
    }
}
