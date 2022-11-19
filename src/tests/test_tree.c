#include <stdio.h>

#include "adt.h"

#define tesMaxChild 4

int main() {
    printf("--- Driver Test Tree ---");
    printf("\n");
    printf("\n");
    FoodList foodList;
    CreateFoodList(&foodList);
    Time contohTime;
    CreateTime(&contohTime, 23, 0, 0);

    Node child[tesMaxChild];

    Food ayam[tesMaxChild];
    Size size;
    size.width = 1;
    size.height = 2;

    int i;
    String uniqname;
    char uniqid;

    for (i = 0; i < tesMaxChild; i++) {
        uniqid = 65 + i;
        uniqname = StringFrom("");
        uniqname = concat_string(StringFrom("ayam rasa hati yang terluka tipe "), StringFrom(&uniqid));
        CreateFood(&ayam[i], 101 + uniqid, uniqname, contohTime, BUY, contohTime, size, contohTime);
        addFood(&foodList, ayam[i]);
    }

    Food gigachadAyam;
    CreateFood(&gigachadAyam, 1000, StringFrom("parent ayam"), contohTime, MIX, contohTime, size, contohTime);
    addFood(&foodList, gigachadAyam);

    // buat node parent
    Node parent = *newNode(Id(gigachadAyam));

    // buat tree
    Tree treeAyam;
    CreateTree(&treeAyam, &parent);

    // buat node children
    for (i = 0; i < tesMaxChild; i++) {
        child[i] = *newNode(Id(ayam[i]));
    }

    // sambungkan parent dengan child
    MakeChildren(&parent, &child[0]);
    MakeChildren(&parent, &child[1]);
    MakeChildren(&child[1], &child[2]);
    MakeChildren(&child[1], &child[3]);

    // tampilkan
    listParent(treeAyam, foodList);

    printf("\n");
    printf("------------------------");
    printf("\n");
    printf("\n");
    return 0;
}
