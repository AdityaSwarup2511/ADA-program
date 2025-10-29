#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int **allocate_matrix(int size)
{
    int **matrix = (int **)malloc(size * sizeof(int *));
    if (!matrix)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        if (!matrix[i])
        {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
    }
    return matrix;
}
void fill_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}
void multiply_matrices(int **A, int **B, int **C, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void free_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}
int main()
{
    srand((unsigned int)time(NULL));
    int sizes[] = {50, 100, 150, 200, 250, 300};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    printf("Matrix Multiplication Timing (Iterative)\n");
    printf("=========================================\n");
    for (int s = 0; s < num_sizes; s++)
    {
        int N = sizes[s];
        int **A = allocate_matrix(N);
        int **B = allocate_matrix(N);
        int **C = allocate_matrix(N);
        fill_matrix(A, N);
        fill_matrix(B, N);
        clock_t start = clock();
        multiply_matrices(A, B, C, N);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Matrix size: %4d x %4d | Time taken: %.4f seconds\n", N, N, time_taken);
        free_matrix(A, N);
        free_matrix(B, N);
        free_matrix(C, N);
    }
    return 0;
}