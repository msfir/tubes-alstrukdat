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
#include "fridge.h"
#include "queue.h"

#define MAX_RESEP 100

static Matrix map;
static Tree resep[MAX_RESEP];
static FoodList foodlist;
static Time program_time;
static Simulator simulator;
static Queue notifications;
static PriorityQueue delivery_list;
static Fridge fridge;

// Fungsi helper
Address __getNodeById(Address *nodes, int id, int size) {
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

// logger
/* 
 * Menampilkan pesan error pada terminal dengan teks berwarna merah (tanpa new line)
 */
void log_error(char* message) {
    printf("\e[91m%s\e[0m", message);
}
/* 
 * Menampilkan pesan info pada terminal dengan teks berwarna hijau (tanpa new line)
 */
void log_info(char* message) {
    printf("\e[92m%s\e[0m", message);
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
        int food_width = parse_int();
        int food_height = parse_int();
        Size food_size = {food_width, food_height};
        enum Action action = parse_action();
        Food f;
        CreateFood(&f, id, name, expire, action, delivery, food_size);
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
        Node *node = __getNodeById(nodes, id, nodes_num);
        int num_child = parse_int();
        for (int k = 0; k < num_child; k++) {
            int id_child = parse_int();
            Node *child = __getNodeById(nodes, id_child, nodes_num);
            MakeChildren(node, child);
        }
        CreateTree(&minor, node);
        resep[i] = minor;
    }

    CreatePrioQueue(&delivery_list, 100);
    CreateFridge(&fridge, 10, 10);
    CreateQueue(&notifications);
}

void display_notifikasi() {
    printf("\nNotifikasi: ");
    if (isEmptyQueue(notifications)) {
        printf("-\n");
    } else {
        printf("\n");
        int counter = 1;
        while(!isEmptyQueue(notifications)) {
            String notikasi;
            dequeue(&notifications, &notikasi);
            printf("   %d. %s\n", counter, STR_VALUE(notikasi));
            counter++;
        }
    }
}

// contoh
void refresh_idle() {
    printf("-----------------------------------\n");
    printf("BNMO di posisi: ");
    TulisPOINT(Location(simulator));
    printf("\n");
    printf("Waktu: ");
    TulisTIME(program_time);
    display_notifikasi();
    printf("\n");
    displayMap(map);
    printf("\n");
}

void add_program_time(int minute) {
    program_time = NextMenit(program_time);
    for (int i = 0; i < lengthPrioQueue(simulator.inventory); i++) {
        Food food = ELMTQUEUE(simulator.inventory, i).food;
        Time t = ELMTQUEUE(simulator.inventory, i).time;
        int new_time = TIMEToMenit(t) - minute;
        if (new_time <= 0) {
            String notifikasi = StringFrom("\e[92m");
            notifikasi = concat_string(notifikasi, food.name);
            notifikasi = concat_string(notifikasi, StringFrom(" telah kedaluwarsa.\e[0m"));
            enqueue(&notifications, notifikasi);
        } else {
            ELMTQUEUE(simulator.inventory, i).time = PrevNMenit(t, minute);
        }
    }
    for (int i = 0; i < lengthPrioQueue(delivery_list); i++) {
        Food food = ELMTQUEUE(delivery_list, i).food;
        Time t = ELMTQUEUE(delivery_list, i).time;
        int new_time = TIMEToMenit(t) - minute;
        if (new_time <= 0) {
            String notifikasi = StringFrom("\e[92m");
            notifikasi = concat_string(notifikasi, food.name);
            notifikasi = concat_string(notifikasi, StringFrom(" yang dipesan telah sampai di inventory.\e[0m"));
            enqueue(&notifications, notifikasi);

            dequeuePrioQueue(&delivery_list, &food);
            enqueuePrioQueue(&Inventory(simulator), (PQInfo) {food, ExpirationTime(food)});
        } else {
            ELMTQUEUE(delivery_list, i).time = PrevNMenit(t, minute);
        }
    }
}

// contoh lagi
void execute_buy() {
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

            add_program_time(1);
            enqueuePrioQueue(&delivery_list, (PQInfo) {food, delivery_time});
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    refresh_idle();
}

void execute_move(String arah) {
    if (is_string_equal(arah, StringFrom("NORTH"))){
        SimulatorMove(&simulator, Location(simulator), &map, -1, 0);
    } else if (is_string_equal(arah, StringFrom("EAST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, 1);
    } else if (is_string_equal(arah, StringFrom("SOUTH"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 1, 0);
    } else if (is_string_equal(arah, StringFrom("WEST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, -1);
    } 
    
    
}

void execute_fry() {
    printFryList(foodlist);
    start_parser(stdin);
}

void execute_mix() {
    printMixList(foodlist);
    start_parser(stdin);
}

void display_inventory() {
    printf("List Makanan di Inventory\n");
    printf("(nama - waktu sisa kedaluwarsa)\n");
    displayPrioqueue(Inventory(simulator));
}

void execute_fridge() {
    printf("\n");
    display_fridge(fridge);
    printf("\n");

    boolean closed = false;
    while (!closed) {
        printf("Enter command: ");
        start_parser(stdin);
        String command = parse_line();

        if (is_string_equal(command, StringFrom("PLACE"))) {
            printf("\n");
            printf("List makanan di inventory \n");
            printf("(Nama - Waktu kedaluwarsa - Ukuran)\n");
            for (int i = 0; i < lengthPrioQueue(Inventory(simulator)); i++) {
                Food food = simulator.inventory.buffer[i].food;
                printf("%d. %s - ", i+1, STR_VALUE(food.name));
                TulisFoodTIME(food.expiration_time);
                printf(" - %dx%d\n", food.size.width, food.size.height);
            }
            printf("\n");
            
            boolean valid = false;
            boolean cancel = false;
            int choice;
            while (!valid) {
                printf("Pilih makanan yang ingin disimpan (kirim 0 untuk batal): ");
                start_parser(stdin);
                choice = parse_int();
                if (0 < choice && choice <= lengthPrioQueue(Inventory(simulator))) {
                    valid = true;
                } else if (choice == 0) {
                    valid = true;
                    cancel = true;
                    printf("\n");
                } else {
                    log_error("Pilihan tidak valid.\n");
                }
            }

            valid = false;
            while (!valid && !cancel) {
                printf("Lokasi penyimpanan (baris): ");
                start_parser(stdin);
                int row = parse_int();
                printf("Lokasi penyimpanan (kolom): ");
                start_parser(stdin);
                int col = parse_int();
                Food food = simulator.inventory.buffer[choice - 1].food;
                if (can_place(fridge, row, col, food)) {
                    place_food(&fridge, row, col, food);
                    printf("\n");
                    display_fridge(fridge);
                    printf("\n");
                    printf("\e[92mBerhasil menyimpan %s ke dalam kulkas.\n\e[0m", STR_VALUE(food.name));
                    printf("\n");
                    valid = true;
                    removeAtPrioqueue(&Inventory(simulator), choice - 1, &food);
                } else {
                    log_error("Tidak bisa menyimpan makanan pada lokasi tersebut\n");
                }
            }

        } else if (is_string_equal(command, StringFrom("TAKE"))) {
            printf("\n");
            boolean valid;
            do {
                printf("Pilih makanan yang ingin diambil (kirim 0 untuk batal): ");
                start_parser(stdin);
                int choice = parse_int();
                if (0 < choice && choice <= fridge.food_count) {
                    Food food;
                    take_food(&fridge, choice - 1, &food);
                    printf("\n");
                    display_fridge(fridge);
                    printf("\n");
                    printf("\e[92mBerhasil mengambil %s dari kulkas.\n\e[0m", STR_VALUE(food.name));
                    printf("\n");
                    valid = true;
                    enqueuePrioQueue(&simulator.inventory, (PQInfo) {food, ExpirationTime(food)});
                } else if (choice == 0) {
                    valid = true;
                    printf("\n");
                } else {
                    log_error("Pilihan tidak valid.\n");
                    valid = false;
                }
            } while (!valid);
        } else if (is_string_equal(command, StringFrom("CLOSE"))) {
            closed = true;
            refresh_idle();
        } else {
            log_error("Command tidak valid.\n");
        }
    }
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
    refresh_idle();
    while (!quit) {
        printf("Enter command: ");
        start_parser(stdin);
        String command = parse_line();
        if (is_string_startswith(command, StringFrom("MOVE"))) {
            execute_move(substring(command, 5, length(command)));
            printf("\n");
        } else if (is_string_equal(command, StringFrom("BUY"))) {
            execute_buy();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("MIX"))) {
            execute_mix();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("FRY"))) {
            execute_fry();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("CATALOG"))) {
            printCatalog(foodlist);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("DELIVERY"))) {
            printf("List Makanan di Perjalanan\n");
            printf("(nama - waktu sisa delivery)\n");
            displayPrioqueue(delivery_list);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("INVENTORY"))) {
            display_inventory();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("FRIDGE"))) {
            execute_fridge();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("EXIT"))) {
            quit = true;
        } else {
            printf("\e[91mCommand tidak valid.\e[0m\n");
        }
        command = StringFrom("");
    }
    printf("\e[?1049l");
    return 0;
}
