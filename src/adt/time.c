#include "boolean.h"
#include "time.h"
#include <stdio.h>
/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid(int D, int H, int M){
    return (
        (0 <= D && D <= 29)
        &&
        (0 <= H && H <= 23)
        &&
        (0 <= M && M <= 59)
    );
};
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime(Time* T, int DD, int HH, int MM){
    Day(*T) = DD;
    Hour(*T) = HH;
    Minute(*T) = MM;
};
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk TIME */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME(Time* T){
    boolean valid;
    do
    {
        int H, M, D;
        scanf("%d %d %d", &D, &H, &M);
        valid = IsTIMEValid(D,H, M);
        if (!valid)
        {
            printf("Waktu tidak valid\n");
        }
        else
        {
            CreateTime(T, D, H, M);
        }
    } while (!valid);
};
/* I.S. : T tidak terdefinisi */
/* F.S. : T terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen DD, HH, MM sehingga membentuk T */
/* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen DD, HH, MM
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk TIME <1,3,4> */

void TulisTIME(Time T){
    printf(
        "%02d.%02d",
        Hour(T), Minute(T)
    );
};
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format HH.MM */
/* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter,
   dll.*/
void TulisFoodTIME(Time T){
    if (Day(T)!=0){
        printf("%d hari ", Day(T));
    }
    if(Hour(T)!=0){
        printf("%d jam ", Hour(T));
    }
    if (Minute(T)!=0){
        printf("%d menit", Minute(T));
    }
    if (Day(T)==0 && Minute(T)==0 && Hour(T)==0){
        printf("0");
    }
};
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format DD hari HH jam MM menit */
/* Proses : menulis nilai setiap komponen T ke layar dalam format */
/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToMenit(Time T){
    return 60*Hour(T) + Minute(T) + 1440*Day(T);
};
/* Diberikan sebuah TIME, mengkonversi menjadi jumlah menit dari pukul 0:0:0 */
/* Rumus : menit = 1440*DD + 60*HH + MM*/
/* Nilai maksimum = 1440*29+23*60+59 */

Time MenitToTIME(long N){
    Time T;
    int HH;
    int MM;
    int DD;

    // Jika jumlah menit >= 43200
    if (N >= 43200)
    {
        N %= 43200;
    }
    // Jika jumlah menit < 0
    while (N < 0)
    {
        N += 43200;
    }

    DD = N / 1440;
    HH = (N % 1440) / 60;
    MM = (N % 1440) % 60;
    CreateTime(&T, DD, HH, MM);
    return T;
};
/* Mengirim  konversi menit ke TIME */
/* Catatan: Jika N >= 43200, maka harus dikonversi dulu menjadi jumlah menit
   yang mewakili jumlah menit yang mungkin dalam 1 hari, yaitu dengan rumus: N1
   = N mod 86400, baru N1 dikonversi menjadi TIME */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (Time T1, Time T2) {
/* Mengirimkan true jika T1=T2, false jika tidak */
    return TIMEToMenit(T1) == TIMEToMenit(T2);
}
boolean TNEQ (Time T1, Time T2) {
/* Mengirimkan true jika T1 tidak sama dengan T2 */
    return TIMEToMenit(T1) != TIMEToMenit(T2);
}
boolean TLT (Time T1, Time T2) {
/* Mengirimkan true jika T1<T2, false jika tidak */
    return TIMEToMenit(T1) < TIMEToMenit(T2);
}
boolean TGT (Time T1, Time T2) {
/* Mengirimkan true jika T1>T2, false jika tidak */
    return TIMEToMenit(T1) > TIMEToMenit(T2);
}
/* *** Operator aritmatika TIME *** */
Time NextMenit(Time T) {
    return MenitToTIME(TIMEToMenit(T)+1); 
};
/* Mengirim 1 menit setelah T dalam bentuk TIME */
Time NextNMenit(Time T, int N){
    return MenitToTIME(TIMEToMenit(T)+N);
};
/* Mengirim N menit setelah T dalam bentuk TIME */
Time PrevMenit(Time T){
    return MenitToTIME(TIMEToMenit(T)-1);
};
/* Mengirim 1 menit sebelum T dalam bentuk TIME */
Time PrevNMenit(Time T, int N){
    return MenitToTIME(TIMEToMenit(T)-N);
};
/* Mengirim N menit sebelum T dalam bentuk TIME */
/* *** Kelompok Operator Aritmetika *** */
long Durasi(Time TAw, Time TAkh) { 
    long detikTAw = TIMEToMenit(TAw);
    long detikTAkh = TIMEToMenit(TAkh);
    if (TGT(TAw, TAkh)){
        detikTAkh += 43200;
    }
    return detikTAkh - detikTAw;
};
/* Mengirim TAkh-TAw dlm menit, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
