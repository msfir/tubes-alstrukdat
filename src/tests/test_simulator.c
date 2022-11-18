#include <stdio.h>
#include "simulator.h"

int main() {
    Simulator S;
    String username;
    Point loc;
    PriorityQueue inventory;
    Time second;
    Matrix map;
    
    CreateSimulator(&S, username, loc);

    float deltaX;
    float deltaY;
    scanf("%f %f", &deltaX, &deltaY);
    SimulatorMove (&S, loc, &map, deltaX, deltaY);
    
    if (IsThereWall (S, (int) deltaX, (int) deltaY)) {
        printf("Ada Dinding!");
    } 



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
}