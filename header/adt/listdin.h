/* File: listdin.h */
/* Definisi ADT Dinamik List */

// hanya digunakan sementara untuk node dan tree
// expect further changes

#ifndef LISTDIN_H
#define LISTDIN_H

#include "boolean.h"
#include "cstring.h"

#define DEFAULT_CAPACITY 40
//i dont want to bloat the memory with food struct

#include "node.h"

// typedef Address* ListDin;
typedef struct listdin
{
    Address* head;
    int length;
    int capacity;
} ListDin;

//return Address*
#define HEAD(l) (l).head

//return int
#define LENGTH(l) (l).length

//return int
#define CAPACITY(l) (l).capacity

//get
int len(ListDin ld);

boolean isEmpty(ListDin ld);

boolean isFull(ListDin ld);


//method
void CreateListDin(ListDin* ld);

void printListDin(ListDin ld);

#endif
