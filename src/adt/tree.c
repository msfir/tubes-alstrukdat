#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "node.h"


void CreateTree(Tree *a, Node *b){
    *a = b;
}

void MakeChildren(Node *a, Node *b){
    Address* childrenList = (Address*) malloc((getChildCount(*a)+1) * sizeof(Address));
    int i;
    if (childrenList != NULL){
        for (i = 0; i<getChildCount(*a); i++){
            CHILD(childrenList, i) = CHILD(BUFFER(a), i);
        }
        CHILD(childrenList, getChildCount(*a)) = b;

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
        //todo
    }
}

int getDegree(Tree a, Node b){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        //todo
    }
}