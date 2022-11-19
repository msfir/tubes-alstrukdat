/* File: node.h */
/* Definisi node pada tree*/

#ifndef NODE_H
#define NODE_H

#include "../food/food.h"

/* Definisi Node */
typedef struct node* Address;
typedef struct node {
    int info;       /* id makanan */
    Address* next;  /* array dinamik berisi Address children node ini */
    int childCount; /* banyak children dari node ini */
} Node;

/* *** Notasi Akses: selektor Address *** */
// return int
#define INFO(p) (p)->info
// return Address*
#define BUFFER(p) (p)->next
// return Address
#define NEXT(p, idx) *((p)->next + idx)
// return int
#define CHILD_COUNT(p) (p)->childCount
// return Address
#define CHILD(l, idx) (l)[(idx)]

/* CONSTRUCTOR */
Address newNode(int id);
/* Meminta info id food dan mengembalikan Address baru dengan memori teralokasi */
/* I.S. sembarang, id terdefinisi */
/* F.S. Address baru atau gagal alokasi */

/* GETTER SETTER */
int getChildCount(Node a);
/* mengembalikan nilai banyak child node ini */

Address getNodeById(Address *nodes, int id, int size);

#endif
