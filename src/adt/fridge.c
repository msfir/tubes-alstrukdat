#include "fridge.h"

#include <math.h>
#include <stdio.h>
/*
 * Konstruktor Fridge.
 * Membuat fridge dengan ukuran width x height
 */
void CreateFridge(Fridge *fridge, int width, int height) {
    createMatrix(width, height, &fridge->space);
    for (int i = 0; i < ROW_EFF(fridge->space); i++) {
        for (int j = 0; j < COL_EFF(fridge->space); j++) {
            MatElmt(fridge->space, i, j) = '.';
        }
    }
    fridge->width = width;
    fridge->height = height;
}

/*
 * Memeriksa apakah dapat menyimpan food
 */
boolean can_place(Fridge fridge, int row, int col, Food food) {
    boolean can = true;
    for (int i = row; i < food.size.height && can; i++) {
        for (int j = col; j < food.size.width && can; j++) {
            can = MatElmt(fridge.space, i, j) == '.';
        }
    }
    return can;
}

/*
 * Menempatkan food ke dalam fridge pada posisi (row, col).
 */
void place_food(Fridge *fridge, int row, int col, Food food) {
    FoodLoc fl = { food, row, col };
    for (int i = row; i < row + food.size.height; i++) {
        for (int j = col; j < col + food.size.width; j++) {
            MatElmt(fridge->space, i, j) = 'X';
        }
    }
    fridge->foods[fridge->food_count] = fl;
    fridge->food_count++;
}

/*
 * Mengambil food dari dalam fridge yang ada di indeks idx dalam fridge.foods
 */
void take_food(Fridge *fridge, int idx, Food *food) {
    FoodLoc fl = fridge->foods[idx];
    *food = fl.food;
    for (int i = fl.row; i < food->size.height; i++) {
        for (int j = fl.col; j < food->size.width; j++) {
            MatElmt(fridge->space, i, j) = '.';
        }
    }
    // menghapus food dalam fridge.foods
    for (int i = idx; i < fridge->food_count - 1; i++) {
        fridge->foods[i] = fridge->foods[i + 1];
    }
    fridge->food_count--;
}

/*
 * Menampilkan fridge pada layar
 */
void display_fridge(Fridge fridge) {
    int w = log10(fridge.height);
    printf("%*c ", w, ' ');
    int cols = fridge.width < 10 ? fridge.width : 10;
    for (int col = 0; col < cols; col++) {
        if (col > 0)
            printf(" ");
        printf("%d", col);
    }
    printf("\n");
    for (int row = 0; row < fridge.height; row++) {
        printf("%*d ", w, row);
        for (int col = 0; col < fridge.width; col++) {
            if (col > 0)
                printf(" ");
            printf("%c", MatElmt(fridge.space, row, col));
        }
        printf("\n");
    }
    printf("\n");
    if (fridge.food_count > 0) {
        printf("List makanan:\n");
        printf("(Nama - Ukuran - Lokasi)\n");
        for (int i = 0; i < fridge.food_count; i++) {
            FoodLoc fl = fridge.foods[i];
            printf("%d. %s - %dx%d - (%d, %d)\n", i+1, STR_VALUE(fl.food.name), fl.food.size.width, fl.food.size.height, fl.row, fl.col);
        }
    } else {
        printf("Kulkas masih kosong.\n");
    }
}
