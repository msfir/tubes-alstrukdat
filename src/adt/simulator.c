#include "boolean.h"
#include "point.h"
#include "string.h"
#include "simulator.h"
#include "time.h"
#include "prioqueuetime.h"
// #include "simulator.h"

#include "matrix.h"

/* *** Konstruktor: Membentuk sebuah Simulator dari komponen-komponennya *** */
void CreateSimulator(Simulator *x, String username, Point loc){
/* I.S. x sembarang
   F.S. x terdefinisi*/
   Username(*x) = username;
   Location(*x) = loc;
   CreatePrioQueue(&Inventory(*x), 100);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

boolean IsThereWall (Simulator x, int NCol, int NRow){
/* Mengirim true jika tidak ada dinding di sekitar Simulator */
   return !(Absis(Location(x)) >= 0 &&  Absis(Location(x)) <= NCol) && (Ordinat(Location(x)) >= 0 && Ordinat(Location(x)) <= NRow);
}

boolean IsEmptySpace(Matrix map, Point P) {
   // return (getSymbol(map, P) != 'T' && getSymbol(map, P) != 'B' && getSymbol(map, P) != 'F' && getSymbol(map, P) != 'C' && getSymbol(map, P) != 'M' && getSymbol(map, P) != 'X');
   return(getSymbol(map, P) == '#');
}

char getSymbol(Matrix map, Point P){
   return MatElmt(map, Absis(P), Ordinat(P));
}

void SimulatorMove (Simulator *x, Point P, Matrix* map, float deltaX, float deltaY){
/* I.S. Posisi Simulator terdefinisi
   F.S. Simulator berubah posisi*/
   Point newLocation = PlusDelta(P, deltaX, deltaY);

   if (!IsThereWall(*x, ROW_EFF(*map), COL_EFF(*map)) && IsEmptySpace(*map, newLocation)){ //10 is map size; GANTI 10 DENGAN MAP SIZE!
      Location(*x) = newLocation;
      MatElmt(*map, Absis(P), Ordinat(P)) = '#';
      MatElmt(*map, Absis(newLocation), Ordinat(newLocation)) = 'S';
   } //else {
      // if(!IsEmptySpace(*map, newLocation) && !IsThereWall(*x, 10, 10)) printf("\nDEBUG: KALIAN NABRAK : %c\n", getSymbol(*map, newLocation));
      // if(IsEmptySpace(*map, newLocation) && IsThereWall(*x, 10, 10)) printf("\nDEBUG: KALIAN NABRAK TEMBOK\n");
   // }
   
}

boolean IsBuySpace(Matrix map, Point P){
   Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;
      // TulisPOINT(P);
   // printf("\n");
   // TulisPOINT(Kanan);
   // printf("\n");
   // TulisPOINT(Kiri);
   // printf("\n");
   // TulisPOINT(Atas);
   // printf("\n");
   // TulisPOINT(Bawah);
   // printf("\n");
   return (getSymbol(map, Kanan) == 'T' || getSymbol(map, Kiri) == 'T' || getSymbol(map, Bawah) == 'T' || getSymbol(map, Atas) == 'T');
};
/*Mengembalikan true jika di sekitar point P merupakan tempat Buy*/
boolean IsMixSpace(Matrix map, Point P){
    Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;

   return (getSymbol(map, Kanan) == 'M' || getSymbol(map, Kiri) == 'M' || getSymbol(map, Bawah) == 'M' || getSymbol(map, Atas) == 'M');
};
/*Mengembalikan true jika di sekitar point P merupakan tempat Mix*/
boolean IsBoilSpace(Matrix map, Point P){
   Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;

   return (getSymbol(map, Kanan) == 'B' || getSymbol(map, Kiri) == 'B' || getSymbol(map, Bawah) == 'B' || getSymbol(map, Atas) == 'B');
};
/*Mengembalikan true jika di sekitar point P merupakan tempat Boil*/
boolean IsFrySpace(Matrix map, Point P){
   Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;

   return (getSymbol(map, Kanan) == 'F' || getSymbol(map, Kiri) == 'F' || getSymbol(map, Bawah) == 'F' || getSymbol(map, Atas) == 'F');
};
/*Mengembalikan true jika di sekitar point P merupakan tempat Fry*/
boolean IsChopSpace(Matrix map, Point P){
   Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;

   return (getSymbol(map, Kanan) == 'C' || getSymbol(map, Kiri) == 'C' || getSymbol(map, Bawah) == 'C' || getSymbol(map, Atas) == 'C');
};
/*Mengembalikan true jika di sekitar point P merupakan tempat Chop*/

boolean IsFridgeSpace(Matrix map, Point P) {
   Point Kanan = P;
   Point Atas = P;
   Point Kiri = P;
   Point Bawah = P;
   Absis(Kanan)++;
   Ordinat(Atas)++;
   Absis(Kiri)--;
   Ordinat(Bawah)--;

   return (getSymbol(map, Kanan) == 'R' || getSymbol(map, Kiri) == 'R' || getSymbol(map, Bawah) == 'R' || getSymbol(map, Atas) == 'R');
}
