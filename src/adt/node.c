#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Address newNode(int id){
    Address res = (Address) malloc(sizeof(Node));
    if(res != NULL){
        INFO(res) = id;
        CHILD_COUNT(res) = 0;
        BUFFER(res) = NULL;
    }

    return res;
}

int getChildCount(Node a){
    return CHILD_COUNT(&a);
}