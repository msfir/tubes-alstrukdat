#include "cstring.h"

#include <stdlib.h>

#include "boolean.h"

String StringFrom(char* str) {
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

String StringFromArr(char str[], int size) {
    String res;
    int i = 0;
    while (i < size) {
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
        STR_VALUE(*dest)[idx] = STR_VALUE(src)[idx];  // menyalin semua isinya termasuk null di akhir
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

String trim_end(String str) {
    int len = length(str);
    boolean ok = false;
    for (int i = len - 1; i >= 0 && !ok; i--) {
        if (STR_VALUE(str)[i] != ' ' && STR_VALUE(str)[i] != '\t' && STR_VALUE(str)[i] != '\n') {
            STR_VALUE(str)[i + 1] = 0;
            ok = true;
        }
    }
    return str;
}

String substring(String str, int start, int end) {
    int idx;
    for (idx = 0; idx < end - start; idx++) {
        STR_VALUE(str)[idx] = STR_VALUE(str)[start + idx];
    }
    STR_VALUE(str)[end - start] = 0;
    return str;
}

String* split(String str, char delimiter, int* wordCount){    
    // variables
    int delimiterCount = 0, i = 0, j = 0, last = 0, wordNum = 0;
    int idxStart = 0, idxEnd = length(str) - 1;

    //remove delimiter(s) on start
    i = 0;
    while (STR_VALUE(str)[i] == delimiter && i < length(str))
    {
        i++;
    } 
    if(i < length(str)){
        idxStart = i;
    }
    
    // remove delimiter(s) on end
    i = 0;
    while (STR_VALUE(str)[length(str)-1-i] == delimiter && length(str)-1-i >= 0)
    {
        i++;
    } 
    if(length(str)-1-i >= 0){
        idxEnd = length(str)-1-i;
    }
    

    // finally strips the str from starting and ending delimiters
    str = substring(str, idxStart, idxEnd+1);

    // count for actual delimiters
    for(i = 0, last = 0; i < length(str); i++){
        if(STR_VALUE(str)[i] == delimiter) 
        {
            if(last - i != 0 && i != length(str)-1){
                delimiterCount++;
            }

            last = i+1;
        }
         
    }

    // wordCount
    *wordCount = delimiterCount+1;

    // initializing the resulting string array
    String* res = (String*) malloc((*wordCount)*sizeof(String));
    for(i = 0; i<*wordCount; i++){
        res[i] = StringFrom("");
    }

    // split the string to array
    i = 0, j = 0, last = 0, wordNum = 0;
    while (i < length(str) && wordNum < *wordCount)
    {
        if(STR_VALUE(str)[i] == delimiter){
            res[wordNum] = substring(str, last, i);

            if(last-i != 0){
                wordNum++;
            }
            last = i+1;
        }

        i++;
    }
    // split it one more time (might opt for do-while since it can loop for +1 more than while loop)
    if(last < length(str)){
        res[wordNum] = substring(str, last, length(str));

        wordNum++;
        last = i+1;
    }
    
    return res;
}

boolean is_string_equal(String a, String b) {
    int len_a = length(a);
    int len_b = length(b);
    boolean equal = len_a == len_b;
    for (int i = 0; i < len_a && equal; i++) {
        equal = STR_VALUE(a)[i] == STR_VALUE(b)[i];
    }
    return equal;
}

// is str startswith substr
boolean is_string_startswith(String str, String substr) {
    int len_substr = length(substr);

    boolean equal = true;
    for (int i = 0; i < len_substr; i++) {
        equal = STR_VALUE(str)[i] == STR_VALUE(substr)[i];
    }
    return equal;
}