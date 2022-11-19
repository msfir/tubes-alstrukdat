#include <assert.h>
#include <stdio.h>

#include "adt.h"
#include "boolean.h"

int main() {
    printf("--- Driver Test PriorityQueue ---");
    printf("\n");
    printf("\n");
    int Capacity;
    PriorityQueue val;
    PQInfo x;
    Food food = { .name = StringFrom("Baso nuklir"),
                  .id = 110,
                  .delivery_time = (Time){ 5, 5, 5 },
                  .expiration_time = (Time){ 365, 0, 0 },
                  .processing_time = (Time){ 3650, 0, 0 },
                  .action_loc = BUY,
                  .size = (Size){ 20, 20 } };
    char input;

    CreatePrioQueue(&val, 100);

    assert(isEmptyPrioQueue(val));

    Capacity = lengthPrioQueue(val);

    enqueuePrioQueue(&val, (PQInfo){ food, food.expiration_time });
    assert(!isEmptyPrioQueue(val));
    assert(lengthPrioQueue(val) == 1);

    displayPrioqueue(val);

    dequeuePrioQueue(&val, &food);
    assert(isEmptyPrioQueue(val));
    assert(lengthPrioQueue(val) == 0);

    displayPrioqueue(val);

    dealocatePrioQueue(&val);

    printf("\n");
    printf("--------------------------------\n");
    printf("\n");
    printf("\n");
}
