/* File: mesinkata.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "charmachine.h"

#define NMax 50
#define BLANK ' '

typedef struct {
    char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai
                           [0..NMax-1] */
    int Length;
} Word;

/* State Mesin Word */
extern boolean endWord;
extern Word currentWord;

void IgnoreBlanks();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void InitMachine(FILE *stream, char mark);
/* I.S. : CC sembarang
   F.S. : EndWord = true, dan CC = MARK;
          atau EndWord = false, CWord adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVWORD();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CWord adalah kata/baris terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndWord = true. */

void ADVLINE();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CWord adalah baris/kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari baris berikutnya, mungkin MARK
          Jika CC = MARK, EndWord = true. */

void CopyWord();
/* Mengakuisisi kata, menyimpan dalam CWord
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CWord berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void CopyLine();
/* Mengakuisisi baris, menyimpan dalam CWord
   I.S. : CC adalah karakter pertama dari baris
   F.S. : CWord berisi kata yang sudah diakuisisi;
          CC = EOL atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang baris melebihi NMax, maka sisa baris "dipotong" */

#endif
