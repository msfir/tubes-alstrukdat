/* File: cstring.h */

#ifndef STRING_H
#define STRING_H

#include "boolean.h"

#define MAX_STRING_LENGTH 100

typedef struct string {
    char buf[MAX_STRING_LENGTH];  // tidak perlu konstruksi karena default
                                  // valuenya adalah string kosong
} String;

#define STR_VALUE(S) (S).buf

/*
 * Membuat ADT String dari pointer char
 */
String StringFrom(char* str);

/*
 * Membuat ADT String dari array of char
 */
String StringFromArr(char str[], int size);

/*
 *  Menyalin string dari src ke dest
 *  I.S sembarang
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

/*
 * Menghapus semua spasi, tab, dan new line di akhir string
 */
String trim_end(String str);

/*
 * Mereturn substring dari str pada range [start, end)
 */
String substring(String str, int start, int end);

/*
 * Mereturn array of string hasil split
 */
String* split(String str, char delimiter, int* wordCount);

/*
 * Mengecek kesamaan dari dua buah string
 */
boolean is_string_equal(String a, String b);

/*
 * Mengecek apakah string diawali substring tertentu
 */
boolean is_string_startswith(String str, String substr);

#endif
