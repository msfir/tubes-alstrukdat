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
#include "resep.h"

#define MAX_RESEP 100

static Matrix map;
static ResepList resepList;
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
    CreateResepList(&resepList);

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
        Resep resep; CreateResep(&resep, minor);
        // resep[i] = minor; //sepertinya lom dipake
        ResepListElmt(resepList, i) = resep;
    }

    CreatePrioQueue(&delivery_list, 100);
    CreateFridge(&fridge, 10, 10);
    CreateQueue(&notifications);
}

// contoh
void refresh_idle() {
    printf("-----------------------------------\n");
    printf("BNMO di posisi: ");
    TulisPOINT(Location(simulator));
    printf("\n");
    printf("Waktu: ");
    TulisTIME(program_time);
    printf("\nNotifikasi: ");
    if (isEmptyQueue(notifications)) {
        printf("-\n");
    } else {
        if (queueLength(notifications) == 1) {
            String notikasi;
            dequeue(&notifications, &notikasi);
            printf("%s\n", STR_VALUE(notikasi));
        } else {
        printf("\n");
            while(!isEmptyQueue(notifications)) {
                String notikasi;
                dequeue(&notifications, &notikasi);
                printf("   - %s\n", STR_VALUE(notikasi));

            }
        }
    }
    printf("\n");
    displayMap(map);
    printf("\n");
}

void add_program_time(int minute) {
    // program_time = NextMenit(program_time);
    program_time = NextNMenit(program_time, minute);
    for (int i = 0; i < lengthPrioQueue(simulator.inventory); i++) {
        Food food = ELMTQUEUE(simulator.inventory, i).food;
        Time t = ELMTQUEUE(simulator.inventory, i).time;
        // ELMTQUEUE(simulator.inventory, i).time = PrevNMenit(t, minute);
        int newTime = TIMEToMenit(t) - minute;
        if (newTime <= 0) {
            String notifikasi = StringFrom("\e[92m");
            notifikasi = concat_string(notifikasi, food.name);
            notifikasi = concat_string(notifikasi, StringFrom(" telah kedaluwarsa.\e[0m"));
            enqueue(&notifications, notifikasi);

            removeAtPrioqueue(&Inventory(simulator), i, &food);
        } else {
            ELMTQUEUE(Inventory(simulator), i).time = PrevNMenit(t, minute);
        }
    }
    for (int i = 0; i < lengthPrioQueue(delivery_list); i++) {
        Food food = ELMTQUEUE(delivery_list, i).food;
        Time t = ELMTQUEUE(delivery_list, i).time;
        int newTime = TIMEToMenit(t) - minute;
        if (newTime <= 0) {
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

            add_program_time(1);
            enqueuePrioQueue(&delivery_list, (PQInfo) {food, delivery_time});
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

char *execute_move(String arah) {
    printf("\n");
    Point temp = Location(simulator);
    if (is_string_equal(arah, StringFrom("NORTH"))){
        SimulatorMove(&simulator, Location(simulator), &map, -1, 0);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
        }
    } else if (is_string_equal(arah, StringFrom("EAST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, 1);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
        }
    } else if (is_string_equal(arah, StringFrom("SOUTH"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 1, 0);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
        }
    } else if (is_string_equal(arah, StringFrom("WEST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, -1);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
        }
    } else{
        printf("\e[91mCommand tidak valid.\e[0m\n");
    }
    
    return "";
}

char *execute_fry() {
    printFryList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) {
        printf("\n");
        printf("Enter command: ");
        start_parser(stdin);
        choice = parse_int();
        Food food; Resep resep;
        if(getFoodWithIdxAction(foodlist, FRY, choice, &food)) {
            if(getResepWithFood(&resep, resepList, food)){
                if(canMakeFromResep(resep, simulator)){
                    enqueuePrioQueue(&Inventory(simulator), (PQInfo) {food, ExpirationTime(food)});
                    printf("\n");
                    printf("Berhasil menggoreng makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");
                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        removeAtPrioqueue(&Inventory(simulator), getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))), &food);
                        printf("Consumed: %s", STR_VALUE(food.name));
                        printf("\n");
                    }

                    add_program_time(1);
                } else {
                    printf("\n");
                    printf("Gagal menggoreng makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");

                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        if(getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))) == IDX_UNDEF){
                            getFoodById(foodlist, INFO(NEXT(ROOT(resep), j)), &food);
                            printf("Missing: %s", STR_VALUE(food.name));
                            printf("\n");
                        }
                    }
                }
            }
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

char *execute_mix() {
    printMixList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) {
        printf("\n");
        printf("Enter command: ");
        start_parser(stdin);
        choice = parse_int();
        Food food; Resep resep;
        if(getFoodWithIdxAction(foodlist, MIX, choice, &food)) {
            if(getResepWithFood(&resep, resepList, food)){
                if(canMakeFromResep(resep, simulator)){
                    enqueuePrioQueue(&Inventory(simulator), (PQInfo) {food, ExpirationTime(food)});
                    printf("\n");
                    printf("Berhasil mencampur makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");
                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        removeAtPrioqueue(&Inventory(simulator), getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))), &food);
                        printf("Consumed: %s", STR_VALUE(food.name));
                        printf("\n");
                    }

                    add_program_time(1);
                } else {
                    printf("\n");
                    printf("Gagal mencampur makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");

                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        if(getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))) == IDX_UNDEF){
                            getFoodById(foodlist, INFO(NEXT(ROOT(resep), j)), &food);
                            printf("Missing: %s", STR_VALUE(food.name));
                            printf("\n");
                        }
                    }
                }
            }
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

char *execute_chop() {
    printChopList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) {
        printf("\n");
        printf("Enter command: ");
        start_parser(stdin);
        choice = parse_int();
        Food food; Resep resep;
        if(getFoodWithIdxAction(foodlist, CHOP, choice, &food)) {
            if(getResepWithFood(&resep, resepList, food)){
                if(canMakeFromResep(resep, simulator)){
                    enqueuePrioQueue(&Inventory(simulator), (PQInfo) {food, ExpirationTime(food)});
                    printf("\n");
                    printf("Berhasil memotong makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");
                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        removeAtPrioqueue(&Inventory(simulator), getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))), &food);
                        printf("Consumed: %s", STR_VALUE(food.name));
                        printf("\n");
                    }

                    add_program_time(1);
                } else {
                    printf("\n");
                    printf("Gagal memotong makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");

                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        if(getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))) == IDX_UNDEF){
                            getFoodById(foodlist, INFO(NEXT(ROOT(resep), j)), &food);
                            printf("Missing: %s", STR_VALUE(food.name));
                            printf("\n");
                        }
                    }
                }
            }
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

char *execute_boil() {
    printBoilList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) {
        printf("\n");
        printf("Enter command: ");
        start_parser(stdin);
        choice = parse_int();
        Food food; Resep resep;
        if(getFoodWithIdxAction(foodlist, BOIL, choice, &food)) {
            if(getResepWithFood(&resep, resepList, food)){
                if(canMakeFromResep(resep, simulator)){
                    enqueuePrioQueue(&Inventory(simulator), (PQInfo) {food, ExpirationTime(food)});
                    printf("\n");
                    printf("Berhasil merebus makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");
                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        removeAtPrioqueue(&Inventory(simulator), getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))), &food);
                        printf("Consumed: %s", STR_VALUE(food.name));
                        printf("\n");
                    }

                    add_program_time(1);
                } else {
                    printf("\n");
                    printf("Gagal merebus makanan menjadi %s.", STR_VALUE(food.name));
                    printf("\n");

                    for(int j = 0; j<CHILD_COUNT(ROOT(resep)); j++){
                        if(getFirstFoundFoodPrioqueue(Inventory(simulator), INFO(NEXT(ROOT(resep), j))) == IDX_UNDEF){
                            getFoodById(foodlist, INFO(NEXT(ROOT(resep), j)), &food);
                            printf("Missing: %s", STR_VALUE(food.name));
                            printf("\n");
                        }
                    }
                }
            }
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }
    return "";
}

void execute_fridge() {
    printf("\n");
    printf("Makanan dalam kulkas\n");
    display_fridge(fridge);
    printf("\n");
    printf("Enter command: ");
    start_parser(stdin);
    String command = parse_line();
    if (is_string_equal(command, StringFrom("PLACE"))) {
        // sementara
        Food food = foodlist.buffer[0];
        if (can_place(fridge, 0, 0, food)) {
            place_food(&fridge, 0, 0, food);
            printf("\n");
            printf("Berhasil menyimpan %s ke dalam kulkas.\n", STR_VALUE(food.name));
        } else {
            printf("\n");
            printf("Tidak bisa menyimpan makanan pada lokasi tersebut\n");
        }
    } else if (is_string_equal(command, StringFrom("TAKE"))) {
        Food food;
        take_food(&fridge, 0, &food);
        printf("Berhasil mengambil %s dari kulkas.\n", STR_VALUE(food.name));
    }
    start_parser(stdin);
}

void execute_wait(int jam, int menit){
    add_program_time(60*jam+menit);
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
        refresh_idle();
        printf("Enter command: ");
        start_parser(stdin);
        String command = parse_line();
        if (is_string_startswith(command, StringFrom("MOVE"))) {
            notifikasi = execute_move(substring(command, 5, length(command)));
            printf("\n");
        } else if (is_string_startswith(command, StringFrom("WAIT"))) {
            int wordCount, jam = 0, menit = 0;
            String* cmdArray = split(command, ' ', &wordCount);

            // if 'menit' provided
            if (wordCount >= 3){
                menit = toInt(cmdArray[2]);
            }
            // if 'jam' provided
            if (wordCount >= 2){
                jam = toInt(cmdArray[1]);
            }

            execute_wait(jam, menit);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("BUY"))) {
            if (IsBuySpace(map, Location(simulator))){
                notifikasi = execute_buy();
                // NextMenit(program_time);
            }else{
                printf("tidak ada lokasi buy");
            }
            printf("\n");
        } else if (is_string_equal(command, StringFrom("MIX"))) {
            if (IsMixSpace(map, Location(simulator))){
                notifikasi = execute_mix();
                // NextMenit(program_time);
            }else{
                printf("tidak ada lokasi mix");
            }
            printf("\n\n");
        } else if (is_string_equal(command, StringFrom("CHOP"))) {
            if (IsChopSpace(map, Location(simulator))){
                notifikasi = execute_chop();
                NextMenit(program_time); //eh ini buat apa?
            }else{
                printf("tidak ada lokasi chop");
            }
            printf("\n\n");
        } else if (is_string_equal(command, StringFrom("FRY"))) {
            if (IsFrySpace(map, Location(simulator))){
                notifikasi = execute_fry();
                NextMenit(program_time);
            }else{
                printf("tidak ada lokasi fry");
            }
            printf("\n\n");
        } else if (is_string_equal(command, StringFrom("BOIL"))) {
            if (IsBoilSpace(map, Location(simulator))){
                notifikasi = execute_boil();
                NextMenit(program_time);
            }else{
                printf("tidak ada lokasi fry");
            }
            printf("\n\n");
        } else if (is_string_equal(command, StringFrom("CATALOG"))) {
            printCatalog(foodlist);
            start_parser(stdin);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("DELIVERY"))) {
            printf("List Makanan di Perjalanan\n");
            printf("(nama - waktu sisa delivery)\n");
            displayPrioqueue(delivery_list);
            start_parser(stdin);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("INV"))) {
            printf("List Makanan di Inventory\n");
            printf("(nama - waktu sisa ekspirasi)\n");
            displayPrioqueue(Inventory(simulator));
            start_parser(stdin);
            printf("\n");
        } else if (is_string_equal(command, StringFrom("FRIDGE"))) {
            execute_fridge();
            printf("\n");
        } else if (is_string_equal(command, StringFrom("EXIT"))) {
            quit = true;
            printf("Simulator dimatikan\n");
        } else {
            printf("\n");
            printf("\e[91mCommand tidak valid.\e[0m\n");
        }
        command = StringFrom("");
    }
    printf("\e[?1049l");
    return 0;
}
