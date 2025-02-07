#pragma once

#include "../adt/static_list.h"
#include "../adt/matrix.h"
#include "../core/simulator.h"

void LoadFoodTypes(StaticList *foodTypes, const char *path);
void LoadRecipes(StaticList *recipes, StaticList *foodTypes, char *path);
void LoadMap(Matrix *map, Simulator *sim, const char *path);