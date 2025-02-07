#include "food.h"
#include <string.h>

/** Food Type */
void ResetFoodType(FoodType *food, int id, const char *name, char action, Time expiredTime, Duration deliveryDuration) {
    food->id = id;
    strcpy(food->name, name);
    food->actionType = action;
    food->timeToExpire = expiredTime;
    food->timeToDeliver = deliveryDuration;
}

int GetFoodId(const FoodType *food) {
    return food->id;
}

const char *GetFoodName(const FoodType *food) {
    return food->name;
}

Time GetFoodTimeToExpire(const FoodType *food) {
    return food->timeToExpire;
}

Duration GetFoorTimeToDeliver(const FoodType *food) {
    return food->timeToDeliver;
}

/** Food Instance */
void ResetFood(Food *food, FoodType *type, Time currentTime) {
    food->type = type;
    food->expiredTime = currentTime;

    AddDuration(&food->expiredTime, &type->timeToExpire);
}

bool IsFoodExpired(const Food *food, const Time currentTime) {
    return IsEqOrLater(&food->expiredTime, &currentTime);
}