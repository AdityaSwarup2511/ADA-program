#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN_SIZE 64
int **allocateMatrix(int size)
{
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)calloc(size, sizeof(int));
    }
    return matrix;
}
void freeMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}
void naiveMultiply(int **A, int **B, int **C, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
}
void addMatrix(int **A, int **B, int **result, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}
void subMatrix(int **A, int **B, int **result, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}
void strassenMultiply(int **A, int **B, int **C, int size)
{
    if (size <= MIN_SIZE)
    {
        naiveMultiply(A, B, C, size);
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
    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **tempA = allocateMatrix(newSize);
    int **tempB = allocateMatrix(newSize);
    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    addMatrix(A11, A22, tempA, newSize);
    addMatrix(B11, B22, tempB, newSize);
    strassenMultiply(tempA, tempB, M1, newSize);
    addMatrix(A21, A22, tempA, newSize);
    strassenMultiply(tempA, B11, M2, newSize);
    subMatrix(B12, B22, tempB, newSize);
    strassenMultiply(A11, tempB, M3, newSize);
    subMatrix(B21, B11, tempB, newSize);
    strassenMultiply(A22, tempB, M4, newSize);
    addMatrix(A11, A12, tempA, newSize);
    strassenMultiply(tempA, B22, M5, newSize);
    subMatrix(A21, A11, tempA, newSize);
    addMatrix(B11, B12, tempB, newSize);
    strassenMultiply(tempA, tempB, M6, newSize);
    subMatrix(A12, A22, tempA, newSize);
    addMatrix(B21, B22, tempB, newSize);
    strassenMultiply(tempA, tempB, M7, newSize);
    addMatrix(M1, M4, tempA, newSize);
    subMatrix(tempA, M5, tempB, newSize);
    addMatrix(tempB, M7, A11, newSize);
    addMatrix(M3, M5, A12, newSize);
    addMatrix(M2, M4, A21, newSize);
    subMatrix(M1, M2, tempA, newSize);
    addMatrix(tempA, M3, tempB, newSize);
    addMatrix(tempB, M6, A22, newSize);
    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i][j] = A11[i][j];
            C[i][j + newSize] = A12[i][j];
            C[i + newSize][j] = A21[i][j];
            C[i + newSize][j + newSize] = A22[i][j];
        }
    }
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(tempA, newSize);
    freeMatrix(tempB, newSize);
}
int main()
{
    int sizes[] = {16, 32, 64, 128, 256}; // Matrix sizes (must be powers of 2)
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    for (int s = 0; s < numSizes; s++)
    {
        int size = sizes[s];
        int **A = allocateMatrix(size);
        int **B = allocateMatrix(size);
        int **C = allocateMatrix(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        clock_t start = clock();
        strassenMultiply(A, B, C, size);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Matrix Size: %d x %d, Time Taken: %.6f seconds\n", size, size, time_taken);
        freeMatrix(A, size);
        freeMatrix(B, size);
        freeMatrix(C, size);
    }
    return 0;
}