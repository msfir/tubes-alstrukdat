#include "cstring.h"
#include <stdlib.h>

String StringFrom(char *str) {
    String res;
    int i = 0;
    while (str[i] != 0) {
        STR_VALUE(res)[i] = str[i];
        i++;
    }
    // memastikan bahwa string hasilnya null-terminated
    STR_VALUE(res)[i] = 0;
    return res;
}

void copy_string(String* dest, String src) {
    int idx;
    for (idx = 0; idx <= length(src); idx++) {
        STR_VALUE(*dest)[idx] = STR_VALUE(src)[idx]; // menyalin semua isinya termasuk null di akhir
    }
}

int length(String str) {
    // MenurStringt definisi, String dalam bahasa C selalu null-terminated
    int i = 0;
    while (STR_VALUE(str)[i] != 0) {
        i++;
    }
    return i;
}

String concat_string(String str1, String str2) {
    String result;
    int len1 = length(str1);
    int len2 = length(str2);
    int i;
    for (i = 0; i <= len1 + len2; i++) {
        if (i < len1) {
            STR_VALUE(result)[i] = STR_VALUE(str1)[i];
        } else {
            STR_VALUE(result)[i] = STR_VALUE(str2)[i - len1];
        }
    }
    return result;
}
