// Noah Hanks, nhanks10

#include "cachelab.h"
#include <stdio.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int blockSize, columnBlock, rowBlock, column, row, diagonal, tmp;

    // 32x32 case
    if (N == 32) {
        blockSize = 8;

        for (columnBlock = 0; columnBlock < N; columnBlock += blockSize)
            for (rowBlock = 0; rowBlock < N; rowBlock += blockSize)
                for (row = rowBlock; row < rowBlock + blockSize; row++) {
                    for (column = columnBlock; column < columnBlock + blockSize; column++) {
                        if (row == column) {
                            tmp = A[row][column];
                            diagonal = row;
                        } else
                            B[column][row] = A[row][column];
                    }
                    if (columnBlock == rowBlock)
                        B[diagonal][diagonal] = tmp;
                }

    } else if (N == 64) {
        int blockForRow, blockForCol;
        int row, col;
        int v0, v1, v2, v3, v4, v5, v6, v7;

        for (blockForCol = 0; blockForCol < M; blockForCol += 8) {
            for (blockForRow = 0; blockForRow < N; blockForRow += 8) {
                for (row = blockForRow; row < blockForRow + 4; row++) {
                    v0 = A[row][blockForCol];
                    v1 = A[row][blockForCol + 1];
                    v2 = A[row][blockForCol + 2];
                    v3 = A[row][blockForCol + 3];
                    v4 = A[row][blockForCol + 4];
                    v5 = A[row][blockForCol + 5];
                    v6 = A[row][blockForCol + 6];
                    v7 = A[row][blockForCol + 7];
                    B[blockForCol][row] = v0;
                    B[blockForCol + 1][row] = v1;
                    B[blockForCol + 2][row] = v2;
                    B[blockForCol + 3][row] = v3;
                    B[blockForCol][row + 4] = v4;
                    B[blockForCol + 1][row + 4] = v5;
                    B[blockForCol + 2][row + 4] = v6;
                    B[blockForCol + 3][row + 4] = v7;
                }
                for (col = blockForCol; col < blockForCol + 4; col++) {

                    // A left-down
                    v4 = A[blockForRow + 4][col];
                    v5 = A[blockForRow + 5][col];
                    v6 = A[blockForRow + 6][col];
                    v7 = A[blockForRow + 7][col];

                    // B right-above
                    v0 = B[col][blockForRow + 4];
                    v1 = B[col][blockForRow + 5];
                    v2 = B[col][blockForRow + 6];
                    v3 = B[col][blockForRow + 7];

                    // set B right-above
                    B[col][blockForRow + 4] = v4;
                    B[col][blockForRow + 5] = v5;
                    B[col][blockForRow + 6] = v6;
                    B[col][blockForRow + 7] = v7;

                    // set B left-down
                    B[col + 4][blockForRow] = v0;
                    B[col + 4][blockForRow + 1] = v1;
                    B[col + 4][blockForRow + 2] = v2;
                    B[col + 4][blockForRow + 3] = v3;

                    // set B right-down
                    B[col + 4][blockForRow + 4] = A[blockForRow + 4][col + 4];
                    B[col + 4][blockForRow + 5] = A[blockForRow + 5][col + 4];
                    B[col + 4][blockForRow + 6] = A[blockForRow + 6][col + 4];
                    B[col + 4][blockForRow + 7] = A[blockForRow + 7][col + 4];
                }
            }
        }
    } else /* random matrix */ {
        blockSize = 16;

        for (columnBlock = 0; columnBlock < M; columnBlock += blockSize)
            for (rowBlock = 0; rowBlock < N; rowBlock += blockSize)
                for (row = rowBlock; (row < rowBlock + blockSize) && (row < N); row++) {
                    for (column = columnBlock; (column < columnBlock + blockSize) && (column < M);
                         column++) {
                        if (row == column) {
                            tmp = A[row][column];
                            diagonal = row;
                        } else
                            B[column][row] = A[row][column];
                    }
                    if (rowBlock == columnBlock)
                        B[diagonal][diagonal] = tmp;
                }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, tmp;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; ++j)
            if (A[i][j] != B[j][i])
                return 0;

    return 1;
}