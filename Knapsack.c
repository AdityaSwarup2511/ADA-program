#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int capacity, int weight[], int profit[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int result = dp[n][capacity];

    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);

    return result;
}

int main() {
    srand(time(0));

    int sizes[] = {10, 20, 30, 40, 50};
    int capacities[] = {50, 100, 150, 200, 250};

    printf("------------------------------------------------------------\n");
    printf("%-8s %-12s %-15s %-15s %-15s\n", "Items", "Capacity", "Max Profit", "Time (s)", "Memory (Bytes)");
    printf("------------------------------------------------------------\n");

    for (int t = 0; t < 5; t++) {
        int n = sizes[t];
        int capacity = capacities[t];

        int *profits = (int *)malloc(n * sizeof(int));
        int *weights = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            profits[i] = rand() % 100 + 10;
            weights[i] = rand() % 30 + 1;
        }

        int runs = 100;
        clock_t start = clock();
        int result = 0;

        for (int r = 0; r < runs; r++) {
            result = knapSack(capacity, weights, profits, n);
        }

        clock_t end = clock();
        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_time = total_time / runs;
        size_t memory_used = (n + 1) * (capacity + 1) * sizeof(int);

        printf("%-8d %-12d %-15d %-15.8lf %-15zu\n", n, capacity, result, avg_time, memory_used);

        free(profits);
        free(weights);
    }

    printf("------------------------------------------------------------\n");
    printf("Time Complexity ~ O(n * W)\n");
    printf("Space Complexity ~ O(n * W)\n");
    printf("------------------------------------------------------------\n");

    return 0;
}