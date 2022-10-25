#include <stdio.h>
#include "food.h"

#include <string.h> //dangerous!!!!!!!!!!! belum dibuat!!

void CreateFood(Food* F, char* name, Time expiration_time, enum Action action_loc, Time delivery_time){
    strcpy(Name(*F), name);
    ExpirationTime(*F) = expiration_time;
    ActionLocation(*F) = action_loc;
    DeliveryTime(*F) = delivery_time;
}

void DisplayFood(Food F){
    printf("nama\t\t:%s\n", Name(F));
    
}