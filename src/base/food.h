#pragma once

#include "time.h"
#include "boolean.h"

#define MAX_FOOD_NAME_LENGTH 50
typedef struct {
    char id;
    char name[MAX_FOOD_NAME_LENGTH];
    char actionType;
    Duration timeToExpire;
    Duration timeToDeliver;
} FoodType;


void ResetFoodType(FoodType *foodType, char id, const char *name, Time expiredTime, Duration deliveryDuration);
char GetFoodId(const FoodType *foodType);
const char *GetFoodName(const FoodType *FoodType);
Duration GetFoodTimeToExpire(const FoodType *FoodType);
Duration GetFoorTimeToDeliver(const FoodType *FoodType);

typedef struct { 
    FoodType* type;
    Time expiredTime;
    Time deliveredTime;
} Food;

void ResetFood(Food *food, FoodType *type, Time currentTime);
bool IsFoodExpired(const Food *food, const Time currentTime);
bool IsFoodDelivered(const Food *food, const Time currentTime);