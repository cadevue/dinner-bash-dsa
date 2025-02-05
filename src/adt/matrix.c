#include "matrix.h"
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
            printf("%c ", GetSymbolForAction(mat->mat[i][j]));
        }
        printf("]\n");
    }
}

char GetActionAtLocation(const Matrix *mat, int x, int y) {
    if (x < 0 || x >= mat->rowEff || y < 0 || y >= mat->colEff) {
        return ACTION_INVALID;
    }

    return mat->mat[x][y];
}

char GetSymbolForAction(char action) {
    switch (action) {
        case ACTION_NONE:
            return ' ';
        case ACTION_BUY:
            return 'B';
        case ACTION_MIX:
            return 'M';
        case ACTION_CHOP:
            return 'C';
        case ACTION_FRY:
            return 'F';
        case ACTION_BOIL:
            return 'B';
        default:
            return '*';
    }
}