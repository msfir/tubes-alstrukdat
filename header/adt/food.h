/* File: makanan.h */
/* Definisi ADT Food (Makanan) */

#ifndef FOOD_H
#define FOOD_H

#include "../boolean.h"
#include "time.h"
#include "point.h"

enum Action {
	BUY,
	MIX,
	CHOP,
	FRY,
	BOIL
};

/* *** Definisi TYPE Food *** */
typedef struct { 
	char name[0xff];
	Time expiration_time;
	Action action_loc;
	Time delivery_time;
} Food;

/* *** Notasi Akses: selektor Makanan *** */
#define Name(F)           (F).name
#define ExpirationTime(F) (F).expiration_time
#define ActionLocation(F) (F).action_loc
#define DeliveryTime(F)   (F).delivery_time

#endif
