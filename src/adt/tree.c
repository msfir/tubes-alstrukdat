#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "node.h"
#include "foodlist.h"


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

void listParent(Tree a, FoodList fl){
    int i;
    for(i = 0; i<getChildCount(*a); i++){        
        printf("%d -> %d\n", INFO(a), INFO(NEXT(a, i))); //ganti dengan nama food melalui foodlist
        if(NEXT(a, i) != NULL) listParent(NEXT(a, i), fl);
    }
}

void listChildren(Tree a, FoodList fl){
    int i, j;
    for(i = 0; i<getChildCount(*a); i++){        
        //todo
    }
}

void getAllReachableNode(Tree a, Node* nodes[]){

}