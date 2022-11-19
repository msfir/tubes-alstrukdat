#include <stdio.h>

#include "adt.h"

int main() {
    printf("--- Driver Test Resep ---");
    printf("\n");
    printf("\n");

    // contohFood
    Time contohTime;
    CreateTime(&contohTime, 1, 2, 3);
    Size size;
    size.width = 1;
    size.height = 2;
    Food ayam;
    CreateFood(
      &ayam, 420, StringFrom("ayam rasa bebek"), contohTime, MIX, PrevNMenit(contohTime, 3600), size, MenitToTIME(0));

    FoodList foodList;
    CreateFoodList(&foodList);
    addFood(&foodList, ayam);

    // resep
    Resep resep;
    ResepList resepList;
    Address foodNode = newNode(Id(ayam));
    Tree foodTree;
    CreateTree(&foodTree, foodNode);

    CreateResep(&resep, foodTree);
    ResepListElmt(resepList, 0) = resep;

    printCookbook(resepList, foodList);

    printf("\n");
    printf("--- Driver Test Resep ---");
    printf("\n");
    printf("\n");
    return 0;
}
