#include "adt.h"

int main() {
    printf("--- Driver Test CharMachine ---");
    printf("\n");
    printf("\n");

    FILE *file = fopen("LICENSE", "r");
    START(file, 0);
    while (!EOP) {
        printf("%c", currentChar);
        ADV();
    }

    printf("\n");
    printf("------------------------");
    printf("\n");
    printf("\n");
}
