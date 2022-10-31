#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boolean.h"
#include "cstring.h"
#include "foodlist.h"
#include "matrix.h"
#include "node.h"
#include "parser.h"
#include "point.h"
#include "prioqueuetime.h"
#include "queue.h"
#include "simulator.h"
#include "time.h"
#include "tree.h"

#define MAX_RESEP 100
#define MAX_FOOD  100

static Matrix map;
static Tree resep[MAX_RESEP];
static FoodList foodlist;
static Time program_time;
static Simulator simulator;
static Queue notifications;
static PriorityQueue delivery_list;

Address getNodeById(Address *nodes, int id, int size) {
    Address node;
    boolean found = false;
    for (int i = 0; i < size && !found; i++) {
        if (INFO(nodes[i]) == id) {
            found = true;
            node = nodes[i];
        }
    }
    return node;
}

void setup_program(Point *simulator_location) {
    // setup map
    FILE *file = fopen("konfigurasi_peta.txt", "r");
    start_parser(file);
    int rows = parse_int();
    int cols = parse_int();
    createMatrix(rows, cols, &map);
    for (int row = 0; row < rows; row++) {
        String line = parse_line();
        for (int col = 0; col < cols; col++) {
            char c = STR_VALUE(line)[col];
            MatElmt(map, row, col) = c;
            if (c == 'S') {
                CreatePoint(simulator_location, row, col);
            }
        }
    }

    // setup food list
    CreateFoodList(&foodlist);
    file = fopen("konfigurasi_makanan.txt", "r");
    start_parser(file);
    int nodes_num = parse_int();
    Address nodes[nodes_num];
    for (int i = 0; i < nodes_num; i++) {
        int id = parse_int();
        String name = parse_line();
        Time expire = parse_time();
        Time delivery = parse_time();
        enum Action action = parse_action();
        Food f;
        CreateFood(&f, id, name, expire, action, delivery);
        addFood(&foodlist, f);
        nodes[i] = newNode(id);
    }

    // setup resep
    file = fopen("konfigurasi_resep.txt", "r");
    start_parser(file);
    int resep_num = parse_int();
    for (int i = 0; i < resep_num; i++) {
        Tree minor;
        int id = parse_int();
        Node *node = getNodeById(nodes, id, nodes_num);
        int num_child = parse_int();
        for (int k = 0; k < num_child; k++) {
            int id_child = parse_int();
            Node *child = getNodeById(nodes, id_child, nodes_num);
            MakeChildren(node, child);
        }
        CreateTree(&minor, node);
        resep[i] = minor;
    }

    CreatePrioQueue(&delivery_list, 100);
}

// contoh
void refresh_idle(char *notifikasi) {
    printf("-----------------------------------\n");
    printf("BNMO di posisi: ");
    TulisPOINT(Location(simulator));
    printf("\n");
    printf("Waktu: ");
    TulisTIME(program_time);
    printf("\nNotifikasi: %s\n", notifikasi);
    printf("\n");
    displayMap(map);
    printf("\n");
}

void add_program_time() {
    program_time = NextMenit(program_time);
    for (int i = 0; i < lengthPrioQueue(simulator.inventory); i++) {
        Time t = ELMTQUEUE(simulator.inventory, i).time;
        ELMTQUEUE(simulator.inventory, i).time = PrevMenit(t);
    }
    for (int i = 0; i < lengthPrioQueue(delivery_list); i++) {
        Time t = ELMTQUEUE(delivery_list, i).time;
        ELMTQUEUE(delivery_list, i).time = PrevMenit(t);
    }
}

// contoh lagi
char *execute_buy() {
    printBuyList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) {
        printf("\n");
        printf("Enter command: ");
        start_parser(stdin);
        choice = parse_int();
        Food food;
        if(getFoodWithIdxAction(foodlist, BUY, choice, &food)) {
            String food_name = food.name;
            Time delivery_time = food.delivery_time;
            printf("\n");
            printf("Berhasil memesan %s. %s akan diantar dalam ", STR_VALUE(food_name), STR_VALUE(food_name));
            TulisFoodTIME(delivery_time);
            printf("\n");

            enqueuePrioQueue(&delivery_list, (PQInfo) {food, delivery_time});
            add_program_time();
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

// contoh lagi
char *execute_fry() {
    printFryList(foodlist);
    start_parser(stdin);
    return "";
}

// contoh lagi
char *execute_mix() {
    printMixList(foodlist);
    start_parser(stdin);
    return "";
}

int main() {
    printf("\e[?1049h\e[H");
    printf(" .-.__.-.__.-.\n");
    printf("(             )        _______\n");
    printf(" )           (      .-' _____ '-.       /| \n");
    printf("(       ||||  )   .' .-'.  ':'-. '.    | |  __\n");
    printf(" ) |||| |||| (   / .''::: .:    '. \\   | | /  \\ \n");
    printf("(  |||| \\__/  ) / /   :::::'      \\ \\  | | |(_|\n");
    printf(" ) \\__/  ||  ( | ;.    ':' `       ; | \\ | \\__/\n");
    printf("(   ||   ||   )| |       '..       | |  ||  ||\n");
    printf(" )  ##   ##  ( | ; '      ::::.    ; |  ##  ##\n");
    printf("(   ##   ##   ) \\ \\       '::::   / /   ##  ##\n");
    printf(" )  j#   ##  (   \\ '.      :::  .' /    ##  ##\n");
    printf("(   g#   ##   )   '. '-.___'_.-' .'     ##  ##\n");
    printf(" )  s#   ##  (      '-._______.-'       ##  ##\n");
    printf("(   __   __   ) \n");
    printf(" '-'  '-'  '-'\n");
    Point simulator_location;
    setup_program(&simulator_location);
    printf("\n");
    printf("Masukkan username: ");
    start_parser(stdin);
    String username = parse_line();
    CreateTime(&program_time, 0, 0, 0);
    CreateSimulator(&simulator, username, simulator_location);
    boolean quit;
    char *notifikasi = "";
    while (!quit) {
        refresh_idle(notifikasi);
        printf("Enter command: ");
        start_parser(stdin);
        String command = parse_line();
        if (is_string_equal(command, StringFrom("BUY"))) {
            notifikasi = execute_buy();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("MIX"))) {
            notifikasi = execute_mix();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("FRY"))) {
            notifikasi = execute_fry();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("CATALOG"))) {
            printCatalog(foodlist);
            start_parser(stdin);
            printf("\n");
        }  else if (is_string_equal(command, StringFrom("DELIVERY"))) {
            printf("List Makanan di Perjalanan\n");
            printf("(nama - waktu sisa delivery)\n");
            displayPrioqueue(delivery_list);
            start_parser(stdin);
            printf("\n");
        } else {
            quit = true;
        }
    }
    printf("\e[?1049l");
    return 0;
}
