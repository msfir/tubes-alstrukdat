/* File: matrix.c */
/* Nama: Ariel Jovananda */
/* NIM: 13521086 */
/* Tanggal: 21 September 2022 */
/* Topik praktikum: Pra Praktikum 4*/
/* Deskripsi: Realisasi fungsi dan prosedur dari header matrix */


#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "cstring.h"
#include "matrix.h"
#include "parser.h"
#include "wordmachine.h"

void createMatrix(int nRows, int nCols, Matrix *m)
{
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
   ROW_EFF(*m) = nRows;
   COL_EFF(*m) = nCols;
}


/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j)
{
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
   return(i >= 0 && i < ROW_CAP) && (j >= 0 && j < COL_CAP);
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m)
{
/* Mengirimkan Index baris terbesar m */
   return ROW_EFF(m) - 1;
}
IdxType getLastIdxCol(Matrix m)
{
/* Mengirimkan Index kolom terbesar m */
   return COL_EFF(m) - 1;
}
boolean isIdxEff(Matrix m, IdxType i, IdxType j)
{
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
   return(i >= 0 && i <= getLastIdxRow(m)) && (j >= 0 && j<= getLastIdxCol(m));
}
ElType getElmtDiagonal(Matrix m, IdxType i)
{
/* Mengirimkan elemen m(i,i) */
   return ELMT(m, i, i);
}

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut)
{
/* Melakukan assignment mOut <- mIn */
   IdxType i, j;

   createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);

   for(i = 0; i < ROW_EFF(mIn); i++)
   {
      for(j = 0; j < COL_EFF(mIn); j++)
      {
         ELMT(*mOut, i, j) = ELMT(mIn, i, j);
      }
   }

}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
{
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
   ElType n;
   IdxType i, j;

   createMatrix(nRow, nCol, m);

   for(i = 0; i < nRow; i++)
   {
      for(j = 0; j < nCol; j++)
      {
         scanf("%c ", &n);
         ELMT(*m, i, j) = n;
      }
   }
}


void CreateMap(Matrix *m, FILE *file)
{
   // STARTWORDFROMFILE("test.txt");
   start_parser(file);

   int rows = parse_int();
   int cols = parse_int();

   createMatrix(rows, cols, m);

   for (int row = 0; row < rows; row++) {
      String line = parse_line();

      for (int col = 0; col < cols; col++) {
         ELMT(*m, row, col) = STR_VALUE(line)[col];
      }
   }
}

void displayMap(Matrix m)
{
   int i, j;

   for(j = 0; j < COL_EFF(m) + 2; j++)
   {
      printf("*");
      printf(" ");
   }
   printf("\n");

    for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         if (j == 0)
         {
            printf("*");
            printf(" ");
         }
         if (ELMT(m, i, j) == '#')
         {
            printf(" ");
         }
         else
         {
            printf("%c", ELMT(m, i, j));
         }
         printf(" ");
         if(j == getLastIdxCol(m))
         {
            printf("*");
         }
      }
      printf("\n");
   }
   for(j = 0; j < COL_EFF(m) + 2; j++)
   {
      printf("*");
      printf(" ");
   }
   printf("\n");
}


void displayMatrix(Matrix m)
{
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
   IdxType i, j;

   for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         printf("%c", ELMT(m, i, j));
         if(j != getLastIdxCol(m))
            printf(" ");
      }
      printf("\n");
   }

   printf("%d, %d", ROW_EFF(m), COL_EFF(m));
}


/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m)
{
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
   return(ROW_EFF(m) == COL_EFF(m));
}
boolean isSymmetric(Matrix m)
{
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
   IdxType i, j;
   
   if(!isSquare(m))
   {
      return false;
   }

   for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         if(ELMT(m, i, j) != ELMT(m, i, j))
         {
            return false;
         }
      }
   }

   return true;
}
boolean isIdentity(Matrix m)
{
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
   IdxType i, j;
   
   if(!isSquare(m))
   {
      return false;
   }

   for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         if(i == j && ELMT(m, i, j) != 1)
         {
            return false;
         }
         if(i != j && ELMT(m, i, j) != 0)
         {
            return false;
         }
      }
   }

   return true;

}

boolean isSparse(Matrix m)
{
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
   int n = 0;
   IdxType i, j;


    for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         if(ELMT(m, i, j) != 0)
         {
            n++;
         }
      }
   }

   return n <= (ROW_CAP * COL_CAP / 20);

}


float determinant(Matrix m)
{
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
    float det, x;
    IdxType i, j, k;
    Matrix tmp;

    det = 0;

    if (COL_EFF(m) == 1) {
        return ELMT(m, 0, 0);
    }

    for (i = 0; i < COL_EFF(m); i++) {
        x = i % 2 == 0 ? ELMT(m, 0, i) : (-1) * ELMT(m, 0, i);
        createMatrix(ROW_EFF(m) - 1, COL_EFF(m) - 1, &tmp);

        for (j = 0; j < COL_EFF(m); j++) {
            if (j == i)
                continue;

            for (k = 1; k < ROW_EFF(m); k++) {
                if (j < i) {
                    ELMT(tmp, k - 1, j) = ELMT(m, k, j);
                } else {
                    ELMT(tmp, k - 1, j - 1) = ELMT(m, k, j);
                }
            }
        }

        x *= determinant(tmp);
        det += x;
    }

    return det;
}
Matrix transpose(Matrix m)
{
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
   IdxType i, j;
   Matrix mT;

   copyMatrix(m, &mT);

   for(i = 0; i < ROW_EFF(m); i++)
   {
      for(j = 0; j < COL_EFF(m); j++)
      {
         ELMT(mT, i, j) = ELMT(m, j, i);
      }
   }

   return mT;
}
void pTranspose(Matrix *m)
{
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
   IdxType i, j;
   Matrix mT;

   mT = transpose(*m);

   for(i = 0; i < ROW_EFF(*m); i++)
   {
      for(j = 0; j < COL_EFF(*m); j++)
      {
         ELMT(*m, i, j) = ELMT(mT, i, j);
      }
   }
}
