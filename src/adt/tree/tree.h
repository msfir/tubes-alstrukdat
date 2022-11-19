/* File: tree.h */
/* Definisi ADT Tree */

#ifndef TREE_H
#define TREE_H

#include "../foodlist/foodlist.h"
#include "../node/node.h"

/* Definisi Tree */
typedef Node *Tree;

// return Address
#define ROOT(t) (t)

/* *** Konstruktor: Membentuk Tree dari Node *** */
/* melakukan assign pada sebuah Node sebagai root sebuah tree */
void CreateTree(Tree *a, Node *b);
/* I.S. a, b terdefinisi */
/* F.S. Tree dengan Node b sebagai [root]*/

void MakeChildren(Node *a, Node *b);
/* I.S. a, b terdefinisi */
/* F.S. Node b menjadi child Node a*/

/* *** Debug: Mendaftar relasi antara node *** */
void listParent(Tree a, FoodList fl);
/* I.S. sembarang */
/* F.S. tercetak parent dari masing masing tree */

#endif
