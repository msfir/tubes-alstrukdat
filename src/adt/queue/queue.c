#include <stdio.h>

#include "adt.h"
#include "boolean.h"

/* *** Kreator *** */
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */
void CreateQueue(Queue *q) {
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}

/* ********* Prototype ********* */
/* Mengirim true jika q kosong: lihat definisi di atas */
boolean isEmptyQueue(Queue q) {
    return IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF;
}
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu IDX_TAIL akan selalu di belakang IDX_HEAD dalam buffer melingkar*/
boolean isFullQueue(Queue q) {
    return (IDX_TAIL(q) + 1) % CAPACITY == IDX_HEAD(q);
}

/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
int queueLength(Queue q) {
    if (isEmptyQueue(q)) {
        return 0;
    } else if (IDX_HEAD(q) <= IDX_TAIL(q)) {
        return IDX_TAIL(q) - IDX_HEAD(q) + 1;
    } else {
        return CAPACITY - IDX_HEAD(q) + IDX_TAIL(q) + 1;
    }
}

/* *** Primitif Add/Delete *** */
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur" dalam buffer melingkar. */
void enqueue(Queue *q, String val) {
    if (isEmptyQueue(*q)) {
        IDX_HEAD(*q) = IDX_TAIL(*q) = 0;
        HEAD(*q) = val;
    } else {
        IDX_TAIL(*q) = (IDX_TAIL(*q) + 1) % CAPACITY;
        TAIL(*q) = val;
    }
}

/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., IDX_HEAD "mundur";
        q mungkin kosong */
void dequeue(Queue *q, String *val) {
    *val = HEAD(*q);
    if (IDX_TAIL(*q) == IDX_HEAD(*q)) {
        IDX_HEAD(*q) = IDX_UNDEF;
        IDX_TAIL(*q) = IDX_UNDEF;
    } else {
        IDX_HEAD(*q) = (IDX_HEAD(*q) + 1) % CAPACITY;
    }
}

/* *** Display Queue *** */
/* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara
   kurung siku; antara dua elemen dipisahkan dengan separator "koma", tanpa
   tambahan karakter di depan, di tengah, atau di belakang, termasuk spasi dan
   enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */
void displayQueue(Queue q) {
    printf("[");
    for (int i = 0; i < queueLength(q); i++) {
        if (i > 0)
            printf(",");
        printf("%s", STR_VALUE(q.buffer[(IDX_HEAD(q) + i) % CAPACITY]));
    }
    printf("]\n");
}
