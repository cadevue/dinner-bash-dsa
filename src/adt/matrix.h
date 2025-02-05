#pragma once
#include "../core/boolean.h"

#define MAT_ROW_CAP 25
#define MAT_COL_CAP 25
// #define SL_ELMT_EQUAL(e1, e2) (e1.i == e2.i || e1.f == e2.f)

#define TILE_EMPTY 0
#define TILE_WALL  1

// /**  Static List is a fixed-size list with maximum size of STATIC_LIST_CAPACITY */
typedef struct {
    char mat[MAT_ROW_CAP][MAT_COL_CAP];
    int rowEff;
    int colEff;
} Matrix;

void ResetMatrix(Matrix *mat, int rowEff, int colEff);
int GetMatrixRowEff(const Matrix *mat);
int GetMatrixColEff(const Matrix *mat);

void SetMatrixElement(Matrix *mat, int row, int col, char element);
void PrintMatrix(const Matrix *mat);