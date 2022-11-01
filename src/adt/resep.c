#include "resep.h"

#include "tree.h"
#include "boolean.h"

Resep undefinedResep() {
    Address undefNode; undefNode = newNode(MARK);
    Tree undefTree; CreateTree(&undefTree, undefNode);
    Resep undefResep; CreateResep(&undefResep, undefTree);

    return undefResep;
}



int resepListLength(ResepList rl){
    int i = IDX_MIN;
    while (ListElmt(rl, i) != undefinedResep() && i < CAPACITY) {
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
        ResepListElmt(*rl, i) = undefinedResep(); // MARK Resep
    }
}


boolean canResepMade(Resep r, FoodList fl){

}

boolean hasResep(ResepList rl, Food f){
    boolean found = false;
    int i;
    for(i=0; i<resepListLength(rl); i++){
        if (INFO(ResepListElmt(rl, i)) == Id(f)){
            found = true;
        }
    }
    
    return found;
}