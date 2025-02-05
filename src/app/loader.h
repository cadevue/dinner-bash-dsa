#include "../adt/static_list.h"
#include "../adt/matrix.h"

void LoadFoodTypes(StaticList *foodTypes, const char *path);
void LoadRecipes(StaticList *recipes, const char *path);
void LoadMap(Matrix *map, const char *path);