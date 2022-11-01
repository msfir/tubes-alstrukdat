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
    printf("1");
    Node childee[teschilcount];
    Time dmytm; CreateTime(&dmytm, 23, 0, 0);
    enum Action acloc;
    Food ayam[teschilcount]; 
    printf("1");
    int i; String uniqname; char uniqid;
    for(i = 0; i<teschilcount; i++){
        uniqid = 65 + i;
        uniqname = StringFrom("");
        uniqname = concat_string(StringFrom("ayam rasa hati yang terluka tipe "), StringFrom(&uniqid));
        CreateFood(&ayam[i], 101+uniqid, uniqname, dmytm, acloc, dmytm);
        addFood(&fdLi, ayam[i]);
    }
    Food gigachadFood; CreateFood(&gigachadFood, 1000, StringFrom("parent ayam"), dmytm, acloc, dmytm);
    addFood(&fdLi, gigachadFood);

    printf("1");

    Node basse = *newNode(Id(gigachadFood)); // lets use this
    Tree trie; CreateTree(&trie, &basse);
    
    
    for(i = 0; i<teschilcount; i++){
        childee[i] = *newNode(Id(ayam[i]));
    } printf("  newnode ");
    
    MakeChildren(&basse, &childee[0]);
    MakeChildren(&basse, &childee[1]);
    MakeChildren(&childee[1], &childee[2]);
    MakeChildren(&childee[1], &childee[3]);
    printf("  newnode ");
    listParent(trie, fdLi);
    printf("lp");
    listChildren(trie, fdLi);
    

    return 0;
}
