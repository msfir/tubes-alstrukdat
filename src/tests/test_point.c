#include <stdio.h>
#include "point.h"

int main() {
    printf("--- Driver Test Parser ---");
    printf("\n")   ;
    printf("\n")   ;
    Point p1, p2;
    CreatePoint(&p1, 1,2);
    TulisPOINT(p1);

    CreatePoint(&p2, 1, 2);
    printf("\n");

    if (EQ(p1,p2)) {
        printf("equal\n");
    }

    p2 = NextX(p2);
    p2 = NextY(p2);
    TulisPOINT(p2);
    printf("\n");

    if (NEQ(p1,p2)) {
        printf("not equal\n");
    }
    p1 = PlusDelta(p1, 3, 3);
    TulisPOINT(p1);
    printf("\n");

    Geser(&p1, 1, 1);
    TulisPOINT(p1);
    printf("\n");

    printf("\n")   ;
    printf("--- Driver Test Parser ---");
    printf("\n")   ;
    printf("\n")   ;
    return 0;
}
