#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "cstring.h"
#include "food.h"
#include "time.h"

/*
 * Mengaktifkan wordmachine
 */
void start_parser(FILE *stream);

/*
 * Melakukan parsing untuk bilangan integer non-negatif, dan mereturn hasilnya.
 */
int parse_int();

/*
 * Melakukan parsing untuk time dan mereturn hasilnya.
 */
Time parse_time();

/*
 * Melakukan parsing untuk satu dan mereturn hasilnya dalam bentuk String.
 */
String parse_line();

/*
 * Melakukan parsing untuk enum action dan mereturn hasilnya.
 */
enum Action parse_action();

#endif
