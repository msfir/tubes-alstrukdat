#include <stdio.h>
#include <assert.h>

#include "food.h"
#include "foodlist.h"
#include "time.h"

int main() {
    printf("--- Driver Test FoodList ---");
    printf("\n")   ;
    printf("\n")   ;
    FoodList list;
    CreateFoodList(&list);

    assert(listLength(list) == 0);
    assert(isEmptyFood(list) == true);
    assert(getFirstIdx(list) == IDX_UNDEF);
    assert(getLastIdx(list) == IDX_UNDEF);

    Food food;
    Time expire;
    CreateTime(&expire, 0, 1, 0);
    Time delivery;
    Size size;
    size.width = 10, size.height = 10;
    CreateTime(&delivery, 0, 0, 10);
    CreateFood(&food, 99, StringFrom("Indomie"), expire, BUY, delivery,size, (Time) {1, 1, 1});
    size.height = 1; size.width = 1;
    Time process;
    CreateTime(&process, 0, 0, 0);
    CreateFood(&food, 99, StringFrom("Indomie"), expire, BUY, delivery, size, process);
    addFood(&list, food);

    assert(listLength(list) == 1);
    assert(isEmptyFood(list) == false);
    assert(getFirstIdx(list) == 0);
    assert(getLastIdx(list) == 0);

    CreateTime(&expire, 0, 0, 30);
    CreateTime(&delivery, 0, 0, 45);
    CreateFood(&food, 22, StringFrom("Mie sedap"), expire, BUY, delivery,size, process);

    CreateTime(&process, 0, 0, 13);
    CreateFood(&food, 22, StringFrom("Mie sedap"), expire, BUY, delivery, size, process);
    addFood(&list, food);

    assert(listLength(list) == 2);
    assert(isEmptyFood(list) == false);
    assert(getFirstIdx(list) == 0);
    assert(getLastIdx(list) == 1);

    printBuyList(list);
    printMixList(list);
    printCatalog(list);

    printf("\n")   ;
    printf("--- Driver Test FoodList ---");
    printf("\n")   ;
    printf("\n")   ;
    return 0;
}
