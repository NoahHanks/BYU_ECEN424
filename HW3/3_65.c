// #include <stdio.h>
#define M 4
// // typedef int Marray_t[M][M];

// void print_matrix(long A[M][M]) {
//     long i, j;
//     for (i = 0; i < M; i++) {
//         for (j = 0; j < M; j++) {
//             printf("%8d   ", A[i][j]);
//         }
//         printf("\n");
//     }
// }

// void transpose(long A[M][M]) {
//     long i, j;
//     for (i = 0; i < M; i++) {
//         for (j = 0; j < i; j++) {
//             long t = A[i][j];
//             A[i][j] = A[j][i];
//             A[j][i] = t;
//         }
//     }
// }

void transpose_optimized(long A[M][M]) {
    int i, j;
    long *row, *col;

    for (i = 0; i < M; i++) {
        row = &A[i][0]; // row = A[i]
        col = &A[0][j]; // col = A[j]
        for (j = 0; j < M; j++) {
            long t = *row;
            *row = *col;
            *col = t;
            row++;
            col += M; // col = &A[j][i]
        }
    }
}

// int main() {
//     long i, j;
//     long A[M][M] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
//     print_matrix(A);
//     printf("\n");
//     transpose(A);
//     // transpose_optimized(A);
//     print_matrix(A);S
// }