#include "loader.h"
#include "../core/action.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LogParseError(FILE *file, char *line, char *reason) {
    printf("Failed to parse line: %s\n", line);
    printf("Reason: %s\n", reason);
    fclose(file);
}

void LoadFoodTypes(StaticList *foodTypes, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", path);
        return;
    }

    char line[100];
    int N = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        N = atoi(line);
    } else {
        LogParseError(file, line, "Number of food types not found or invalid");
        return;
    }

    ResetStaticList(foodTypes, TYPE_FOOD);
    for (int i = 0; i < N; i++)
    {
        // Read ID
        int id;
        if (fgets(line, sizeof(line), file) != NULL) {
            id = atoi(line);
        } else {
            LogParseError(file, line, "Food ID not found or invalid");
            return;
        }

        // Read name
        char name[MAX_FOOD_NAME_LENGTH];
        if (fgets(line, sizeof(line), file) != NULL) {
            line[strcspn(line, "\n")] = 0;
            strcpy(name, line);
        } else {
            LogParseError(file, line, "Food Name not found or invalid");
            return;
        }

        // Read time to expire
        int expDay, expHour, expMinute;
        if (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%d %d %d", &expDay, &expHour, &expMinute) != 3) {
                LogParseError(file, line, "Time to expire not found or invalid");
                return;
            }
        } else {
            LogParseError(file, line, "Time to expire not found or invalid");
            return;
        }
        Duration expireDuration = {expDay, expHour, expMinute};

        // Read time to deliver
        int delDay, delHour, delMinute;
        if (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%d %d %d", &delDay, &delHour, &delMinute) != 3) {
                LogParseError(file, line, "Delivery duration not found or invalid");
                return;
            }
        }
        Duration deliveryDuration = {delDay, delHour, delMinute};

        // Read Action
        char action;
        if (fgets(line, sizeof(line), file) != NULL) {
            action = line[0];
        } else {
            LogParseError(file, line, "Action not found or invalid");
            return;
        }

        FoodType foodType;
        ResetFoodType(&foodType, id, name, action, expireDuration, deliveryDuration);
        InsertLastStaticList(foodTypes, (StaticListElement) { .foodType = foodType });
    }

    printf("Food types loaded successfully\n");
}

Tree *FindOrCreateNode(StaticList *recipes, int foodId) {
    for (int i = 0; i < GetStaticListCount(recipes); i++) {
        Tree *node = (Tree *) (GetStaticListElement(recipes, i)->recipe);
        if (node->data.foodId == foodId) {
            return node;
        }
    }

    Tree *newNode = (Tree *)malloc(sizeof(Tree));
    newNode->data.foodId = foodId;
    newNode->childCount = 0;

    StaticListElement elmt = { .recipe = newNode };
    InsertLastStaticList(recipes, elmt);
    return newNode;
}

void LoadRecipes(StaticList *recipes, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", path);
        return;
    }

    ResetStaticList(recipes, TYPE_RECIPE);
    char line[100];
    int recipeCount = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        recipeCount = atoi(line);
    } else {
        LogParseError(file, line, "Number of recipes not found or invalid");
        return;
    }

    for (int i = 0; i < recipeCount; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            int parentId, childCount;
            if (sscanf(line, "%d %d", &parentId, &childCount) < 2) {
                LogParseError(file, line, "Invalid recipe format");
                return;
            }

            Tree *parentNode = FindOrCreateNode(recipes, parentId);

            // Traverse each token
            char *token = strtok(line, " ");
            token = strtok(NULL, " "); // Skip parent ID
            token = strtok(NULL, " "); // Skip child count

            // Add children
            while (token != NULL && childCount > 0) {
                int childId = atoi(token);
                Tree *childNode = FindOrCreateNode(recipes, childId);
                AddChild(parentNode, childNode);
                token = strtok(NULL, " ");
                childCount--;
            }
        } else {
            LogParseError(file, line, "Missing recipe data");
            return;
        }
    }
    fclose(file);

    printf("Recipes loaded successfully\n");
}

char MapConfigSymbolToAction(char symbol) {
    switch (symbol) {
        case '#':
            return ACTION_NONE;
        case 'X':
            return ACTION_OBSTACLE;
        case 'T':
            return ACTION_BUY;
        case 'M':
            return ACTION_MIX;
        case 'C':
            return ACTION_CHOP;
        case 'F':
            return ACTION_FRY;
        case 'B':
            return ACTION_BOIL;
        case 'S':
            return ACTION_SIM_POS;
        default:
            return ACTION_INVALID;
    }
}

void LoadMap(Matrix *map, Simulator *sim, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", path);
        return;
    }

    char line[100];
    int rowEff, colEff;

    if (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%d %d", &rowEff, &colEff) != 2) {
            LogParseError(file, line, "Invalid map dimensions");
            return;
        }
    } else {
        LogParseError(file, line, "Map dimensions not found");
        return;
    }

    ResetMatrix(map, rowEff, colEff);

    for (int i = 0; i < rowEff; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            for (int j = 0; j < colEff && line[j] != '\0' && line[j] != '\n'; j++) {
                char action = MapConfigSymbolToAction(line[j]);
                if (action == ACTION_INVALID) {
                    char reason[50];
                    sprintf(reason, "Invalid map tile: %c", line[j]);
                    LogParseError(file, line, reason);
                    return;
                } else if (action == ACTION_SIM_POS) {
                    SetSimulatorPosition(sim, i, j);
                } else {
                    SetMatrixElement(map, i, j, action);
                }
            }
        } else {
            LogParseError(file, line, "Missing map row data");
            return;
        }
    }
    fclose(file);

    printf("Map loaded successfully\n");
}
