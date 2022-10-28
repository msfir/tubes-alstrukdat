#ifndef NODE_H
#define NODE_H

#define MAX_CHILDREN 5 //assuming so

// #include "listdin.h"
#include "food.h"

// struct ListDin;

typedef struct node* Address;
typedef struct node
{
    Food *info;
    // struct ListDin *next;
} Node;

//return Food*
#define INFO(p) (p)->info

//return ListDin
// #define NEXT_LISTDIN(p) (p)->next

//return Address
// #define NEXT_ELMT(p, idx) ELMT(*NEXT_LISTDIN(p), (idx))

// void CreateNode(Node *a, Food *b);
Address newNode(Food *a);

int getChildCount(Node a);


#endif
