#include <stdio.h>

// Structure for an activity
typedef struct {
    int start;
    int finish;
} Activity;

// Function to sort activities by finish time
void sortActivities(Activity arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].finish > arr[j].finish) {
                Activity temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to select maximum number of non-overlapping activities
void activitySelection(Activity arr[], int n) {
    // Sort activities by their finish times
    sortActivities(arr, n);

    printf("\nSelected activities are:\n");

    // The first activity always gets selected
    int i = 0;
    printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, arr[i].start, arr[i].finish);

    // Consider the rest of the activities
    for (int j = 1; j < n; j++) {
        // If this activity starts after the last selected activity finishes
        if (arr[j].start >= arr[i].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", j + 1, arr[j].start, arr[j].finish);
            i = j;
        }
    }
}

int main() {
    int n;

    printf("Enter the number of activities: ");
    scanf("%d", &n);

    Activity arr[n];

    printf("Enter start and finish times of each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d:\n", i + 1);
        printf("Start time: ");
        scanf("%d", &arr[i].start);
        printf("Finish time: ");
        scanf("%d", &arr[i].finish);
    }

    activitySelection(arr, n);

    return 0;
}
