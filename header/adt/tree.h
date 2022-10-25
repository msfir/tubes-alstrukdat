#ifndef TREE_H
#define TREE_H

/// RANT!
// tree is kinda confusing on its own
// it has so many variant, and every variant is mostly distinct to each other :))))))))))))000
// we'r using n-ary tree
// but how can i implement it from a linked nodes:(

// using this definition
// 1 -> 2
// 2 -> 1 

#include <stdio.h>

// #include "listlinier.h" // maybe later i'll just make node.h, linkedlist kinda not needed here
#include "node.h"

typedef Node Tree;

void CreateTree(Tree *a);

// void PairNode(Node a, Node b); // pair by definition
void MakeChildren(Node *a, Node *b);

void listParent(Tree a);

void listChildren(Tree a);

int greatestDegree(Tree a);

int getDegree(Tree a, Node b); // what degree is b in tree a


#endif