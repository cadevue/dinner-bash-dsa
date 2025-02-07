#include "matrix.h"
#include "../core/action.h"
#include <stdio.h>

void ResetMatrix(Matrix *mat, int rowEff, int colEff) {
    mat->rowEff = rowEff;
    mat->colEff = colEff;
    for (int i = 0; i < rowEff; i++) {
        for (int j = 0; j < colEff; j++) {
            mat->mat[i][j] = ACTION_NONE;
        }
    }
}

void SetMatrixElement(Matrix *mat, int row, int col, char element) {
    mat->mat[row][col] = element;
}

char GetElementAtLocation(const Matrix *mat, int x, int y) {
    if (x < 0 || x >= mat->rowEff || y < 0 || y >= mat->colEff) {
        return ACTION_INVALID;
    }

    return mat->mat[x][y];
}