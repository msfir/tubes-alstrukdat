#ifndef FRIDGE_H
#define FRIDGE_H

#include <math.h>
#include <stdio.h>

#include "../food/food.h"
#include "../matrix/matrix.h"
#include "boolean.h"

typedef struct FoodLoc {
    Food food;
    int row;
    int col;
} FoodLoc;

typedef struct Fridge {
    Matrix space;
    FoodLoc foods[100];
    int width;
    int height;
    int food_count;
} Fridge;

/*
 * Konstruktor Fridge.
 * Membuat fridge dengan ukuran width x height
 */
void CreateFridge(Fridge *fridge, int width, int height);

/*
 * Memeriksa apakah dapat menyimpan food
 */
boolean can_put(Fridge fridge, int row, int col, Food food);

/*
 * Menempatkan food ke dalam fridge pada posisi (row, col).
 */
void put_food(Fridge *fridge, int row, int col, Food food);

/*
 * Mengambil food dari dalam fridge yang ada di indeks idx dalam fridge.foods
 */
void take_food(Fridge *fridge, int idx, Food *food);

/*
 * Menampilkan fridge pada layar
 */
void display_fridge(Fridge fridge);

#endif
