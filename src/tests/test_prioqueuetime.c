#include <stdio.h>
#include "boolean.h"
#include "prioqueuetime.h"
#include "food.h"

int main() {

    int Capacity;
    PriorityQueue val;
    PQInfo x;
    Food food;
    char input;

    CreatePrioQueue(&val, 100);

    if (isEmptyPrioQueue(val)) {
        printf("Inventory Kosong!\n");
    } else if (isFullPrioQueue(val)) {
        printf("Inventory Penuh!\n");
    }
 
    Capacity = lengthPrioQueue(val);

    int newTimeAfterDelivery;
    scanf("%c", &input);
    if (input == 'i') {
        enqueuePrioQueue(&val, (PQInfo) {food, MenitToTIME(newTimeAfterDelivery)});
    } else {
        dequeuePrioQueue(&val, &food);
    }

    displayPrioqueue(val);
    printf("\n");
    
    dealocatePrioQueue(&val);
}
