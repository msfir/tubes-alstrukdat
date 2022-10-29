#include "matrix.h"

#include <stdio.h>


int main() {
    Matrix map;
    CreateMap(&map, fopen("test_peta.txt", "r"));

    displayMatrix(map);
    printf("\n");
    displayMap(map);

    return 0;
}
