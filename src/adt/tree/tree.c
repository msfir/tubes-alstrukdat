#include <stdio.h>
#include <stdlib.h>

#include "adt.h"

void CreateTree(Tree *a, Node *b) {
    *a = b;
}

void MakeChildren(Node *a, Node *b) {
    Address *childrenList = (Address *)malloc((getChildCount(*a) + 1) * sizeof(Address));
    int i;
    if (childrenList != NULL) {
        for (i = 0; i < getChildCount(*a); i++) {
            CHILD(childrenList, i) = CHILD(BUFFER(a), i);
        }
        CHILD(childrenList, getChildCount(*a)) = b;

        free(BUFFER(a));
        BUFFER(a) = childrenList;

        CHILD_COUNT(a)++;
    }
}

void listParent(Tree a, FoodList fl) {
    int i;
    Food tempParent, tempChild;
    for (i = 0; i < getChildCount(*a); i++) {
        getFoodById(fl, (INFO(a)), &tempParent);
        getFoodById(fl, INFO(NEXT(a, i)), &tempChild);
        printf("%s -> %s\n",
               STR_VALUE(Name(tempParent)),
               STR_VALUE(Name(tempChild)));  // ganti dengan nama food melalui foodlist
        if (NEXT(a, i) != NULL)
            listParent(NEXT(a, i), fl);
    }
}
