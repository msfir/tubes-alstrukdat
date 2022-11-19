#include "logger.h"

#include <stdio.h>

/*
 * Menampilkan pesan error pada terminal dengan teks berwarna merah (tanpa new line)
 */
void log_error(char *message) {
    printf("\e[91m%s\e[0m", message);
}
/*
 * Menampilkan pesan info pada terminal dengan teks berwarna hijau (tanpa new line)
 */
void log_info(char *message) {
    printf("\e[92m%s\e[0m", message);
}
