#include <stdio.h> 
#include "food.h"
#include "time.h"
#include "cstring.h"


int main(){ 
    printf("--- Driver Test Food ---");
    printf("\n")   ;
    printf("\n")   ;
    Time contohTime; CreateTime(&contohTime, 1, 2, 3);
    Size size; size.width = 1; size.height = 2;
    Food ayam; 
    CreateFood(&ayam, 420, StringFrom("ayam rasa bebek"), contohTime, MIX, PrevNMenit(contohTime, 3600), size, MenitToTIME(0));
    

    DisplayFood(ayam);

    printf("\n")   ;
    printf("\n")   ;
    printf("--- Driver Test Food ---");
    printf("\n")   ;
    printf("\n")   ;
    return 0;
}
