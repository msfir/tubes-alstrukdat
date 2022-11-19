/* File: point.h */

#include <math.h>
#include <stdio.h>

#include "adt.h"
#include "boolean.h"

/* *** Notasi Akses: Selektor POINT *** */
#define Absis(P)   (P).X
#define Ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
void CreatePoint(Point *P, int X, int Y) {
    /* Membentuk sebuah POINT dari komponen-komponennya */
    Absis(*P) = X;
    Ordinat(*P) = Y;
}

void TulisPOINT(Point P) {
    /* Nilai P ditulis ke layar dengan format "(X,Y)"
       tanpa spasi, enter, atau karakter lain di depan, belakang,
       atau di antaranya
       Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
    */
    /* I.S. P terdefinisi */
    /* F.S. P tertulis di layar dengan format "(X,Y)" */
    printf("(%d,%d)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ(Point P1, Point P2) {
    /* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
    return ((Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ(Point P1, Point P2) {
    /* Mengirimkan true jika P1 tidak sama dengan P2 */
    return ((Absis(P1) != Absis(P2) || Ordinat(P1) != Ordinat(P2)));
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX(Point P) {
    /* Mengirim salinan P dengan absis ditambah satu */
    Point P2;

    CreatePoint(&P2, Absis(P) + 1, Ordinat(P));
    return P2;
}

Point NextY(Point P) {
    /* Mengirim salinan P dengan ordinat ditambah satu */
    Point P2;

    CreatePoint(&P2, Absis(P), Ordinat(P) + 1);
    return P2;
}

Point PlusDelta(Point P, int deltaX, int deltaY) {
    /* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
    Point P2;

    CreatePoint(&P2, Absis(P) + deltaX, Ordinat(P) + deltaY);
    return P2;
}

void Geser(Point *P, int deltaX, int deltaY) {
    /* I.S. P terdefinisi */
    /* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
