/* File: tree.h */
/* Definisi ADT Tree */

#ifndef TREE_H
#define TREE_H

#include "node.h"

/* Definisi Tree */
typedef Node* Tree;

/* *** Konstruktor: Membentuk Tree dari Node *** */
/* melakukan assign pada sebuah Node sebagai root sebuah tree */
void CreateTree(Tree *a, Node *b);
/* I.S. a, b terdefinisi */
/* F.S. Tree dengan Node b sebagai [root]*/

void MakeChildren(Node *a, Node *b);
/* I.S. a, b terdefinisi */
/* F.S. Node b menjadi child Node a*/

/* *** Debug: Mendaftar relasi antara node *** */
void listParent(Tree a);
/* I.S. sembarang */
/* F.S. tercetak parent dari masing masing tree */

void listChildren(Tree a);
/* I.S. sembarang */
/* F.S. tercetak children dari masing masing tree */


#endif