#include <stdio.h>
#include "simulator.h"
#include "boolean.h"

int main() {
    printf("--- Driver Test Simulator ---");
    printf("\n")   ;
    printf("\n")   ;
    Simulator S;
    String username;
    Point loc;
    PriorityQueue inventory;
    Time second;
    Matrix map;
    
    CreateSimulator(&S, username, loc);

    int deltaX = 10;
    int deltaY = 0;
    CreatePoint(&loc, 0, 0);

    SimulatorMove (&S, loc, &map, deltaX, deltaY);
    
    if (IsThereWall (S, deltaX, deltaY)) {
        printf("Ada Dinding!");
    } 

    deltaX = -1;
    deltaY = 7;
    if (!IsEmptySpace(map, loc)) {
        if(IsBuySpace(map, loc)) {
            printf("Kamu bisa membeli disini!\n");
        } else if (IsMixSpace(map, loc)) {
            printf("Kamu bisa mencampur disini!\n");
        } else if (IsBoilSpace(map, loc)) {
            printf("Kamu bisa merebus disini!\n");
        } else if (IsFrySpace(map, loc)) {
            printf("Kamu bisa menggoreng disini!\n");
        } else if (IsChopSpace(map, loc)) {
            printf("Kamu bisa memotong disini!\n");
        } else if (IsFridgeSpace(map, loc)) {
            printf("Disini ada Kulkas!\n");
        } else {
            printf("Disini bukan lokasi apapun!\n");
        }
    }
    printf("\n")   ;
    printf("--- Driver Test Simulator ---");
    printf("\n")   ;
    printf("\n")   ;
}
