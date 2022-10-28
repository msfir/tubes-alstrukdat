/* File: listdin.h */
/* Definisi ADT Dinamik List */

// hanya digunakan sementara untuk node dan tree
// expect further changes

#ifndef LISTDIN_H
#define LISTDIN_H

#include "boolean.h"
#include "cstring.h"


#include "node.h"

// typedef Address* ListDin;
typedef struct listdin
{
    Address* buffer;
    int listLength;
    int capacity;
} ListDin;

//return Address*
#define BUFFER(l) (l).buffer
//return Address
#define ELMT(l, idx) (l).buffer[idx]
//return int
#define LISTLEN(l) (l).listLength
//return int
#define CAPACITY(l) (l).capacity

//get
int len(ListDin ld);

boolean isEmpty(ListDin ld);

boolean isFull(ListDin ld);


//method
void CreateListDin(ListDin* ld, int capacity);

void dealocateList(ListDin *l);

void displayListDin(ListDin ld);
void displayListDinAsFood(ListDin ld);

//
void insertLast(ListDin *l, Address val);

void deleteLast(ListDin *l, Address *val);
#endif
