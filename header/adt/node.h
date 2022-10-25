#ifndef node_h
#define node_h

#define MAX_CHILDREN 5 //assuming so

#include "food.h"

typedef struct node* Address;
typedef struct node
{
    Food *info; //address
    Address next[MAX_CHILDREN];
} Node;

#define INFO(p) (p)->info
#define NEXT(p, idx) (p)->next[(idx)]

// void CreateNode(Node *a, Food *b);
Address newNode(Food *a);

int getChildCount(Node a);


#endif // !node_h
