#include "commands.h"
#include "parser.h"
#include "logger.h"

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
                printf("%d. %s - ", i + 1, STR_VALUE(food.name));
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
                    enqueuePrioQueue(&simulator.inventory, (PQInfo){ food, ExpirationTime(food) });
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
