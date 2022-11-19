#include <assert.h>
#include <stdio.h>

#include "adt.h"

int main() {
    printf("--- Driver Test Set ---");
    printf("\n");
    printf("\n");
    Set a;
    CreateEmptySet(&a);
    set_add(&a, 3);
    set_add(&a, 13);
    set_add(&a, 42);
    set_add(&a, 60);
    set_add(&a, 4);
    set_add(&a, 6);
    set_add(&a, 9);
    set_remove(&a, 30);
    set_remove(&a, 42);
    set_add(&a, 60);
    set_add(&a, 4);
    assert(set_length(a) == 6);
    Set b;
    CreateEmptySet(&b);
    set_add(&b, 42);
    set_add(&b, 60);
    set_add(&b, 4);
    set_add(&b, 54);
    set_add(&b, 22);
    assert(set_length(b) == 5);
    Set c = set_intersection(a, b);
    assert(set_length(c) == 2);
    c = set_union(a, b);
    assert(set_length(c) == 9);
    printf("All tests passed.\n");
    printf("\n");
    printf("--- Driver Test Set ---");
    printf("\n");
    printf("\n");
    return 0;
}
