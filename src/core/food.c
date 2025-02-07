#include "food.h"
#include <string.h>

/** Food Type */
void ResetFoodType(FoodType *foodType, int id, const char *name, char action, Duration timeToExpire, Duration timeToDeliver) {
    foodType->id = id;
    strcpy(foodType->name, name);
    foodType->actionType = action;
    foodType->timeToExpire = timeToExpire;
    foodType->timeToDeliver = timeToDeliver;
}

/** Food Instance */
void ResetFood(Food *food, const FoodType *type, Time currentTime) {
    food->type = type;
    food->expiredTime = currentTime;

    AddDuration(&food->expiredTime, &type->timeToExpire);
}