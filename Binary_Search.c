#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            return mid; // found
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // not found
}
int main()
{
    int n_values[] = {1000, 5000, 10000, 50000, 100000}; // different n values
    int num_tests = sizeof(n_values) / sizeof(n_values[0]);
    for (int t = 0; t < num_tests; t++)
    {
        int n = n_values[t];
        int *arr = (int *)malloc(n * sizeof(int));
        // Fill array with sorted values 1..n
        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }
        int key = n; // searching for last element (worst case)
        clock_t start = clock();
        int result = binarySearch(arr, n, key);
        clock_t end = clock();
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n=== Test Case %d ===\n", t + 1);
        printf("Array size (n): %d\n", n);
        printf("Searching for: %d\n", key);
        if (result != -1)
        {
            printf("Result: Element found at index %d\n", result);
        }
        else
        {
            printf("Result: Element not found\n");
        }
        printf("Time taken: %f seconds\n", time_taken);
        free(arr); // free memory
    }
    return 0;
}
