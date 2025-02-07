#pragma once

#include "time.h"
#include "boolean.h"

#define MAX_FOOD_NAME_LENGTH 50

// Food Type
typedef struct {
    int id;
    char name[MAX_FOOD_NAME_LENGTH];
    char actionType;
    Duration timeToExpire;
    Duration timeToDeliver;
} FoodType;

void ResetFoodType(FoodType *foodType, int id, const char *name, char action, Duration timeToExpire, Duration timeToDeliver);

// Food Instance
typedef struct { 
    const FoodType* type;
    Time expiredTime;
} Food;

void ResetFood(Food *food, const FoodType *type, Time currentTime);
void ResetFoodWithExpired(Food *food, const FoodType *type, Duration timeToExpire);