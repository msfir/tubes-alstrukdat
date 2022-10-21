#include "boolean.h"
#include "wordmachine.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* path_separtor;
    char* os = getenv("OS");
    os = (os == NULL ? "" : os);
    if (strcmp("Windows_NT", os) == 0) {
        path_separtor = "\\";
    } else {
        path_separtor = "/";
    }
    char cwd[0xff];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        printf("%s", cwd);
        strcat(cwd, path_separtor);
        strcat(cwd, "test.txt");
        printf("%s\n", cwd);
        STARTWORD(cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    while (!endWord) {
        printf("%s\n", currentWord.TabWord);
        ADVWORD();
    }
    return 0;
}
