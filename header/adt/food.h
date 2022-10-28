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
    int id;
    String name;
    Time expiration_time;
    enum Action action_loc;
    Time delivery_time;
} Food;

/* *** Notasi Akses: selektor Makanan *** */
//return int
#define Id(F)             (F).id
//return String
#define Name(F)           (F).name
//return Time
#define ExpirationTime(F) (F).expiration_time
//return enum Action
#define ActionLocation(F) (F).action_loc
//return Time
#define DeliveryTime(F)   (F).delivery_time

void CreateFood(Food* F, String name, Time expiration_time, enum Action action_loc, Time delivery_time);

void DisplayFood(Food F);

#endif
