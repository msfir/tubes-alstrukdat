#include "matrix.h"

#include <stdio.h>


int main() {
    printf("--- Driver Test Map ---");
    printf("\n")   ;
    printf("\n")   ;
    Matrix map;
    CreateMap(&map, fopen("test_peta.txt", "r"));

    displayMatrix(map);
    printf("\n");
    displayMap(map);

    printf("\n")   ;
    printf("--- Driver Test Map ---");
    printf("\n")   ;
    printf("\n")   ;
    return 0;
}
