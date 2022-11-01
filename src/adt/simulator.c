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
   CreateTime(&Time(*x), 0, 0, 0);
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

   if (!IsThereWall(*x, 10, 10) && IsEmptySpace(*map, newLocation)){ //10 is map size; GANTI 10 DENGAN MAP SIZE!
      Location(*x) = newLocation;
      MatElmt(*map, Absis(P), Ordinat(P)) = '#';
      MatElmt(*map, Absis(newLocation), Ordinat(newLocation)) = 'S';
   } //else {
      // if(!IsEmptySpace(*map, newLocation) && !IsThereWall(*x, 10, 10)) printf("\nDEBUG: KALIAN NABRAK : %c\n", getSymbol(*map, newLocation));
      // if(IsEmptySpace(*map, newLocation) && IsThereWall(*x, 10, 10)) printf("\nDEBUG: KALIAN NABRAK TEMBOK\n");
   // }
   
}

