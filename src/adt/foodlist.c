#include "foodlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "cstring.h"
/* **************KONSTRUKTOR************** */
void CreateFoodList(FoodList *L) {
    int i;
    for (i = 0; i < CAPACITY; i++) {
        Id(ListElmt(*L, i)) = MARK;
    }
};
/* I.S L sembarang */
/* F.S Terbentuk list L kosong dengan kapasitas CAPACITy
   Proses: inisialisasi semua elemen List L dengan MARK */

/* **************SELEKTOR TAMBAHAN************** */
/* *** Banyaknya elemen *** */

int listLength(FoodList l){
    int i = IDX_MIN;
    while (Id(ListElmt(l, i)) != MARK && i < CAPACITY) {
        i++;
    }
    return i;
};
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */

int getFirstIdx(FoodList L) {
    if (Id(ListElmt(L, 0)) == MARK) {
        return IDX_UNDEF;
    }
    return IDX_MIN;
};
/* Menghasilkan indeks pertama elemen list L, jika L kosong menghasilkan IDX_UNDEF */

int getLastIdx(FoodList L) {
    return listLength(L) - 1;
};
/* Menghasilkan indeks elemen terakhir list L, jika L kosong menghasilkan IDX_UNDEF */

/* **************PRIMITIF LAIN************** */
boolean isEmptyFood(FoodList L) {
    return (listLength(L) == 0);
};
/* Menghasilkan True jika L kosong. False jika tidak */
boolean isFullFood(FoodList L) {
    return listLength(L) == CAPACITY - 1;
};
/* Menghasilkan True jika L penuh. False jika tidak */

void addFood(FoodList *L, Food M) {
    if (isFullFood(*L)) {
        printf("List makanan penuh\n");
    } else {
        ListElmt(*L, listLength(*L)) = M;
    }
};
/* I.S L terdefinisi dan tidak penuh. M terdefinisi */
/* F.S Menambahkan M sebagai elemen terakhir list L. NEFF L bertambah 1 */

/* **************PRIMITIF LAIN UNTUK LIST BAHAN MAKANAN************** */
void printBuyList(FoodList L) {
    printf("======================\n");
    printf("=        BUY         =\n");
    printf("======================\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan dengan aksi BUY\n");
    } else {
        int i, j = 0;
        printf("List Bahan Makanan yang Bisa Dibeli:\n");
        for (i = 0; i < listLength(L); i++) {
            if (ActionLocation(ListElmt(L, i)) == BUY) {
                j++;
                printf("%d. %s\n", j, STR_VALUE(Name(ListElmt(L, i))));
            }
        }
        if (j == 0) {
            printf("Tidak ada makanan dengan aksi BUY\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dibeli beserta waktu delivery-nya. L tidak berubah */

void printFryList(FoodList L) {
    printf("======================\n");
    printf("=        FRY         =\n");
    printf("======================\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan dengan aksi FRY\n");
    } else {
        int i, j = 0;
        printf("List Bahan Makanan yang Bisa Digoreng:\n");
        for (i = 0; i < listLength(L); i++) {
            if (ActionLocation(ListElmt(L, i)) == FRY) {
                j++;
                printf("%d. %s\n", j, STR_VALUE(Name(ListElmt(L, i))));
            }
        }
        if (j == 0) {
            printf("Tidak ada makanan dengan aksi FRY\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa digoreng. L tidak berubah */

void printMixList(FoodList L) {
    printf("======================\n");
    printf("=        MIX         =\n");
    printf("======================\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan dengan aksi MIX\n");
    } else {
        printf("List Bahan Makanan yang Bisa DiMix:\n");
        int i, j = 0;
        for (i = 0; i < listLength(L); i++) {
            if (ActionLocation(ListElmt(L, i)) == MIX) {
                j++;
                printf("%d. %s\n", j, STR_VALUE(Name(ListElmt(L, i))));
            }
        }
        if (j == 0) {
            printf("Tidak ada makanan dengan aksi MIX\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dimix. L tidak berubah */

void printBoilList(FoodList L) {
    printf("======================\n");
    printf("=        BOIL        =\n");
    printf("======================\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan dengan aksi BOIL\n");
    } else {
        int i, j = 0;
        printf("List Bahan Makanan yang Bisa DiBoil:\n");
        for (i = 0; i < listLength(L); i++) {
            if (ActionLocation(ListElmt(L, i)) == BOIL) {
                j++;
                printf("%d. %s\n", j, STR_VALUE(Name((ListElmt(L, i)))));
            }
        }
        if (j == 0) {
            printf("Tidak ada makanan dengan aksi BOIL\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa direbus. L tidak berubah */

void printChopList(FoodList L) {
    printf("======================\n");
    printf("=        CHOP        =\n");
    printf("======================\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan dengan aksi CHOP\n");
    } else {
        printf("List Bahan Makanan yang Bisa Dipotong:\n");
        int i, j = 0;
        for (i = 0; i < listLength(L); i++) {
            if (ActionLocation(ListElmt(L, i)) == CHOP) {
                j++;
                printf("%d. %s\n", j, STR_VALUE(Name((ListElmt(L, i)))));
            }
        }
        if (j == 0) {
            printf("Tidak ada makanan dengan aksi CHOP\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dipotong. L tidak berubah */

void printCatalog(FoodList L) {
    printf("List Makanan\n");
    printf("(nama - durasi kedaluwarsa - aksi yang diperlukan - delivery time)\n");
    if (isEmptyFood(L)) {
        printf("Tidak ada makanan\n");
    } else {
        int i, j = 0;
        for (i = 0; i < listLength(L); i++) {
            j++;
            Food f = ListElmt(L, i);
            printf("%d. %s - ", j, STR_VALUE(Name(f)));
            TulisFoodTIME(ExpirationTime(f));
            printf(" - %s - ", ActionName[ActionLocation(f)]);
            TulisFoodTIME(DeliveryTime(f));
            printf("\n");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan, waktu kadaluwarsa, aksi yang bisa dilakukan, dan waktu delivery */

boolean getFoodWithIdxAction (FoodList L, enum Action action, int idx, Food *food)
{
    int counter = 0, i;
    for (i = 0; i < listLength(L);i++){
        if (ActionLocation(ListElmt(L,i)) == action){
            counter++;
            if (counter == idx){
                *food = ListElmt(L, i);
                return true;
            }
        }
    }
    return false;
}
/* Mengembalikan elemen Makanan ke-idx pada List yang memiliki elemen lokasiAksi = lokasiAksi */

boolean getFoodById(FoodList L, int id, Food *food){
    int counter = 0, i;
    for (i = 0; i < listLength(L);i++){
        if (Id(ListElmt(L,i)) == id){
            *food = ListElmt(L, i);
            return true;
        }
    }
    return false;
};
/*Mengembalikan true jika menemukan id sesuai input, dan false jika tidak*/

int getIdxById(FoodList L, int id){
    boolean found;
    int i;

    i = 0;
    found = false;
    while (i<listLength(L) && !found){
        if (Id(ListElmt(L,i))==id){
            found = true;
            return i;
        }
        i++;
    }
    return IDX_UNDEF;
};
/*mengembalikan idx yg menyimpan id food, mengembalikan idx undef jika tidak ada*/

Food getElmtById(FoodList L, int id){
    boolean found;
    int i;

    i = 0;
    found = false;
    while (i<listLength(L) && !found){
        if (Id(ListElmt(L,i))==id){
            found = true;
            return ListElmt(L,i);
        }
        i++;
    }
    return ListElmt(L, i);
};
/*pre kondisi: id terdefinisi
mengembalikan Element food makanan*/
