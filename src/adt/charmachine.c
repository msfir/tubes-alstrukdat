/* File: charmachine.c */
/* Implementasi Mesin Karakter */

#include "charmachine.h"
#include <stdio.h>

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
    EOP = feof(pita) || currentChar == MARK;
    EOL = currentChar == '\n';
    if (EOP) {
        fclose(pita);
    }
}
