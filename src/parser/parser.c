#include "parser.h"

#include <math.h>
#include <stdio.h>

#include "adt.h"

int str_to_int(String str) {
    int len = length(str);
    int res = 0;
    int mul = pow(10, len - 1);
    for (int i = 0; i < len; i++) {
        int digit = (int)(STR_VALUE(str)[i] - '0');
        res += digit * mul;
        mul /= 10;
    }
    return res;
}

/*
 * Mengaktifkan wordmachine
 */
void start_parser(FILE *stream) {
    char mark;
    if (stream == stdin) {
        mark = '\n';
    } else {
        mark = 0;
    }
    InitMachine(stream, mark);
}

/*
 * Melakukan parsing untuk bilangan integer non-negatif, dan mereturn hasilnya.
 */
int parse_int() {
    ADVWORD();
    String word = StringFromArr(currentWord.TabWord, currentWord.Length);
    word = trim_end(word);
    int res = str_to_int(word);
    return res;
}

/*
 * Melakukan parsing untuk time dan mereturn hasilnya.
 */
Time parse_time() {
    Time time;
    String word;

    ADVWORD();
    word = StringFromArr(currentWord.TabWord, currentWord.Length);
    int DD = str_to_int(trim_end(word));

    ADVWORD();
    word = StringFromArr(currentWord.TabWord, currentWord.Length);
    int HH = str_to_int(trim_end(word));

    ADVWORD();
    word = StringFromArr(currentWord.TabWord, currentWord.Length);
    int MM = str_to_int(trim_end(word));

    CreateTime(&time, DD, HH, MM);
    return time;
}

/*
 * Melakukan parsing untuk satu dan mereturn hasilnya dalam bentuk String.
 */
String parse_line() {
    ADVLINE();
    return trim_end(StringFromArr(currentWord.TabWord, currentWord.Length));
}

/*
 * Melakukan parsing untuk enum action dan mereturn hasilnya.
 */
enum Action parse_action() {
    String action = parse_line();
    if (is_string_equal(action, StringFrom("Buy"))) {
        return BUY;
    } else if (is_string_equal(action, StringFrom("Mix"))) {
        return MIX;
    } else if (is_string_equal(action, StringFrom("Chop"))) {
        return CHOP;
    } else if (is_string_equal(action, StringFrom("Fry"))) {
        return FRY;
    } else if (is_string_equal(action, StringFrom("Boil"))) {
        return BOIL;
    }
    return -1;
}
