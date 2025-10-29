#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    free(L);
    free(R);
}
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int main()
{
    int n_values[] = {1000, 5000, 10000, 50000, 100000};
    int num_tests = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));
    printf("n\tTime (seconds)\n");
    for (int t = 0; t < num_tests; t++)
    {
        int n = n_values[t];
        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand();
        }
        clock_t start = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, time_taken);
        free(arr);
    }
    return 0;
}