#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Address newNode(Food *a){
    Address res = (Address) malloc(sizeof(Node));
    // ListDin lmao; CreateListDin(&lmao, 2);
    if(res != NULL){
        INFO(res) = a;
        CHILD_COUNT(res) = 0;
        BUFFER(res) = NULL;
    }

    return res;
}

int getChildCount(Node a){
    return CHILD_COUNT(&a);
}