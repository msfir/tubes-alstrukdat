#include <stdio.h>
#include "foodlist.h"

#include "cstring.h"
/* **************KONSTRUKTOR************** */
void CreateFoodList (FoodList *L){
    int i ;
    for (i = 0; i < CAPACITY;i++){
        Id(ELMT(*L, i)) = MARK;
    }
};
/* I.S L sembarang */
/* F.S Terbentuk list L kosong dengan kapasitas CAPACITy
   Proses: inisialisasi semua elemen List L dengan MARK */

/* **************SELEKTOR TAMBAHAN************** */
/* *** Banyaknya elemen *** */
int listLength(ListStatik l){
    int i = IDX_MIN;
    while (ELMT(l,i)!=MARK && i<CAPACITY){
        i++;
    }
    return i;
};
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  

int getFirstIdx (FoodList L){
    if (ELMT(*L, 0)==MARK){
        return IDX_UNDEF;
    }
    return IDX_MIN;
};
/* Menghasilkan indeks pertama elemen list L, jika L kosong menghasilkan IDX_UNDEF */

int getLastIdx (FoodList L){
    return listLength(L) - 1;
};
/* Menghasilkan indeks elemen terakhir list L, jika L kosong menghasilkan IDX_UNDEF */

/* **************PRIMITIF LAIN************** */
boolean isEmptyFood (FoodList L){
    return (listLength(L) == 0);
};
/* Menghasilkan True jika L kosong. False jika tidak */
boolean isFullFood (FoodList L){
    return listLength(L) == CAPACITY - 1;
};
/* Menghasilkan True jika L penuh. False jika tidak */

void addFood (FoodList *L, Food M){
    if (isFullFood(*L)){
        printf("List makanan penuh");
    }else{
        ELMT(*L, listLength(*L)) = M;
    }
};
/* I.S L terdefinisi dan tidak penuh. M terdefinisi */
/* F.S Menambahkan M sebagai elemen terakhir list L. NEFF L bertambah 1 */

/* **************PRIMITIF LAIN UNTUK LIST BAHAN MAKANAN************** */
void printBuyList (FoodList L){
    printf("======================\n");
    printf("=        BUY         =\n");
    printf("======================\n");
    if (isEmpty(L)){
        printf("Tidak ada makanan dengan aksi BUY");
    }else{
        int i,j = 0;
        printf("List Bahan Makanan yang Bisa Dibeli:\n");
        for (i = 0; i < listLength(L);i++){
            if (ActionLocation(ELMT(L,i))=="BUY"){
                j++;
                printf("%d. %c", j, NAME(ELMT(L, i)));
            }
        }
        if (j==0){
            printf("Tidak ada makanan dengan aksi BUY");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dibeli beserta waktu delivery-nya. L tidak berubah */

void printFryList (FoodList L){
    printf("======================\n");
    printf("=        FRY         =\n");
    printf("======================\n");
    if (isEmpty(L)){
        printf("Tidak ada makanan dengan aksi FRY");
    }else{
        int i,j = 0;
        printf("List Bahan Makanan yang Bisa Digoreng:\n");
        for (i = 0; i < listLength(L);i++){
            if (ActionLocation(ELMT(L,i))=="FRY"){
                j++;
                printf("%d. %c", j, NAME(ELMT(L, i)));
            }
        }
        if (j==0){
            printf("Tidak ada makanan dengan aksi FRY");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa digoreng. L tidak berubah */

void printMixList (FoodList L){
    printf("======================\n");
    printf("=        MIX         =\n");
    printf("======================\n");
    if (isEmpty(L)){
        printf("Tidak ada makanan dengan aksi MIX");
    }else{
        printf("List Bahan Makanan yang Bisa DiMix:\n");
        int i,j = 0;
        for (i = 0; i < listLength(L);i++){
            if (ActionLocation(ELMT(L,i))=="MIX"){
                j++;
                printf("%d. %c", j, NAME(ELMT(L, i)));
            }
        }
        if (j==0){
            printf("Tidak ada makanan dengan aksi MIX");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dimix. L tidak berubah */

void printBoilList (FoodList L){
    printf("======================\n");
    printf("=        BOIL        =\n");
    printf("======================\n");
    if (isEmpty(L)){
        printf("Tidak ada makanan dengan aksi BOIL");
    }else{
        int i,j = 0;
        printf("List Bahan Makanan yang Bisa DiBoil:\n");
        for (i = 0; i < listLength(L);i++){
            if (ActionLocation(ELMT(L,i))=="BOIL"){
                j++;
                printf("%d. %c", j, NAME(ELMT(L, i)));
            }
        }
        if (j==0){
            printf("Tidak ada makanan dengan aksi BOIL");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa direbus. L tidak berubah */

void printChopList (FoodList L){
    printf("======================\n");
    printf("=        CHOP        =\n");
    printf("======================\n");
    if (isEmpty(L)){
        printf("Tidak ada makanan dengan aksi CHOP");
    }else{
        printf("List Bahan Makanan yang Bisa Dipotong:\n");
        int i,j = 0;
        for (i = 0; i < listLength(L);i++){
            if (ActionLocation(ELMT(L,i))=="CHOP"){
                j++;
                printf("%d. %c", j, NAME(ELMT(L, i)));
            }
        }
        if (j==0){
            printf("Tidak ada makanan dengan aksi CHOP");
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan yang bisa dipotong. L tidak berubah */

void printCatalog (FoodList L){
    printf("List Makanan\n");
    printf("(nama - durasi kedaluwarsa - aksi yang diperlukan - delivery time) ");
    if (isEmpty(L)){
        printf("Tidak ada makanan");
    }else{
        int i,j = 0;
        for (i = 0; i < listLength(L);i++){
            j++;
            printf("%d. %c - %c - %c - %c", j, NAME(ELMT(L, i)), ExpirationTime((ELMT(L, i))), ActionLocation(ELMT(L, i)), DeliveryTime(ELMT(L, i)));
        }
    }
};
/* I.S L terdefinisi */
/* F.S Memunculkan ke layar nama makanan, waktu kadaluwarsa, aksi yang bisa dilakukan, dan waktu delivery */

Food getFoodWithIdxAction (FoodList L, char action, int idx);
{pake counter}
/* Mengembalikan elemen Makanan ke-idx pada List yang memiliki elemen lokasiAksi = lokasiAksi */

