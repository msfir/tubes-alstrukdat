#include <stdio.h>

#include "adt.h"
#include "commands.h"

void execute_rekomendasi() {
    Set inventory_set;
    CreateEmptySet(&inventory_set);
    Set recom;
    CreateEmptySet(&recom);
    for (int i = simulator.inventory.idxHead; i <= simulator.inventory.idxTail; i++) {
        set_add(&inventory_set, simulator.inventory.buffer[i].food.id);
    }
    for (int i = 0; i < resepListLength(resepList); i++) {
        Set req;
        CreateEmptySet(&req);
        Resep resep = resepList.buffer[i];
        for (int j = 0; j < resep->childCount; j++) {
            set_add(&req, resep->next[j]->info);
        }
        if (set_is_subset(req, inventory_set)) {
            set_add(&recom, resep->info);
        }
    }

    printf("---------------------------------\n");
    printf("| List makanan yang bisa dibuat |\n");
    printf("---------------------------------\n");
    if (set_is_empty(recom)) {
        printf("Tidak ada makanan yang bisa dibuat.\n");
    } else {
        for (int i = 0; i < recom.length; i++) {
            Food food;
            getFoodById(foodlist, ELMT_SET(recom, i), &food);
            printf("  %d. %s - %s\n", i + 1, STR_VALUE(food.name), ActionName[food.action_loc]);
        }
    }
}
