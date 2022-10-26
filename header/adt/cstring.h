/* File: cstring.h */

#ifndef STRING_H
#define STRING_H

#define MAX_STRING_LENGTH 100

typedef struct string {
    char buf[MAX_STRING_LENGTH]; // tidak perlu konstruksi karena default
                                 // valuenya adalah string kosong
} String;

#define STR_VALUE(S) (S).buf

/*
 * Membuat ADT String dari pointer char
 */
String StringFrom(char* str);

/*
 *  Menyalin string dari src ke dest
 *  I.S dest dan src telah diinisialisasi
 *  F.S String src tersalin ke String dest
 */
void copy_string(String* dest, String src);

/*
 *  Mengembalikan panjang String
 */
int length(String str);

/*
 * Konkatenasi dua String, menghasilkan String baru
 */
String concat_string(String dest, String str);

#endif
