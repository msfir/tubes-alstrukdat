#include "time.h"
#include <stdio.h>

int main(){
    printf("--- Driver Test Time ---");
    printf("\n")   ;
    printf("\n")   ;
    Time time;
    CreateTime(&time, 0, 0, 0);
    NextMenit(time);
    printf("%ld\n", TIMEToMenit(time));
    TulisTIME(time);
    PrevMenit(time);
    printf("\n")   ;
    printf("\n")   ;
    printf("--- Driver Test Time ---");
    printf("\n")   ;
    printf("\n")   ;
}
