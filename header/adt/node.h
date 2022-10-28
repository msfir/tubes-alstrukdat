#ifndef NODE_H
#define NODE_H

#include "food.h"

typedef struct node* Address;
typedef struct node
{
    Food *info;
    Address* next; //list of children
    int childCount;
} Node;

//return Food*
#define INFO(p) (p)->info

//return Address*
#define BUFFER(p) (p)->next

// return Address
#define NEXT(p, idx) *((p)->next+idx)

//return int
#define CHILD_COUNT(p) (p)->childCount



Address newNode(Food *a);

int getChildCount(Node a);


#endif
