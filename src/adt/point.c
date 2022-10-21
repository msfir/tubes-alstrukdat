#include "boolean.h"
#include "adt/point.h"
#include <stdio.h>
#include <math.h>

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
void CreatePoint(Point *P, float X, float Y)
{
    /* Membentuk sebuah Point dari komponen-komponennya */
    Absis(*P) = X;
    Ordinat(*P) = Y;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT(Point *P)
{
    /* Membaca nilai absis dan ordinat dari keyboard dan membentuk
       Point P berdasarkan dari nilai absis dan ordinat tersebut */
    /* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
    /* Contoh: 1 2
       akan membentuk Point <1,2> */
    /* I.S. Sembarang */
    /* F.S. P terdefinisi */
    float x, y;
    scanf("%f %f", &x, &y);
    CreatePoint(P, x, y);
}
void TulisPOINT(Point P)
{
    /* Nilai P ditulis ke layar dengan format "(X,Y)"
       tanpa spasi, enter, atau karakter lain di depan, belakang,
       atau di antaranya
       Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
    */
    /* I.S. P terdefinisi */
    /* F.S. P tertulis di layar dengan format "(X,Y)" */
    printf("(%.2f,%.2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ(Point P1, Point P2)
{
    /* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
    return (Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2));
}
boolean NEQ(Point P1, Point P2)
{
    /* Mengirimkan true jika P1 tidak sama dengan P2 */
    return (Absis(P1) != Absis(P2)) || (Ordinat(P1) != Ordinat(P2));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin(Point P)
{
    /* Menghasilkan true jika P adalah titik origin */
    return (Absis(P) == 0) && (Ordinat(P) == 0);
}
boolean IsOnSbX(Point P)
{
    /* Menghasilkan true jika P terletak Pada sumbu X */
    return Ordinat(P) == 0;
}
boolean IsOnSbY(Point P)
{
    /* Menghasilkan true jika P terletak pada sumbu Y */
    return Absis(P) == 0;
}
int Kuadran(Point P)
{
    /* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
    /* Prekondisi : P bukan titik origin, */
    /*              dan P tidak terletak di salah satu sumbu */
    if (Absis(P) > 0 && Ordinat(P) > 0)
    {
        return 1;
    }
    else if (Absis(P) < 0 && Ordinat(P) > 0)
    {
        return 2;
    }
    else if (Absis(P) < 0 && Ordinat(P) < 0)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX(Point P)
{
    /* Mengirim salinan P dengan absis ditambah satu */
    Point P1;
    CreatePoint(&P1, Absis(P) + 1, Ordinat(P));
    return P1;
}
Point NextY(Point P)
{
    /* Mengirim salinan P dengan ordinat ditambah satu */
    Point P1;
    CreatePoint(&P1, Absis(P), Ordinat(P) + 1);
    return P1;
}
Point PlusDelta(Point P, float deltaX, float deltaY)
{
    /* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
    Point P1;
    CreatePoint(&P1, Absis(P) + deltaX, Ordinat(P) + deltaY);
    return P1;
}
Point MirrorOf(Point P, boolean SbX)
{
    /* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
    /* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
    /* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
    Point P1;
    if (SbX)
    {
        CreatePoint(&P1, Absis(P), -Ordinat(P));
    }
    else
    {
        CreatePoint(&P1, -Absis(P), Ordinat(P));
    }
    return P1;
}
float Jarak0(Point P)
{
    /* Menghitung jarak P ke (0,0) */
    return sqrtf(Absis(P) * Absis(P) + Ordinat(P) * Ordinat(P));
}
float Panjang(Point P1, Point P2)
{
    /* Menghitung panjang garis yang dibentuk P1 dan P2 */
    /* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
    /* Tuliskan spec fungsi yang lebih tepat. */
    /* Menghitung jarak P1 ke P2 */
    return sqrtf(
        (Absis(P1) - Absis(P2)) * (Absis(P1) - Absis(P2)) +
        (Ordinat(P1) - Ordinat(P2)) * (Ordinat(P1) - Ordinat(P2)));
}
void Geser(Point *P, float deltaX, float deltaY)
{
    /* I.S. P terdefinisi */
    /* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
void GeserKeSbX(Point *P)
{
    /* I.S. P terdefinisi */
    /* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
    /* Proses : P digeser ke sumbu X. */
    /* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
    Ordinat(*P) = 0;
}
void GeserKeSbY(Point *P)
{
    /* I.S. P terdefinisi*/
    /* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
    /* Proses : P digeser ke sumbu Y. */
    /* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
    Absis(*P) = 0;
}
void Mirror(Point *P, boolean SbX)
{
    /* I.S. P terdefinisi */
    /* F.S. P dicerminkan tergantung nilai SbX atau SbY */
    /* Jika SbX true maka dicerminkan terhadap sumbu X */
    /* Jika SbX false maka dicerminkan terhadap sumbu Y */
    if (SbX)
    {
        Ordinat(*P) *= -1;
    }
    else
    {
        Absis(*P) *= -1;
    }
}
void Putar(Point *P, float Sudut)
{
    /* I.S. P terdefinisi */
    /* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
    Sudut = Sudut * atan(1) * 4 / 180.0;
    float x = cosf(Sudut) * Absis(*P) - sinf(Sudut) * Ordinat(*P);
    float y = sinf(Sudut) * Absis(*P) + cosf(Sudut) * Ordinat(*P);
    Absis(*P) = x;
    Ordinat(*P) = y;
}
