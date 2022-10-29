#include "boolean.h"
#include "wordmachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("test.txt", "r");
    InitMachine(file, 0);
    ADVWORD();
    boolean firstWord = true;
    while (!endWord) {
        if (!firstWord) printf(" ");
        for (int i = 0; i < currentWord.Length; i++) {
            printf("%c", currentWord.TabWord[i]);
        }
        firstWord = currentWord.TabWord[currentWord.Length - 1] == '\n';
        ADVWORD();
    }
    return 0;
}
