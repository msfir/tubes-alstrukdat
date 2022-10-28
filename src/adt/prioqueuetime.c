#include <stdio.h>
#include "../boolean.h"
#include "prioqueuetime.h"

/* ********* Prototype ********* */
boolean IsEmpty(PrioQueueTime Q){
/* Mengirim true jika Q kosong: lihat definisi di atas */
   return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}

boolean IsFull(PrioQueueTime Q){
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
   if (HEAD(Q) != 0) {
      return (TAIL(Q) == (HEAD(Q) - 1));
   } else {
      return (TAIL(Q) == (MaxEl(Q) - 1));
   }
}

int NBElmt(PrioQueueTime Q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
   if (IsEmpty(Q)) {
      return 0;
   } else {
      
   }
}

/* *** Kreator *** */
void MakeEmpty(PrioQueueTime* Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime* Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue(PrioQueueTime* Q, infotype X);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar
 * berdasarkan time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void Dequeue(PrioQueueTime* Q, infotype* X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular
   buffer; Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueueTime(PrioQueueTime Q);
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/


