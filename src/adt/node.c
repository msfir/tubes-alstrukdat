#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "listdin.h"

Address newNode(Food *a){
    Address res = (Address) malloc(sizeof(Node));
    // ListDin lmao; CreateListDin(&lmao, 2);
    if(res != NULL){
        INFO(res) = a;
        
        // int i;
        // for(i = 0; i<MAX_CHILDREN; i++){
        //     NEXT(res, i) = NULL;
        // }

        // CreateListDin(&NEXT_LISTDIN(res), MAX_CHILDREN); // create a new dynarr with 0 element
    }

    return res;
}

int getChildCount(Node a){
    int i, res = 0;
    for(i = 0; i < MAX_CHILDREN; i++){
        // if(NEXT_ELMT(&a, i) != NULL) res++;
    }

    return res;
}