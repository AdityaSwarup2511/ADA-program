#include <stdio.h>
#include <time.h>

// Function to sort activities by their finish time
void sortActivities(int start[], int finish[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (finish[i] > finish[j])
            {
                // Swap finish times
                temp = finish[i];
                finish[i] = finish[j];
                finish[j] = temp;

                // Swap start times to keep pair consistent
                temp = start[i];
                start[i] = start[j];
                start[j] = temp;
            }
        }
    }
}

// Function to print the maximum set of non-overlapping activities
void activitySelection(int start[], int finish[], int n)
{
    // Step 1: Sort by finish time
    sortActivities(start, finish, n);

    printf("Selected Activities (start, finish):\n");

    // Step 2: Select first activity
    int i = 0;
    printf("(%d, %d)\n", start[i], finish[i]);

    // Step 3: Check next activities
    for (int j = 1; j < n; j++)
    {
        if (start[j] >= finish[i])
        {
            printf("(%d, %d)\n", start[j], finish[j]);
            i = j;
        }
    }
}

int main()
{
    int start[] = {1, 2, 3, 0, 5, 8, 5};
    int finish[] = {3, 4, 5, 6, 7, 9, 9};
    int n = sizeof(start) / sizeof(start[0]);

    // Start time measurement
    clock_t start_time = clock();
    for (int i = 0; i < 100000; i++)
    {
        activitySelection(start, finish, n);
    }
    // End time measurement
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / 100000 / CLOCKS_PER_SEC;
    printf("Time taken for 100000 iterations: %f seconds\n", time_taken);
    return 0;
}