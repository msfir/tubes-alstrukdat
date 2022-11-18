#include <stdio.h>
#include "food.h"

#include "cstring.h"

void CreateFood(Food* F, int id, String name, Time expiration_time, enum Action action_loc, Time delivery_time, Size size, Time processing_time) {
    Id(*F) = id;
    copy_string(&Name(*F), name);
    ExpirationTime(*F) = expiration_time;
    ActionLocation(*F) = action_loc;
    DeliveryTime(*F) = delivery_time;
    Size(*F) = size;
    ProcTime(*F) = processing_time;
}

void DisplayFood(Food F){ // i may change it to DescribeFood
    printf("Id Makanan\t: %d\n", Id(F));
    printf("Nama Makanan\t: %s\n", STR_VALUE(Name(F)));
    printf("Waktu Ekspirasi\t: "); TulisTIME(ExpirationTime(F)); printf("\n");
    printf("Lama Pengiriman\t: "); TulisTIME(DeliveryTime(F));printf("\n");
    printf("Aksi \t\t: %s\n", ActionName[ActionLocation(F)]);
}
