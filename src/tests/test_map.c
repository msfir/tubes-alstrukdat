#include <stdio.h>

#include "adt.h"

int main() {
    printf("--- Driver Test Map ---");
    printf("\n");
    printf("\n");
    Matrix map;
    CreateMap(&map, fopen("konfigurasi_peta.txt", "r"));

    displayMatrix(map);
    printf("\n");
    displayMap(map);

    printf("\n");
    printf("-----------------------");
    printf("\n");
    printf("\n");
    return 0;
}
