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
    //add warning if passing the limit amount of children
}

void listParent(Tree a){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%s -> %s\n", STR_VALUE(INFO(a)->name), STR_VALUE(INFO(NEXT(a, i))->name));
        if(NEXT(a, i) != NULL) {listParent(NEXT(a, i));}
    }
}

void listChildren(Tree a){
    int i, j;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%s -> ", STR_VALUE(INFO(a)->name));
        for(j = 0; j < getChildCount(*a); j++){
            if(j!=0) printf(", ");
            printf("%s", STR_VALUE(INFO(NEXT(a, j))->name));
        }
        printf("\n");
        if(NEXT(a, i) != NULL) {listParent(NEXT(a, i));}
    }
}

int getDegree(Tree a, Node b){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%s -> %s\n", STR_VALUE(INFO(a)->name), STR_VALUE(INFO(NEXT(a, i))->name));
        if(NEXT(a, i) != NULL) {listParent(NEXT(a, i));}
    }
}