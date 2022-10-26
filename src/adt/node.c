#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Address newNode(Food *a){
    Address res = (Address) malloc(sizeof(Node));

    if(res != NULL){
        INFO(res) = a;
        
        int i;
        for(i = 0; i<MAX_CHILDREN; i++){
            NEXT(res, i) = NULL;
        }
    }

    return res;
}

int getChildCount(Node a){
    int i, res = 0;
    for(i = 0; i < MAX_CHILDREN; i++){
        if(NEXT(&a, i) != NULL) res++;
    }

    return res;
}