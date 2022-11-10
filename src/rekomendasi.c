#include "rekomendasi.h"

#include <stdio.h>
#include "food.h"
#include "foodlist.h"
#include "resep.h"

void execute_rekomendasi() {
    printf("---------------------------------\n");
    printf("| List makanan yang bisa dibuat |\n");
    printf("---------------------------------\n");
    int counter = 0;
    for (int i = 0; i < listLength(foodlist); i++) {
        Food food = ListElmt(foodlist, i);
        if (food.action_loc != BUY) {
            Resep resep;
            getResepWithFood(&resep, resepList, food);
            if (canMakeFromResep(resep, simulator)) {
                printf("  %d. %s - %s\n", ++counter, STR_VALUE(food.name), ActionName[food.action_loc]);
            }
        }
    }
    if (counter == 0) {
        printf("Tidak ada makanan yang bisa dibuat.\n");
    }
}
