#include "time.h"

int main(){
    Time time;
    CreateTime(&time, 0, 0, 0);
    NextMenit(time);
    printf("%d %d", TIMEToMenit(time), MenitToTIME(time));
    TulisTime(time);
    PrevMenit(time);
}