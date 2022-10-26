/* File: time.h */
/* Definisi ADT TIME */

#ifndef TIME_H
#define TIME_H

#include "../boolean.h"

/* *** Definisi TYPE TIME <HH:MM:SS> *** */
typedef struct {
    int DD; /* integer [0..29] hari*/
    int HH; /* integer [0..23] jam*/
    int MM; /* integer [0..59] menit*/
} Time;

/* *** Notasi Akses: selektor TIME *** */
// clang-format off
#define Hour(T)   (T).HH
#define Minute(T) (T).MM
#define Day(T) (T).DD
// clang-format on

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid(int D, int H, int M);
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime(Time* T, int DD, int HH, int MM);
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk TIME */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME(Time* T);
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

void TulisTIME(Time T);
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter,
   dll.*/

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToMenit(Time T);
/* Diberikan sebuah TIME, mengkonversi menjadi jumlah menit dari pukul 0:0:0 */
/* Rumus : menit = 1440*DD + 60*HH + MM*/
/* Nilai maksimum = 1440*29+23*60+59 */

Time MenitToTIME(long N);
/* Mengirim  konversi menit ke TIME */
/* Catatan: Jika N >= 43200, maka harus dikonversi dulu menjadi jumlah menit
   yang mewakili jumlah menit yang mungkin dalam 1 hari, yaitu dengan rumus: N1
   = N mod 86400, baru N1 dikonversi menjadi TIME */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ(Time T1, Time T2);
/* Mengirimkan true jika T1=T2, false jika tidak */
boolean TNEQ(Time T1, Time T2);
/* Mengirimkan true jika T1 tidak sama dengan T2 */
boolean TLT(Time T1, Time T2);
/* Mengirimkan true jika T1<T2, false jika tidak */
boolean TGT(Time T1, Time T2);
/* Mengirimkan true jika T1>T2, false jika tidak */
/* *** Operator aritmatika TIME *** */
Time NextMenit(Time T);
/* Mengirim 1 menit setelah T dalam bentuk TIME */
Time NextNMenit(Time T, int N);
/* Mengirim N menit setelah T dalam bentuk TIME */
Time PrevMenit(Time T);
/* Mengirim 1 menit sebelum T dalam bentuk TIME */
Time PrevNMenit(Time T, int N);
/* Mengirim N menit sebelum T dalam bentuk TIME */
/* *** Kelompok Operator Aritmetika *** */
long Durasi(Time TAw, Time TAkh);
/* Mengirim TAkh-TAw dlm menit, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */

#endif
