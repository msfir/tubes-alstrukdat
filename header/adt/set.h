/* FILE set.h */
/* Definisi ADT Set */

#ifndef _SET_H
#define _SET_H

#include <stdio.h>
#include "boolean.h"

#define MAX_SET_SIZE 50

typedef int setinfo;

typedef struct set {
    setinfo buffer[MAX_SET_SIZE];
    int length; // Set kosong jika length == 0
} Set; 

#define ELMT_SET(s, idx) (s).buffer[idx]
#define set_length(s) (s).length

/* 
 * Membuat set kosong
 */
void CreateEmptySet(Set *s);

/* 
 * Return true jika set kosong
 */
boolean set_is_empty(Set s); 

/* 
 * Mencari indeks dari suatu elemen dalam set, -1 jika tidak ada
 */
int set_find(Set s, setinfo x);

/* 
 * Mengecek apakah x berada di set
 */
boolean set_is_in(Set s, setinfo x); 

/* 
 * Mengecek apakah a adalah subset dari b
 */
boolean set_is_subset(Set a, Set b); 

/* 
 * Menambahkan elemen ke dalam set secara terurut
 */
void set_add(Set *s, setinfo x);

/* 
 * Menghapus elemen dari set
 */
void set_remove(Set *s, setinfo x);

/* 
 * Membuat set baru hasil irisan dari dua set
 */
Set set_intersection(Set a, Set b);

/* 
 * Membuat set baru hasil gabungan dari dua set
 */
Set set_union(Set a, Set b);

#endif
