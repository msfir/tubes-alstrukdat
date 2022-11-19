#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt.h"
#include "boolean.h"

int main() {
    printf("--- Driver Test WordMachine ---");
    printf("\n");
    printf("\n");
    FILE *file = fopen("konfigurasi_peta.txt", "r");
    InitMachine(file, 0);
    ADVWORD();
    boolean firstWord = true;
    while (!endWord) {
        if (!firstWord)
            printf(" ");
        for (int i = 0; i < currentWord.Length; i++) {
            printf("%c", currentWord.TabWord[i]);
        }
        firstWord = currentWord.TabWord[currentWord.Length - 1] == '\n';
        ADVWORD();
    }
    printf("\n");
    printf("-------------------------------");
    printf("\n");
    printf("\n");
    return 0;
}
