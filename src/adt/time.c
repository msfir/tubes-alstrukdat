#include "boolean.h"
#include "adt/time.h"
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S) {
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
    return (
        (0 <= H && H <= 23)
        &&
        (0 <= M && M <= 59)
        &&
        (0 <= S && S <= 59)
    );
}

/* *** Konstruktor: Membentuk sebuah Time dari komponen-komponennya *** */
void CreateTime (Time * T, int HH, int MM, int SS) {
/* Membentuk sebuah Time dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk Time */
    Hour(*T) = HH;
    Minute(*T) = MM;
    Second(*T) = SS;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (Time * T) {
/* I.S. : T tidak terdefinisi */
/* F.S. : T terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
/* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika Time tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk Time <1,3,4> */
    boolean valid;
    do
    {
        int H, M, S;
        scanf("%d %d %d", &H, &M, &S);
        valid = IsTIMEValid(H, M, S);
        if (!valid)
        {
            printf("Jam tidak valid\n");
        }
        else
        {
            CreateTime(T, H, M, S);
        }
    } while (!valid);

}

void TulisTIME (Time T) {
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
    printf(
        "%02d:%02d:%02d",
        Hour(T), Minute(T), Second(T)
    );
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (Time T) {
/* Diberikan sebuah Time, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
    return 3600*Hour(T) + 60*Minute(T) + Second(T);
}

Time DetikToTIME (long N) {
/* Mengirim  konversi detik ke Time */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi Time */
    Time T;
    int HH;
    int MM;
    int SS;

    // Jika jumlah detik >= 86400
    if (N >= 86400)
    {
        N %= 86400;
    }
    // Jika jumlah detik < 0
    while (N < 0)
    {
        N += 86400;
    }

    HH = N / 3600;
    MM = (N % 3600) / 60;
    SS = (N % 3600) % 60;
    CreateTime(&T, HH, MM, SS);
    return T;
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (Time T1, Time T2) {
/* Mengirimkan true jika T1=T2, false jika tidak */
    return TIMEToDetik(T1) == TIMEToDetik(T2);
}
boolean TNEQ (Time T1, Time T2) {
/* Mengirimkan true jika T1 tidak sama dengan T2 */
    return TIMEToDetik(T1) != TIMEToDetik(T2);
}
boolean TLT (Time T1, Time T2) {
/* Mengirimkan true jika T1<T2, false jika tidak */
    return TIMEToDetik(T1) < TIMEToDetik(T2);
}
boolean TGT (Time T1, Time T2) {
/* Mengirimkan true jika T1>T2, false jika tidak */
    return TIMEToDetik(T1) > TIMEToDetik(T2);
}
/* *** Operator aritmatika Time *** */
Time NextDetik (Time T) {
/* Mengirim 1 detik setelah T dalam bentuk Time */
    return DetikToTIME(TIMEToDetik(T) + 1);
}
Time NextNDetik (Time T, int N) {
/* Mengirim N detik setelah T dalam bentuk Time */
    return DetikToTIME(TIMEToDetik(T) + N);
}
Time PrevDetik (Time T) {
/* Mengirim 1 detik sebelum T dalam bentuk Time */
    return DetikToTIME(TIMEToDetik(T) - 1);
}
Time PrevNDetik (Time T, int N) {
/* Mengirim N detik sebelum T dalam bentuk Time */
    return DetikToTIME(TIMEToDetik(T) - N);
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (Time TAw, Time TAkh) {
/* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
    long detikTAw = TIMEToDetik(TAw);
    long detikTAkh = TIMEToDetik(TAkh);
    if (TGT(TAw, TAkh))
    {
        detikTAkh += 86400;
    }
    return detikTAkh - detikTAw;
}
