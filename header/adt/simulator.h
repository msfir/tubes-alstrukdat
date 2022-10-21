/* File: makanan.h */
/* Definisi ADT Simulator */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../boolean.h"
#include "point.h"
#include "prioqueuetime.h"
#include "time.h"

/* *** Definisi TYPE Simulator *** */
typedef struct {
    char username[0xff];
    Point location;
    PrioQueueTime inventory;
} Simulator;

/* *** Notasi Akses: selektor Simulator *** */
// clang-format off
#define Username(I)  (I).username
#define Location(I)  (I).location
#define inventory(I) (I).inventory
// clang-format on

#endif
