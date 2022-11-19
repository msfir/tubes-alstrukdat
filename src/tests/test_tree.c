#include <stdio.h>
#include "food.h"
#include "tree.h"
#include "node.h"
#include "time.h"
#include "cstring.h"

#include "foodlist.h"

#define teschilcount 4  //pls be <23

int main(){ 
    FoodList fdLi; CreateFoodList(&fdLi);
    Node childee[teschilcount];
    Time contohTime; CreateTime(&contohTime, 23, 0, 0);
    Food ayam[teschilcount]; 
    Size size; size.width = 1; size.height = 2;
    int i; String uniqname; char uniqid;
    for(i = 0; i<teschilcount; i++){
        uniqid = 65 + i;
        uniqname = StringFrom("");
        uniqname = concat_string(StringFrom("ayam rasa hati yang terluka tipe "), StringFrom(&uniqid));
        CreateFood(&ayam[i], 101+uniqid, uniqname, contohTime, BUY, contohTime, size, contohTime);
        addFood(&fdLi, ayam[i]);
    }
    Food gigachadFood; CreateFood(&gigachadFood, 1000, StringFrom("parent ayam"), contohTime, BOIL, contohTime, size, contohTime);
    addFood(&fdLi, gigachadFood);


    Node basse = *newNode(Id(gigachadFood)); // lets use this
    Tree trie; CreateTree(&trie, &basse);
    
    
    for(i = 0; i<teschilcount; i++){
        childee[i] = *newNode(Id(ayam[i]));
    }
    
    MakeChildren(&basse, &childee[0]);
    MakeChildren(&basse, &childee[1]);
    MakeChildren(&childee[1], &childee[2]);
    MakeChildren(&childee[1], &childee[3]);

    listParent(trie, fdLi);
    

    return 0;
}
