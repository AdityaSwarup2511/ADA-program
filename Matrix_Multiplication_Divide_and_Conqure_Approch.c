#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int **allocateMatrix(int size)
{
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        matrix[i] = (int *)calloc(size, sizeof(int));
    return matrix;
}
void freeMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}
void addMatrix(int **A, int **B, int **C, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}
void subMatrix(int **A, int **B, int **C, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}
void copySubMatrix(int **src, int **dest, int row_offset, int col_offset, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i][j] = src[i + row_offset][j + col_offset];
}
void pasteSubMatrix(int **src, int **dest, int row_offset, int col_offset, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i + row_offset][j + col_offset] = src[i][j];
}
void divideAndConquerMultiply(int **A, int **B, int **C, int size)
{
    if (size == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int newSize = size / 2;
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    copySubMatrix(A, A11, 0, 0, newSize);
    copySubMatrix(A, A12, 0, newSize, newSize);
    copySubMatrix(A, A21, newSize, 0, newSize);
    copySubMatrix(A, A22, newSize, newSize, newSize);
    copySubMatrix(B, B11, 0, 0, newSize);
    copySubMatrix(B, B12, 0, newSize, newSize);
    copySubMatrix(B, B21, newSize, 0, newSize);
    copySubMatrix(B, B22, newSize, newSize, newSize);
    divideAndConquerMultiply(A11, B11, M1, newSize);
    divideAndConquerMultiply(A12, B21, M2, newSize);
    addMatrix(M1, M2, C11, newSize);
    divideAndConquerMultiply(A11, B12, M1, newSize);
    divideAndConquerMultiply(A12, B22, M2, newSize);
    addMatrix(M1, M2, C12, newSize);
    divideAndConquerMultiply(A21, B11, M1, newSize);
    divideAndConquerMultiply(A22, B21, M2, newSize);
    addMatrix(M1, M2, C21, newSize);
    divideAndConquerMultiply(A21, B12, M1, newSize);
    divideAndConquerMultiply(A22, B22, M2, newSize);
    addMatrix(M1, M2, C22, newSize);
    pasteSubMatrix(C11, C, 0, 0, newSize);
    pasteSubMatrix(C12, C, 0, newSize, newSize);
    pasteSubMatrix(C21, C, newSize, 0, newSize);
    pasteSubMatrix(C22, C, newSize, newSize, newSize);
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
}
void fillMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}
int nextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n)
        power *= 2;
    return power;
}
int main()
{
    srand(time(NULL));
    int sizes[] = {16, 32, 64, 128, 256}; // Must be power of 2
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    for (int s = 0; s < numSizes; s++)
    {
        int size = sizes[s];
        printf("\nMatrix Size: %dx%d\n", size, size);
        int **A = allocateMatrix(size);
        int **B = allocateMatrix(size);
        int **C = allocateMatrix(size);
        fillMatrix(A, size);
        fillMatrix(B, size);
        clock_t start = clock();
        divideAndConquerMultiply(A, B, C, size);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Execution Time: %.6f seconds\n", time_spent);
        freeMatrix(A, size);
        freeMatrix(B, size);
        freeMatrix(C, size);
    }
    return 0;
}