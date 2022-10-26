#include <stdio.h>
#include "tree.h"
#include "node.h"
// #include "listlinier.h"

void CreateTree(Tree *a, Node *b){
    // a = newNode(1); // idk whether shud i number it accordingly or no, or maybe just change it to Food altogether
    *a = b;
}

void MakeChildren(Node *a, Node *b){
    if(getChildCount(*a) < MAX_CHILDREN){
        NEXT(a, getChildCount(*a)) = b;
    }
}

void listParent(Tree a){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%s -> %s\n", STR_VALUE(INFO(a)->name), STR_VALUE(INFO(NEXT(a, i))->name));
        if(NEXT(a, i) != NULL) {listParent(NEXT(a, i));}
    }
}
