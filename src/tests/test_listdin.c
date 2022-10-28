#include <stdio.h> 
#include "listdin.h"
#include "node.h"
#include "food.h"
#include "cstring.h"
#include "time.h"

int main(){ 
    Time dmytm; CreateTime(&dmytm, 12, 23, 9); enum Action eklok = MIX;
    Food pecel; CreateFood(&pecel, StringFrom("pecel ayam"), dmytm, eklok, dmytm);
    Food takol; CreateFood(&takol, StringFrom("ayam takol"), dmytm, eklok, dmytm);
    Address aPecel, aTakol; aPecel = newNode(&pecel); aTakol = newNode(&takol);

    ListDin ld; CreateListDin(&ld, 5);
    displayListDin(ld);

    insertLast(&ld, aPecel);
    insertLast(&ld, aTakol);

    displayListDin(ld);
    displayListDinAsFood(ld);
    

    return 0;
}