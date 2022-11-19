#include <stdio.h>

#include "adt.h"
#include "boolean.h"
#include "commands.h"
#include "parser.h"

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
        if (getFoodWithIdxAction(foodlist, BUY, choice, &food)) {
            String food_name = food.name;
            Time delivery_time = food.delivery_time;
            printf("\n");
            printf("Berhasil memesan %s. %s akan diantar dalam ", STR_VALUE(food_name), STR_VALUE(food_name));
            TulisFoodTIME(delivery_time);
            printf("\n");

            add_program_time(1);
            enqueuePrioQueue(&delivery_list, (PQInfo){ food, delivery_time });

            success = true;
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    }

    return success;
}
