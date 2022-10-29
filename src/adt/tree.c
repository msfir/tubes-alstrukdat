#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "node.h"
// #include "listlinier.h"

void CreateTree(Tree *a, Node *b){
    // a = newNode(1); // idk whether shud i number it accordingly or no, or maybe just change it to Food altogether
    *a = b;
}

void MakeChildren(Node *a, Node *b){
    Address* childrenList = (Address*) malloc((getChildCount(*a)+1) * sizeof(Address));
    int i;
    if (childrenList != NULL){
        for (i = 0; i<getChildCount(*a); i++){
            ELMT(childrenList, i) = ELMT(BUFFER(a), i);
        }
        ELMT(childrenList, getChildCount(*a)) = b;

        free(BUFFER(a));
        BUFFER(a) = childrenList;

        CHILD_COUNT(a)++;
    }

}

void listParent(Tree a){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%d -> %d\n", INFO(a), INFO(NEXT(a, i)));
        if(NEXT(a, i) != NULL) listParent(NEXT(a, i));
    }
}

void listChildren(Tree a){
    int i, j;
    for(i = 0; i<getChildCount(*a); i++){        
        // printf("%s -> ", STR_VALUE(INFO(a)->name));
        // for(j = 0; j < getChildCount(*a); j++){
        //     if(j!=0) printf(", ");
        //     // printf("%s", STR_VALUE(INFO(NEXT_ELMT(a, j))->name));
        // }
        // printf("\n");
        // // if(NEXT_ELMT(a, i) != NULL) {listParent(NEXT_ELMT(a, i));}
    }
}

int getDegree(Tree a, Node b){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        // printf("%s -> %s\n", STR_VALUE(INFO(a)->name), STR_VALUE(INFO(NEXT_ELMT(a, i))->name));
        // if(NEXT_ELMT(a, i) != NULL) {listParent(NEXT_ELMT(a, i));}
    }
}