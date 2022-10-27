#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "food.h"
#include "parser.h"
#include "time.h"
#include "wordmachine.h"

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
        FILE* stream = fopen(cwd, "r");
        start_parser(stream);
    } else {
        perror("getcwd() error");
        return 1;
    }
    int n = parse_int();
    for (int i = 0; i < n; i++) {
        int id = parse_int();
        String name = parse_line();
        Time expire = parse_time();
        Time delivery = parse_time();
        enum Action action = parse_action();
        printf("Makanan %d\n", i+1);
        printf("ID\t:%d\n", id);
        printf("Name\t:%s\n", STR_VALUE(name));
        printf("Expire time\t:");
        TulisTIME(expire);
        printf("\n");
        printf("Delivery time\t:");
        TulisTIME(delivery);
        printf("\n");
        printf("%d\n", action);
    }
    return 0;
}
