#include "set.h"

void CreateEmptySet(Set *s) {
    s->length = 0;
}

/* 
 * Return true jika set kosong
 */
boolean set_is_empty(Set s) {
    return s.length == 0;
}


/* 
 * Mencari indeks dari suatu elemen dalam set, -1 jika tidak ada
 */
int set_find(Set s, setinfo x) {
    int low = 0;
    int high = s.length - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ELMT_SET(s, mid) == x) {
            return mid;
        }
        if (ELMT_SET(s, mid) < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/* 
 * Mengecek apakah x berada di set
 */
boolean set_is_in(Set s, setinfo x) {
    return set_find(s, x) != -1;
}

/* 
 * Mengecek apakah a adalah subset dari b
 */
boolean set_is_subset(Set a, Set b) {
    boolean subset = true;
    int i = 0;
    while (i < a.length && subset) {
        subset = subset && set_is_in(b, ELMT_SET(a, i));
        i++;
    }
    return subset;
}

void set_add(Set *s, setinfo x) {
    if (set_is_empty(*s)) {
        s->length++;
        ELMT_SET(*s, 0) = x;
    } else if (!set_is_in(*s, x)) {
        int idx = 0;
        while (idx < s->length && ELMT_SET(*s, idx) < x) {
            idx++;
        }
        for (int i = s->length - 1; i >= idx; i--) {
            ELMT_SET(*s, i + 1) = ELMT_SET(*s, i);
        }
        ELMT_SET(*s, idx) = x;
        s->length++;
    }
}

/* 
 * Menghapus elemen dari set
 */
void set_remove(Set *s, setinfo x) {
    int idx = set_find(*s, x);
    if (idx != -1) {
        s->length--;
        for (int i = idx; i < s->length; i++) {
            ELMT_SET(*s, i) = ELMT_SET(*s, i + 1);
        }
    }
}

/* 
 * Membuat set baru hasil irisan dari dua set
 */
Set set_intersection(Set a, Set b) {
    Set res;
    CreateEmptySet(&res);
    for (int i = 0; i < a.length; i++) {
        if (set_is_in(b, ELMT_SET(a, i))) {
            set_add(&res, ELMT_SET(a, i));
        }
    }
    return res;
}

/* 
 * Membuat set baru hasil gabungan dari dua set
 */
Set set_union(Set a, Set b) {
    Set res;
    CreateEmptySet(&res);
    for (int i = 0; i < a.length; i++) {
        set_add(&res, ELMT_SET(a, i));
    }
    for (int i = 0; i < b.length; i++) {
        set_add(&res, ELMT_SET(b, i));
    }
    return res;
}
