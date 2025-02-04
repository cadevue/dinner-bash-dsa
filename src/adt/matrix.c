#include "matrix.h"

void ResetMatrix(Matrix *mat, char rowEff, char colEff) {
    mat->rowEff = rowEff;
    mat->colEff = colEff;
    for (char i = 0; i < rowEff; i++) {
        for (char j = 0; j < colEff; j++) {
            mat->mat[i][j] = TILE_EMPTY;
        }
    }
}

char GetMatrixRowEff(const Matrix *mat) {
    return mat->rowEff;
}

char GetMatrixColEff(const Matrix *mat) {
    return mat->colEff;
}

void SetMatrixElement(Matrix *mat, char row, char col, char element) {
    mat->mat[row][col] = element;
}

void PrintMatrix(const Matrix *mat) {
    printf("Matrix:\n");
    for (char i = 0; i < mat->rowEff; i++) {
        printf("[");
        for (char j = 0; j < mat->colEff; j++) {
            printf("%c ", mat->mat[i][j]);
        }
        printf("]\n");
    }
}