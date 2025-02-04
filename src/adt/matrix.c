#include "matrix.h"
#include <stdio.h>

void ResetMatrix(Matrix *mat, int rowEff, int colEff) {
    mat->rowEff = rowEff;
    mat->colEff = colEff;
    for (int i = 0; i < rowEff; i++) {
        for (int j = 0; j < colEff; j++) {
            mat->mat[i][j] = TILE_EMPTY;
        }
    }
}

int GetMatrixRowEff(const Matrix *mat) {
    return mat->rowEff;
}

int GetMatrixColEff(const Matrix *mat) {
    return mat->colEff;
}

void SetMatrixElement(Matrix *mat, int row, int col, char element) {
    mat->mat[row][col] = element;
}

void PrintMatrix(const Matrix *mat) {
    printf("Matrix:\n");
    for (int i = 0; i < mat->rowEff; i++) {
        printf("[");
        for (int j = 0; j < mat->colEff; j++) {
            printf("%c ", mat->mat[i][j]);
        }
        printf("]\n");
    }
}