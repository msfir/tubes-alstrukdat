#include "wordmachine.h"
#include "charmachine.h"
#include <stdio.h>

boolean endWord;
Word currentWord;

void IgnoreBlanks() {
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK) {
        ADV();
    }
}

void InitMachine(FILE *stream, char mark) {
    /* Membaca file di path kata per kata
       I.S. : currentChar sembarang
       F.S. : endWord = true, dan currentChar = MARK;
              atau endWord = false, currentWord adalah kata yang sudah
       diakuisisi, currentChar karakter pertama sesudah karakter terakhir kata
     */
    START(stream, mark);
}

void ADVWORD() {
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin
       MARK Jika currentChar = MARK, endWord = true. Proses : Akuisisi kata
       menggunakan procedure CopyWord */
    IgnoreBlanks();
    if (EOP) {
        endWord = true;
    } else {
        CopyWord();
        IgnoreBlanks();
    }
}

void ADVLINE() {
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata/baris terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true. */
    IgnoreBlanks();
    if (EOP) {
        endWord = true;
    } else {
        CopyLine();
        IgnoreBlanks();
    }
}

void CopyWord() {
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang
       diakuisisi. Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong
     */
    currentWord.Length = 0;
    while (currentChar != BLANK && !EOL && !EOP) {
        if (currentWord.Length < NMax) { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        } else
            break;
    }
    if (EOL) {
        ADV();
    }
}

void CopyLine() {
    /* Mengakuisisi baris, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari baris
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = EOL atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang
       diakuisisi. Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong
     */
    currentWord.Length = 0;
    while (!EOP && !EOL) {
        if (currentWord.Length < NMax) { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        } else
            break;
    }
    ADV();
}
