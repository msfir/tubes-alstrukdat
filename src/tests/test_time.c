#include "time.h"
#include <stdio.h>

int main(){
    Time time;
    CreateTime(&time, 0, 0, 0);
    NextMenit(time);
    printf("%ld\n", TIMEToMenit(time));
    TulisTIME(time);
    PrevMenit(time);
}
