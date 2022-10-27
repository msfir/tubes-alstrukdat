#include <stdio.h>
#include "food.h"

#include "cstring.h"

void CreateFood(Food* F, String name, Time expiration_time, enum Action action_loc, Time delivery_time){
    copy_string(&Name(*F), name);
    ExpirationTime(*F) = expiration_time;
    ActionLocation(*F) = action_loc;
    DeliveryTime(*F) = delivery_time;
}

void DisplayFood(Food F){ // i may change it to DescribeFood
    printf("Nama Makanan\t: %s\n", STR_VALUE(Name(F)));
    printf("Waktu Ekspirasi\t: "); TulisTIME(ExpirationTime(F)); printf("\n");
    printf("Lama Pengiriman\t: "); TulisTIME(DeliveryTime(F));printf("\n");
    printf("Aksi \t\t: %s\n", ActionLocation(F))
}
