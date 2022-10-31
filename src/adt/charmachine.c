/* File: charmachine.c */
/* Implementasi Mesin Karakter */

#include "charmachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char currentChar;
boolean EOP;
boolean EOL;
FILE *pita;
char MARK;

static int retval;

void START(FILE *stream, char mark) {
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
       Karakter pertama yang ada pada pita posisinya adalah pada jendela.
       I.S. : sembarang
       F.S. : currentChar adalah karakter pertama pada pita. Jika currentChar !=
       MARK maka EOP akan padam (false). Jika currentChar = MARK maka EOP akan
       menyala (true) */

    /* Algoritma */
    EOP = false;
    EOL = false;
    pita = stream;
    MARK = mark;
    ADV();
}

void ADV() {
    /* Pita dimajukan satu karakter.
       I.S. : Karakter pada jendela =
              currentChar, currentChar != MARK
       F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
              currentChar mungkin = MARK.
                    Jika  currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(pita, "%c", &currentChar);
    if (retval != 1 && errno != 0) {
        perror("Error");
        exit(1);
    }
    EOP = feof(pita) || currentChar == MARK;
    EOL = currentChar == '\n';
    if (EOP && pita != stdin) {
        fclose(pita);
    }
}
