#include <stdio.h>
#include <stdlib.h>

#include "adt.h"

Address newNode(int id){
    Address res = (Address) malloc(sizeof(Node));
    if(res != NULL){
        INFO(res) = id;
        CHILD_COUNT(res) = 0;
        BUFFER(res) = NULL;
    }

    return res;
}

int getChildCount(Node a) {
    return CHILD_COUNT(&a);
}

Address getNodeById(Address *nodes, int id, int size) {
    Address node;
    boolean found = false;
    for (int i = 0; i < size && !found; i++) {
        if (INFO(nodes[i]) == id) {
            found = true;
            node = nodes[i];
        }
    }
    return node;
}
