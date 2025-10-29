#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}
int main()
{
    int n_values[] = {1000, 5000, 10000, 20000, 30000};
    int num_tests = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));
    printf("n\tTime (seconds)\n");
    FILE *fptr = fopen("bubble_sort_times.csv", "w");
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
        bubbleSort(arr, n);
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
