#include "loader.h"
#include <stdio.h>

void LoadFoodTypes(StaticList *foodTypes, const char *path) {
    // Load
    ResetStaticList(foodTypes);
    printf("Loading food types from %s\n", path);
    PrintStaticList(foodTypes);
}

void LoadRecipes(StaticList *recipes, const char *path) {
    // Load
    ResetStaticList(recipes);
    printf("Loading recipes from %s\n", path);
    PrintStaticList(recipes);
}

void LoadMap(Matrix *map, const char *path) {
    // Load
    ResetMatrix(map, 0, 0);
    printf("Loading map from %s\n", path);
    PrintMatrix(map);
}