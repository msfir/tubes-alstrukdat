#include "adt.h"

int main() {
    printf("--- Driver Test Food ---");
    printf("\n");
    printf("\n");

    FILE *file = fopen("LICENSE", "r");
    START(file, 0);
    while (!EOP) {
        printf("%c", currentChar);
        ADV();
    }

    printf("\n");
    printf("--- Driver Test Food ---");
    printf("\n");
    printf("\n");
}
