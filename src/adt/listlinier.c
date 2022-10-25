// SEMENTARAAAAAA, NTAR KUDU GANTI!

#include <stdio.h>
#include <stdlib.h>

#include "listlinier.h"


Address newNode(ElType val){
    Address res = (Address) malloc(sizeof(Node));

    if(res != NULL){
        INFO(res) = val;
        NEXT(res) = NULL;
    }

    return res;
}

void CreateList(List *l){
    FIRST(*l) = NULL;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */


boolean isEmpty(List l){
    return (FIRST(l) == NULL);
}
/* Mengirim true jika list kosong */

ElType getElmt(List l, int idx){
    Address curAddr = l;
    int cur = 0;

    while (cur < idx)
    {
        curAddr = NEXT(curAddr);
        cur++;
    }
    
    return INFO(curAddr);
}
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */


void setElmt(List *l, int idx, ElType val){
    Address curAddr = *l;
    int cur = 0;

    while (cur < idx)
    {
        curAddr = NEXT(curAddr);
        cur++;
    }

    INFO(curAddr) = val;

}
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOf(List l, ElType val){
    int idx = 0;
    Address curAddr = l;
    boolean found = false;

    while (idx < length(l) && !found)
    {
        if(getElmt(l, idx) == val){
            found = true;
        }
        else{
            idx++;
        }
    }

    if(found){
        return idx;
    } 
    else{
        return IDX_UNDEF;
    }
}
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */




void insertFirst(List *l, ElType val){
    insertAt(l, val, 0);
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLast(List *l, ElType val){
    if(isEmpty(*l)){
        insertAt(l, val, 0);
    } else{
        
        insertAt(l, val, length(*l));
    }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */


void insertAt(List *l, ElType val, int idx){
    if (idx == 0)
    {
        Address newAddr = newNode(val);
        NEXT(newAddr) = *l;
        *l = newAddr;
    }
    else
    {
        int cnt = 0;
        Address curAddr = *l;

        while (cnt < idx-1)
        {
            curAddr = NEXT(curAddr);
            cnt++;
        }

        Address newL = newNode(val);

        NEXT(newL) = NEXT(curAddr);
        NEXT(curAddr) = newL;
    }
}
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */




void deleteFirst(List *l, ElType *val){
    deleteAt(l, 0, val);
}
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */


void deleteLast(List *l, ElType *val){
    deleteAt(l, length(*l)-1, val);
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */

void deleteAt(List *l, int idx, ElType *val){
    if (idx == 0)
    {
        Address currAddr = *l;
        *val = INFO(currAddr);
        *l = NEXT(currAddr);

        free(currAddr);
    }
    else
    {
        int cnt = 0;
        Address curAddr = *l;
        
        while (cnt < idx-1)
        {
            curAddr = NEXT(curAddr);
            cnt++;
        }
        
        Address nextAddr = NEXT(curAddr);        
        *val = INFO(nextAddr);
        NEXT(curAddr) = NEXT(nextAddr);        
        free(nextAddr);

    }
}
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */


void displayList(List l){
    printf("[");

    if(!isEmpty(l)){
        Address curAddr = l;
        while(NEXT(curAddr) != NULL){
            printf("%d,", INFO(curAddr));    
            curAddr = NEXT(curAddr);
        }
        printf("%d", INFO(curAddr));
    }
    

    printf("]");
}
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */


int length(List l){
    int result = 0;

    if(!isEmpty(l)){
        Address currAddr = l;

        result = 1;

        while (NEXT(currAddr) != NULL)
        {
            result++;
            currAddr = NEXT(currAddr);
        }
        
    }

    return result;
}
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */


List concat(List l1, List l2){
    List l3; CreateList(&l3);
    Address curAddr;

    curAddr = l1;
    while (curAddr != NULL)
    {
        insertLast(&l3, INFO(curAddr));
        curAddr = NEXT(curAddr);
    }
    
    curAddr = l2;
    while (curAddr != NULL)
    {
        insertLast(&l3, INFO(curAddr));
        curAddr = NEXT(curAddr);
    }
    
    return l3;
}
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */