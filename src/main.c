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
#include "stack.h"
#include "rekomendasi.h"

#define MAX_RESEP 100

static Matrix map;
ResepList resepList;
FoodList foodlist;
static Time program_time;
Simulator simulator;
static Queue notifications;
static PriorityQueue delivery_list;
static Fridge fridge;
static Stack undoS, redoS;

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

            int newTimeAfterDelivery = TIMEToMenit(food.expiration_time) + newTime; // catch for absurd amount of wait time
            
            if (newTimeAfterDelivery > 0){
                enqueuePrioQueue(&simulator.inventory, (PQInfo) {food, MenitToTIME(newTimeAfterDelivery)});  
            }   else {
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

boolean execute_buy() {
    boolean success = false;

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

            success = true;
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }

    return success;
}

boolean execute_move(String arah) {
    printf("\n");
    Point temp = Location(simulator);
    if (is_string_equal(arah, StringFrom("NORTH"))){
        SimulatorMove(&simulator, Location(simulator), &map, -1, 0);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("EAST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, 1);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("SOUTH"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 1, 0);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
            return true;
        }
    } else if (is_string_equal(arah, StringFrom("WEST"))) {
        SimulatorMove(&simulator, Location(simulator), &map, 0, -1);
        if (!EQ(temp, Location(simulator)) ){
            add_program_time(1);
            return true;
        }
    } else{
        log_error("Command tidak valid.\n");
    }

    return false;
}

boolean execute_fry() { 
    boolean success = false;

    printFryList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) { // RETURN WILL CAUSE THIS LOOP TO BREAK
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
                    success = true;
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

    return success;
}

boolean execute_mix() {
    boolean success = false;

    printMixList(foodlist);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    int choice = 1;
    while (choice != 0) { // RETURN WILL CAUSE THIS LOOP TO BREAK
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
                    success = true;
                    
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

    return success;
}

boolean execute_chop() {
    boolean success = false;

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
                    success = true;
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

    return success;
}

boolean execute_boil() {
    boolean success;

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
                    success = true;
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

    return success;
}

boolean execute_fridge() {
    boolean changed = false;
    printf("\n");
    display_fridge(fridge);
    printf("\n");

    boolean closed = false;
    while (!closed) {
        printf("Enter command: ");
        start_parser(stdin);
        String command = parse_line();

        if (is_string_equal(command, StringFrom("PUT"))) {
            printf("\n");
            printf("List makanan di inventory \n");
            printf("(Nama - Waktu kedaluwarsa - Ukuran)\n");
            for (int i = 0; i < lengthPrioQueue(Inventory(simulator)); i++) {
                PQInfo info = getElmtAtIdxPrioqueue(simulator.inventory, i);
                Food food = info.food;
                printf("%d. %s - ", i+1, STR_VALUE(food.name));
                TulisFoodTIME(info.time);
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
                PQInfo info = getElmtAtIdxPrioqueue(simulator.inventory, choice - 1);
                Food food = info.food;
                if (can_put(fridge, row, col, food)) {
                    food.expiration_time = info.time;
                    put_food(&fridge, row, col, food);
                    printf("\n");
                    display_fridge(fridge);
                    printf("\n");
                    printf("\e[92mBerhasil menyimpan %s ke dalam kulkas.\n\e[0m", STR_VALUE(food.name));
                    printf("\n");
                    changed = true;
                    valid = true;
                    removeAtPrioqueue(&simulator.inventory, choice - 1, &food);
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
                    changed = true;
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
        } else {
            log_error("Command tidak valid.\n");
        }
    }
    return changed;
}

boolean execute_wait(int jam, int menit){
    int deltaTime = 60*jam+menit;

    if (deltaTime > 0 && jam >= 0 && menit >= 0){
        add_program_time(deltaTime);
        return true;
    }
    
    return false;
}

void execute_undo(infoState temp){
    Point prev_loc = simulator.location;

    PriorityQueue inv = simulator.inventory;
    PriorityQueue deliv = delivery_list;

    // dealocatePrioQueue(&Inventory(simulator));

    simulator = ElmtSimulator(temp);
    
    float deltaX = Absis(simulator.location) - Absis(prev_loc);
    float deltaY = Ordinat(simulator.location) - Ordinat(prev_loc);
    SimulatorMove(&simulator, prev_loc, &map, deltaX, deltaY);
    delivery_list = ElmtDelivery(temp);
    program_time = ElmtTime(temp);
    fridge = temp.fridge;

    dealocatePrioQueue(&inv);
    dealocatePrioQueue(&deliv);
}

void execute_redo(infoState temp){
    PriorityQueue inv = simulator.inventory;
    PriorityQueue deliv = delivery_list;
    Point prev_loc = simulator.location;
    simulator = ElmtSimulator(temp);
    float deltaX = Absis(simulator.location) - Absis(prev_loc);
    float deltaY = Ordinat(simulator.location) - Ordinat(prev_loc);
    SimulatorMove(&simulator, prev_loc, &map, deltaX, deltaY);
    delivery_list = ElmtDelivery(temp);
    program_time = ElmtTime(temp);
    fridge = temp.fridge;

    dealocatePrioQueue(&inv);
    dealocatePrioQueue(&deliv);
}

infoState copy_state(Simulator sim, String command, PriorityQueue deliv, Time time, Fridge fridge) {
    infoState state = {0};
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
    setup_program(&simulator_location); //setup program
    printf("\n");

    printf("Masukkan username: ");
    start_parser(stdin);
    String username = parse_line();
    CreateTime(&program_time, 0, 0, 0);
    CreateSimulator(&simulator, username, simulator_location); //setup simulator
    boolean run = true;
    String temp = StringFrom("");
    
    while (run){ 
        printf("Enter command (START/EXIT): ");
        start_parser(stdin);
        String command = parse_line();
        if (is_string_equal(command, StringFrom("START"))){
            boolean quit=false;
            refresh_idle();
            while (!quit) {
                printf("Enter command: ");
                start_parser(stdin);
                String command = parse_line();
                if (is_string_startswith(command, StringFrom("MOVE"))) {
                    String arah = substring(command, 5, length(command));
                    infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                    if (execute_move(arah)){
                        Push(&undoS, state);
                        CreateEmptyStack(&redoS);
                    }
                    printf("\n");
                    refresh_idle();
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
                    infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                    if (execute_wait(jam, menit)){
                        Push(&undoS, state);
                        CreateEmptyStack(&redoS);
                    }
                    
                    printf("\n");
                    refresh_idle();
                } else if (is_string_equal(command, StringFrom("BUY"))) {
                    if (IsBuySpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        Push(&undoS, state);
                        
                        if(execute_buy()){
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }
                        printf("\n");
                        refresh_idle();
                    }else{
                        log_error("Tidak berada di lokasi buy.\n");
                    }
                } else if (is_string_equal(command, StringFrom("MIX"))) {
                    if (IsMixSpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory; deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                        
                        if(execute_mix()){
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    }else{
                        log_error("Tidak berada di lokasi mix.\n");
                    }
                } else if (is_string_equal(command, StringFrom("CHOP"))) {
                    if (IsChopSpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory; deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                        
                        if(execute_chop()){
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    } else {
                        log_error("Tidak berada di lokasi chop.\n");
                    }
                } else if (is_string_equal(command, StringFrom("FRY"))) {
                    if (IsFrySpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory; deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                    
                        if(execute_fry()){
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }

                        printf("\n");
                        refresh_idle();
                    }else{
                        log_error("Tidak berada di lokasi fry.\n");
                    }
                } else if (is_string_equal(command, StringFrom("BOIL"))) {
                    if (IsBoilSpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        PriorityQueue tempInventory; deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                        
                        if(execute_boil()){
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }
                        
                        printf("\n");
                        refresh_idle();
                    }else{
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
                    if (IsFridgeSpace(map, Location(simulator))){
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
                        if(execute_fridge()) {
                            Push(&undoS, state);
                            CreateEmptyStack(&redoS);
                        }
                        printf("\n");
                        refresh_idle();
                    }else{
                        log_error("Tidak berada di lokasi refrigerator.\n");
                    }
                } else if (is_string_equal(command, StringFrom("UNDO"))){
                    if (IsEmptyStack(undoS)){
                        printf("BNMO masih di state awal\n"); // mungkin sesuatu kaya "Already at oldest change" lebih cocok?
                    }else{
                        infoState temp;
                        Pop(&undoS, &temp);
                        infoState state = copy_state(simulator, ElmtAction(temp), delivery_list, program_time, fridge);
                        PriorityQueue tempInventory; deepcopyPrioQueue(&tempInventory, Inventory(ElmtSimulator(state)));
                        Inventory(ElmtSimulator(state)) = tempInventory;
                        Push(&redoS, state);
                        execute_undo(temp);
                        String notifikasi = StringFrom("\e[92mCommand ");
                        notifikasi = concat_string(notifikasi, ElmtAction(temp));
                        notifikasi = concat_string(notifikasi, StringFrom(" telah dibatalkan.\e[0m"));
                        enqueue(&notifications, notifikasi);
                        refresh_idle();
                    }
                } else if (is_string_equal(command, StringFrom("REDO"))){
                    if (IsEmptyStack(redoS)){
                        printf("Tidak ada langkah yang bisa di redo\n");
                    }else{
                        infoState temp;
                        Pop(&redoS, &temp);
                        infoState state = copy_state(simulator, command, delivery_list, program_time, fridge);
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
        }else if (is_string_equal(command, StringFrom("EXIT"))) {
            run = false;
            printf("Simulator dimatikan\n");
        }else{
            printf("\e[91mCommand tidak valid.\e[0m\n");
        }
        command = StringFrom("");
    }
    printf("\e[?1049l");
    return 0;
}
