#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt.h"
#include "boolean.h"
#include "commands.h"
#include "parser.h"
#include "logger.h"

#define MAX_RESEP 100

Matrix map;
ResepList resepList;
FoodList foodlist;
Time program_time;
Simulator simulator;
Queue notifications;
PriorityQueue delivery_list;
Fridge fridge;
Stack undoS, redoS;

// logger
/*
 * Menampilkan pesan error pada terminal dengan teks berwarna merah (tanpa new line)
 */
void log_error(char *message) {
    printf("\e[91m%s\e[0m", message);
}
/*
 * Menampilkan pesan info pada terminal dengan teks berwarna hijau (tanpa new line)
 */
void log_info(char *message) {
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
        Size food_size = { food_width, food_height };
        Time processing_time = parse_time();
        enum Action action = parse_action();
        Food f;
        CreateFood(&f, id, name, expire, action, delivery, food_size, processing_time);
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
        Node *node = getNodeById(nodes, id, nodes_num);
        int num_child = parse_int();
        for (int k = 0; k < num_child; k++) {
            int id_child = parse_int();
            Node *child = getNodeById(nodes, id_child, nodes_num);
            MakeChildren(node, child);
        }
        CreateTree(&minor, node);
        Resep resep;
        CreateResep(&resep, minor);
        ResepListElmt(resepList, i) = resep;
    }

    CreatePrioQueue(&delivery_list, 100);
    CreateFridge(&fridge, 10, 10);
    CreateQueue(&notifications);
    CreateEmptyStack(&undoS);
    CreateEmptyStack(&redoS);
}

void display_notifikasi() {
    printf("\nNotifikasi: ");
    if (isEmptyQueue(notifications)) {
        printf("-\n");
    } else {
        printf("\n");
        int counter = 1;
        while (!isEmptyQueue(notifications)) {
            String notikasi;
            dequeue(&notifications, &notikasi);
            printf("   %d. %s\n", counter, STR_VALUE(notikasi));
            counter++;
        }
    }
}

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
    // program_time = NextMenit(program_time);
    program_time = NextNMenit(program_time, minute);
    for (int i = 0; i < lengthPrioQueue(simulator.inventory); i++) {
        Food food = getElmtAtIdxPrioqueue(simulator.inventory, i).food;
        Time t = getElmtAtIdxPrioqueue(simulator.inventory, i).time;
        // ELMTQUEUE(simulator.inventory, i).time = PrevNMenit(t, minute);
        int newTime = TIMEToMenit(t) - minute;
        if (newTime <= 0) {
            String notifikasi = StringFrom("\e[92m");
            notifikasi = concat_string(notifikasi, food.name);
            notifikasi = concat_string(notifikasi, StringFrom(" telah kedaluwarsa.\e[0m"));
            enqueue(&notifications, notifikasi);

            dequeuePrioQueue(&simulator.inventory, &food);
            i--;
        } else {
            ELMTQUEUE(simulator.inventory, i + simulator.inventory.idxHead).time = PrevNMenit(t, minute);
        }
    }
    for (int i = 0; i < lengthPrioQueue(delivery_list); i++) {
        Food food = getElmtAtIdxPrioqueue(delivery_list, i).food;
        Time t = getElmtAtIdxPrioqueue(delivery_list, i).time;
        int newTime = TIMEToMenit(t) - minute;
        if (newTime <= 0) {
            String notifikasi = StringFrom("\e[92m");
            notifikasi = concat_string(notifikasi, food.name);
            notifikasi = concat_string(notifikasi, StringFrom(" yang dipesan telah sampai di inventory.\e[0m"));
            enqueue(&notifications, notifikasi);

            dequeuePrioQueue(&delivery_list, &food);

            int newTimeAfterDelivery
              = TIMEToMenit(food.expiration_time) + newTime;  // catch for absurd amount of wait time

            if (newTimeAfterDelivery > 0) {
                enqueuePrioQueue(&simulator.inventory, (PQInfo){ food, MenitToTIME(newTimeAfterDelivery) });
            } else {
                notifikasi = StringFrom("\e[92m");
                notifikasi = concat_string(notifikasi, food.name);
                notifikasi = concat_string(notifikasi, StringFrom(" telah kedaluwarsa.\e[0m"));
                enqueue(&notifications, notifikasi);
            }

            i--;
        } else {
            ELMTQUEUE(delivery_list, i + delivery_list.idxHead).time = PrevNMenit(t, minute);
        }
    }
}

infoState copy_state(Simulator sim, String command, PriorityQueue deliv, Time time, Fridge fridge) {
    infoState state = { 0 };
    Simulator new_sim;
    CreateSimulator(&new_sim, sim.username, sim.location);
    deepcopyPrioQueue(&new_sim.inventory, sim.inventory);
    state.s = new_sim;
    deepcopyPrioQueue(&state.deliv, deliv);
    state.time = time;
    state.action = command;
    state.fridge = fridge;
    return state;
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
    setup_program(&simulator_location);  // setup program
    printf("\n");

    printf("Masukkan username: ");
    start_parser(stdin);
    String username = parse_line();
    CreateTime(&program_time, 0, 0, 0);
    CreateSimulator(&simulator, username, simulator_location);  // setup simulator
    boolean run = true;
    String temp = StringFrom("");

    while (run) {
        printf("Enter command (START/EXIT): ");
        start_parser(stdin);
        String command = parse_line();
        if (is_string_equal(command, StringFrom("START"))) {
            boolean quit = false;
            refresh_idle();
            while (!quit) {
                printf("Enter command: ");
                start_parser(stdin);
                String command = parse_line();
                if (is_string_startswith(command, StringFrom("MOVE"))) {
                    String arah = substring(command, 5, length(command));
                    infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                    if (execute_move(arah)) {
                        Push(&undoS, state);
                        CreateEmptyStack(&redoS);
                    }
                    printf("\n");
                    refresh_idle();
                } else if (is_string_startswith(command, StringFrom("WAIT"))) {
                    int wordCount, jam = 0, menit = 0;
                    String *cmdArray = split(command, ' ', &wordCount);

                    // if 'menit' provided
                    if (wordCount >= 3) {
                        menit = toInt(cmdArray[2]);
                    }
                    // if 'jam' provided
                    if (wordCount >= 2) {
                        jam = toInt(cmdArray[1]);
                    }
                    infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                    if (execute_wait(jam, menit)) {
                        Push(&undoS, state);
                        CreateEmptyStack(&redoS);
                    }

                    printf("\n");
                    refresh_idle();
                } else if (is_string_equal(command, StringFrom("BUY"))) {
                    if (IsBuySpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        Push(&undoS, state);

                        if (execute_buy()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }
                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi buy.\n");
                    }
                } else if (is_string_equal(command, StringFrom("MIX"))) {
                    if (IsMixSpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory;
                        deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;

                        if (execute_mix()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi mix.\n");
                    }
                } else if (is_string_equal(command, StringFrom("CHOP"))) {
                    if (IsChopSpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory;
                        deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;

                        if (execute_chop()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi chop.\n");
                    }
                } else if (is_string_equal(command, StringFrom("FRY"))) {
                    if (IsFrySpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory;
                        deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;

                        if (execute_fry()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi fry.\n");
                    }
                } else if (is_string_equal(command, StringFrom("BOIL"))) {
                    if (IsBoilSpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory;
                        deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;

                        if (execute_boil()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi boil.\n");
                    }
                } else if (is_string_equal(command, StringFrom("CATALOG"))) {
                    printf("\n");
                    printCatalog(foodlist);
                    printf("\n");
                } else if (is_string_equal(command, StringFrom("COOKBOOK"))) {
                    printf("\n");
                    printCookbook(resepList, foodlist);
                    printf("\n");
                } else if (is_string_equal(command, StringFrom("DELIVERY"))) {
                    printf("\n");
                    printf("List Makanan di Perjalanan\n");
                    printf("(nama - waktu sisa delivery)\n");
                    displayPrioqueue(delivery_list);
                    printf("\n");
                } else if (is_string_equal(command, StringFrom("INVENTORY"))) {
                    printf("\n");
                    printf("List Makanan di Inventory\n");
                    printf("(nama - waktu sisa ekspirasi)\n");
                    displayPrioqueue(Inventory(simulator));
                    printf("\n");
                } else if (is_string_equal(command, StringFrom("FRIDGE"))) {
                    if (IsFridgeSpace(map, Location(simulator))) {
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        if (execute_fridge()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }
                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi refrigerator.\n");
                    }
                } else if (is_string_equal(command, StringFrom("UNDO"))) {
                    if (IsEmptyStack(undoS)) {
                        printf("BNMO masih di state awal\n");  // mungkin sesuatu kaya "Already at oldest change" lebih
                                                               // cocok?
                    } else {
                        infoState temp;
                        Pop(&undoS, &temp);
                        infoState state = copy_state(simulator, ElmtAction(temp), delivery_list, program_time, fridge);
                        PriorityQueue tempInventory;
                        deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                        Push(&redoS, state);
                        execute_undo(temp);
                        String notifikasi = StringFrom("\e[92mCommand ");
                        notifikasi = concat_string(notifikasi, ElmtAction(temp));
                        notifikasi = concat_string(notifikasi, StringFrom(" telah dibatalkan.\e[0m"));
                        enqueue(&notifications, notifikasi);
                        refresh_idle();
                    }
                } else if (is_string_equal(command, StringFrom("REDO"))) {
                    if (IsEmptyStack(redoS)) {
                        printf("Tidak ada langkah yang bisa di redo\n");
                    } else {
                        infoState temp;
                        Pop(&redoS, &temp);
                        infoState state = copy_state(simulator, ElmtAction(temp), delivery_list, program_time, fridge);
                        Push(&undoS, state);
                        execute_redo(temp);
                        String notifikasi = StringFrom("\e[92mCommand ");
                        notifikasi = concat_string(notifikasi, ElmtAction(temp));
                        notifikasi = concat_string(notifikasi, StringFrom(" dijalankan kembali.\e[0m"));
                        enqueue(&notifications, notifikasi);
                        refresh_idle();
                    }
                } else if (is_string_equal(command, StringFrom("RECOMMEND"))) {
                    printf("\n");
                    execute_rekomendasi();
                    printf("\n");
                } else if (is_string_equal(command, StringFrom("EXIT"))) {
                    quit = true;
                    run = false;
                    printf("Simulator dimatikan\n");
                } else {
                    printf("\e[91mCommand tidak valid.\e[0m\n");
                }
                command = StringFrom("");
            }
        } else if (is_string_equal(command, StringFrom("EXIT"))) {
            run = false;
            printf("Simulator dimatikan\n");
        } else {
            printf("\e[91mCommand tidak valid.\e[0m\n");
        }
        command = StringFrom("");
    }
    printf("\e[?1049l");
    return 0;
}
