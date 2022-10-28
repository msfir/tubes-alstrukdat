#include <stdio.h>
#include "listdin.h"

// #include "cstring.h"
#include "node.h"

int len(ListDin ld){
    return LENGTH(ld);
}

boolean isEmpty(ListDin ld){
    return (LENGTH(ld) == 0);
}

boolean isFull(ListDin ld){
    return (LENGTH(ld) == CAPACITY(ld));
}

void CreateListDin(ListDin* ld){
    CAPACITY(*ld) = DEFAULT_CAPACITY;
    LENGTH(*ld) = 0;

    HEAD(*ld) = (Address*) malloc(CAPACITY(*ld)*sizeof(Address));
    if(HEAD(*ld) == NULL) printf("WARNING DANGEROUS BEHAVIOR IN listdin.c : FAILED MALLOC");
}

void printListDin(ListDin ld){
    int i; printf("[");
    for(i = 0; i<LENGTH(ld); i++){
        if(i != 0) printf(", ");
        printf("p%p", *(HEAD(ld)+i));
    } printf("]");
}