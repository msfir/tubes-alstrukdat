#include "resep.h"

#include "boolean.h"

// Resep undefinedResep() {
//     Address undefNode; undefNode = newNode(MARK);
//     Tree undefTree; CreateTree(&undefTree, undefNode);
//     Resep undefResep; CreateResep(&undefResep, undefTree);
//
//     return undefResep;
// }



int resepListLength(ResepList rl){
    int i = IDX_MIN;
    while (ListElmt(rl, i) != NULL /* undefinedResep() */ && i < CAPACITY) {
        i++;
    }
    return i;
}

void CreateResep(Resep* r, Tree t){
    //createtree terlebih dulu dan assign sebagai resep
    *r = t;
}

void CreateResepList(ResepList* rl){
    int i;
    for (i = 0; i < CAPACITY; i++) {
        ResepListElmt(*rl, i) = NULL /* undefinedResep() */; // MARK Resep
    }
}


boolean canMakeFromResep(Resep r, Simulator s){
    boolean canMade = true;

    // if(INFO(Resep) )
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
    if(hasResep(rl, f)){
        int i; 
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
