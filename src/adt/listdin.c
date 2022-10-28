#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"

#include "cstring.h"
#include "node.h"

int len(ListDin ld){
    return LISTLEN(ld);
}

boolean isEmpty(ListDin ld){
    return (LISTLEN(ld) == 0);
}

boolean isFull(ListDin ld){
    return (LISTLEN(ld) == CAPACITY(ld));
}

void CreateListDin(ListDin* ld, int capacity){
    CAPACITY(*ld) = capacity;
    LISTLEN(*ld) = 0;

    BUFFER(*ld) = (Address*) malloc(CAPACITY(*ld)*sizeof(Address));
    if(BUFFER(*ld) == NULL) printf("WARNING DANGEROUS BEHAVIOR IN listdin.c : FAILED MALLOC");
}

void dealocateList(ListDin *l){
    CAPACITY(*l) = 0;
    LISTLEN(*l);

    free(BUFFER(*l));
}

void displayListDin(ListDin ld){
    int i; printf("[");
    for(i = 0; i<LISTLEN(ld); i++){
        if(i != 0) printf(", ");
        printf("p : %p", *(BUFFER(ld)+i));
    } printf("]\n");
}

void displayListDinAsFood(ListDin ld){
    int i; printf("[");
    for(i = 0; i<LISTLEN(ld); i++){
        if(i != 0) printf(", ");
        printf("%s", STR_VALUE(Name(*INFO(ELMT(ld, i)))));
    } printf("]\n");
}

void insertLast(ListDin *l, Address val){
    if(!isFull(*l)){
        ELMT(*l, LISTLEN(*l)) = val;
        LISTLEN(*l)++; 
    }
}

void deleteLast(ListDin *l, Address *val){
    if(!isEmpty(*l)){
        *val = ELMT(*l, LISTLEN(*l)-1);
        LISTLEN(*l)--;
    }
}