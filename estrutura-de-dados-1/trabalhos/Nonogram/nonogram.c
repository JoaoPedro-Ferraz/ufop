#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nonogram.h"


Nonogram *NonogramAllocate(int dimension, int **rowHints, int **colHints) {
    Nonogram *nonogram = (Nonogram *)malloc(sizeof(Nonogram));
    if (!nonogram) {
        perror("Erro ao alocar memoria para o Nonogram");
        return NULL;
    }
    nonogram->dimension = dimension;

    nonogram->board = (int **)malloc(dimension * sizeof(int *));
    if (!nonogram->board) {
        free(nonogram);
        return NULL;
    }

    for (int i = 0; i < dimension; i++) {
        nonogram->board[i] = (int *)calloc(dimension, sizeof(int));
        if (!nonogram->board[i]) {
            while (--i >= 0) free(nonogram->board[i]);
            free(nonogram->board);
            free(nonogram);
            return NULL;
        }
    }

    nonogram->rowHints = rowHints;
    nonogram->colHints = colHints;

    return nonogram;
}

void NonogramFree(Nonogram *nonogram) {
    if (!nonogram) return;

    for (int i = 0; i < nonogram->dimension; i++) {
        free(nonogram->board[i]);
    }
    free(nonogram->board);

    for (int i = 0; i < nonogram->dimension; i++) {
        free(nonogram->rowHints[i]);
        free(nonogram->colHints[i]);
    }
    free(nonogram->rowHints);
    free(nonogram->colHints);
    free(nonogram);
}

Nonogram *NonogramRead() {
    int dimension;
    scanf("%d", &dimension);

    int **rowHints = (int **)malloc(dimension * sizeof(int *));
    int **colHints = (int **)malloc(dimension * sizeof(int *));

    for (int i = 0; i < dimension; i++) {
        int count;
        scanf("%d", &count);
        rowHints[i] = (int *)malloc((count + 1) * sizeof(int));
        rowHints[i][0] = count;
        for (int j = 1; j <= count; j++) {
            scanf("%d", &rowHints[i][j]);
        }
    }

    for (int i = 0; i < dimension; i++) {
        int count;
        scanf("%d", &count);
        colHints[i] = (int *)malloc((count + 1) * sizeof(int));
        colHints[i][0] = count;
        for (int j = 1; j <= count; j++) {
            scanf("%d", &colHints[i][j]);
        }
    }

    return NonogramAllocate(dimension, rowHints, colHints);
}

int validateLine(int *line, int dimension, int *hints, int hintCount) {
    int groupCount = 0, currentGroup = 0;
    int groups[dimension];

    for (int i = 0; i < dimension; i++) {
        if (line[i] == 1) {
            currentGroup++;
        } else if (currentGroup > 0) {
            groups[groupCount++] = currentGroup;
            currentGroup = 0;
        }
    }
    if (currentGroup > 0) {
        groups[groupCount++] = currentGroup;
    }

    if (groupCount != hintCount) return 0;
    for (int i = 0; i < groupCount; i++) {
        if (groups[i] != hints[i]) return 0;
    }

    return 1;
}

int validateBoard(Nonogram *nonogram) {
    int dimension = nonogram->dimension;

    for (int i = 0; i < dimension; i++) {
        if (!validateLine(nonogram->board[i], dimension, nonogram->rowHints[i] + 1, nonogram->rowHints[i][0])) {
            return 0;
        }
    }

    for (int j = 0; j < dimension; j++) {
        int col[dimension];
        for (int i = 0; i < dimension; i++) {
            col[i] = nonogram->board[i][j];
        }
        if (!validateLine(col, dimension, nonogram->colHints[j] + 1, nonogram->colHints[j][0])) {
            return 0;
        }
    }
    return 1;
}

int validatePartial(int *line, int dimension, int *hints, int hintCount, int pos) {
    int groupCount = 0, currentGroup = 0;
    int groups[dimension];

    for (int i = 0; i <= pos; i++) {
        if (line[i] == 1) {
            currentGroup++;
        } else if (currentGroup > 0) {
            groups[groupCount++] = currentGroup;
            currentGroup = 0;
        }
    }
    if (currentGroup > 0) {
        groups[groupCount++] = currentGroup;
    }

    for (int i = 0; i < groupCount; i++) {
        if (i >= hintCount || groups[i] > hints[i]) return 0;
    }
    
    return 1;
}

int isPartialValid(Nonogram *nonogram, int row, int col) {
    int dimension = nonogram->dimension;

    if (!validatePartial(nonogram->board[row], dimension, nonogram->rowHints[row] + 1, nonogram->rowHints[row][0], col)) {
        return 0;
    }

    int colData[dimension];
    for (int i = 0; i <= row; i++) {
        colData[i] = nonogram->board[i][col];
    }
    if (!validatePartial(colData, dimension, nonogram->colHints[col] + 1, nonogram->colHints[col][0], row)) {
        return 0;
    }

    return 1;
}

int solveNonogram(Nonogram *nonogram, int row, int col, int *solutionCount) {
    if (row == nonogram->dimension) {
        if (validateBoard(nonogram)) {
            printf("SOLUTION %d:\n", ++(*solutionCount));
            NonogramPrint(nonogram);
        }
        return 0;
    }

    int nextRow = (col == nonogram->dimension - 1) ? row + 1 : row;
    int nextCol = (col == nonogram->dimension - 1) ? 0 : col + 1;

    nonogram->board[row][col] = 1;
    if (isPartialValid(nonogram, row, col)) {
        solveNonogram(nonogram, nextRow, nextCol, solutionCount);
    }

    nonogram->board[row][col] = 0;
    if (isPartialValid(nonogram, row, col)) {
        solveNonogram(nonogram, nextRow, nextCol, solutionCount);
    }

    return 0;
}

int NonogramPlay(Nonogram *nonogram) {
    int solutionCount = 0;
    solveNonogram(nonogram, 0, 0, &solutionCount);

    if (solutionCount == 0) {
        printf("No solution was found!\n");
    }

    return solutionCount;
}

void NonogramPrint(const Nonogram *nonogram) {
    for (int i = 0; i < nonogram->dimension; i++) {
        for (int j = 0; j < nonogram->dimension; j++) {
            printf("%c ", nonogram->board[i][j] ? '*' : '.');
        }
        printf("\n");
    }
}