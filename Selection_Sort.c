#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}
int main()
{
    int n_values[] = {100, 500, 1000, 2000, 3000};
    int num_tests = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));
    printf("n\tTime (seconds)\n");
    FILE *fptr = fopen("selection_sort_times.csv", "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "n,time_taken\n");
    }
    for (int t = 0; t < num_tests; t++)
    {
        int n = n_values[t];
        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand();
        }
        clock_t start = clock();
        selectionSort(arr, n);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, time_taken);
        if (fptr != NULL)
        {
            fprintf(fptr, "%d,%f\n", n, time_taken);
        }
        free(arr);
    }
    if (fptr != NULL)
    {
        fclose(fptr);
    }
    return 0;
}
