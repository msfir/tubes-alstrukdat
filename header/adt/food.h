/* File: makanan.h */
/* Definisi ADT Food (Makanan) */

#ifndef FOOD_H
#define FOOD_H

#include "boolean.h"
#include "point.h"
#include "time.h"
#include "cstring.h"

enum Action { BUY, MIX, CHOP, FRY, BOIL };

/* *** Definisi TYPE Food *** */
typedef struct {
    String name;
    Time expiration_time;
    enum Action action_loc;
    Time delivery_time;
} Food;

/* *** Notasi Akses: selektor Makanan *** */
// clang-format off
#define Name(F)           (F).name
#define ExpirationTime(F) (F).expiration_time
#define ActionLocation(F) (F).action_loc
#define DeliveryTime(F)   (F).delivery_time
// clang-format on

void CreateFood(Food* F, String name, Time expiration_time, enum Action action_loc, Time delivery_time);

void DisplayFood(Food F);

#endif
