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
    Address* next; // using a new dyn list
    int childCount; // where i store the childd!!!!!!!!!!!!!!!!!!!!!!!!!!1
} Node;

//return Food*
#define INFO(p) (p)->info

//return ListDin
// #define NEXT_LISTDIN(p) (p)->next

//return Address
// #define NEXT_ELMT(p, idx) ELMT(*NEXT_LISTDIN(p), (idx))

//return Address*
#define BUFFER(p) (p)->next

// return Address
#define NEXT(p, idx) *((p)->next+idx)

//return int
#define CHILD_COUNT(p) (p)->childCount

// void CreateNode(Node *a, Food *b);
Address newNode(Food *a);

int getChildCount(Node a);


#endif
