#include <stdio.h>
#include "point.c"
#include "matrix.c"

int main()
{
    Matrix m;
    int nRow, nCol;

    CreateMap(&m);
    displayMap(m);

}