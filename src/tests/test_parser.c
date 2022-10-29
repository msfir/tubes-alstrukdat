#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "food.h"
#include "node.h"
#include "parser.h"
#include "time.h"
#include "wordmachine.h"
#include "tree.h"

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
        Food f;
        CreateFood(&f, id, name, expire, action, delivery);
        printf("Makanan %d\n", i+1);
        DisplayFood(f);
    }
    FILE *konfigurasi_resep = fopen("test_resep.txt", "r");
    start_parser(konfigurasi_resep);
    n = parse_int();
    for (int i = 0; i < n; i++) {
        int id = parse_int();
        Address parent = newNode(id);
        Tree tree;
        CreateTree(&tree, parent);
        int num_child = parse_int();
        for (int k = 0; k < num_child; k++) {
            int id_child = parse_int();
            Address child = newNode(id_child);
            MakeChildren(parent, child);
        }
        printf("%d\n", parent->childCount);
    }
    return 0;
}
