#pragma once

#include "../core/boolean.h"

#define MAT_ROW_CAP 25
#define MAT_COL_CAP 25

typedef struct {
    char mat[MAT_ROW_CAP][MAT_COL_CAP];
    int rowEff;
    int colEff;
} Matrix;

void ResetMatrix(Matrix *mat, int rowEff, int colEff);
int GetMatrixRowEff(const Matrix *mat);
int GetMatrixColEff(const Matrix *mat);

void SetMatrixElement(Matrix *mat, int row, int col, char element);
char GetElementAtLocation(const Matrix *mat, int x, int y);