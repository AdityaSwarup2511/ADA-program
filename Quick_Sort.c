#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main()
{
    int n_values[] = {1000, 5000, 10000, 50000, 100000};
    int num_tests = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));
    printf("n\tTime (seconds)\n");
    FILE *fptr = fopen("quick_sort_times.csv", "w");
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
        quickSort(arr, 0, n - 1);
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