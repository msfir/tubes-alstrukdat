#include "resep.h"

#include "boolean.h"


int resepListLength(ResepList rl){
    int i = IDX_MIN;
    while (ListElmt(rl, i) != NULL && i < CAPACITY) {
        i++;
    }
    return i;
}

void CreateResep(Resep* r, Tree t){
    *r = t;
}

void CreateResepList(ResepList* rl){
    int i;
    for (i = 0; i < CAPACITY; i++) {
        ResepListElmt(*rl, i) = NULL;
    }
}

void printCookbook(ResepList rl, FoodList fl){
    Food foodToPrint; Resep resepToPrint; 
    printf("List Resep\n");
    printf(" (aksi yang diperlukan - bahan..)\n");

    for(int i = 0; i < resepListLength(rl); i++){
        resepToPrint = ResepListElmt(rl, i);
        getFoodById(fl, INFO(ROOT(resepToPrint)), &foodToPrint);
        printf("%d. %s\n", i+1, STR_VALUE(Name(foodToPrint)));
        printf("%s", ActionName[ActionLocation(foodToPrint)]);

        for(int j = 0; j < CHILD_COUNT(ROOT(resepToPrint)); j++){
            getFoodById(fl, INFO(NEXT(ROOT(resepToPrint), j)), &foodToPrint);
            printf(" - %s", STR_VALUE(Name(foodToPrint)));
        }

        printf("\n");
    }
}

boolean canMakeFromResep(Resep r, Simulator s){
    boolean canMade = true;

    int i;
    for(i = 0; i<CHILD_COUNT(ROOT(r)); i++){
        if(!isInPrioqueue(Inventory(s), INFO(NEXT(ROOT(r), i)))){
            canMade = false;
        }
    }

    return canMade;
}

boolean hasResep(ResepList rl, Food f){
    boolean found = false;
    int i;
    for(i=0; i<resepListLength(rl) && !found; i++){
        if (INFO(ResepListElmt(rl, i)) == Id(f)){
            found = true;
        }
    }
    
    return found;
}

boolean getResepWithFood(Resep* resep, ResepList rl, Food f){
    boolean found = false;
    int i = 0; 
    if(hasResep(rl, f)){
        while(!found && i < resepListLength(rl)){
            if (INFO(ResepListElmt(rl, i)) == Id(f)){
                *resep = ResepListElmt(rl, i);

                found = true;
            }
            i++;
        }
    }
    return found; 
}