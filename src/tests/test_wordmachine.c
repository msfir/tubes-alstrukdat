#include "boolean.h"
#include "wordmachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    InitMachine(stdin, '\n');
    ADVWORD();
    while (!endWord) {
        printf("%s\n", currentWord.TabWord);
        ADVWORD();
    }
    return 0;
}
