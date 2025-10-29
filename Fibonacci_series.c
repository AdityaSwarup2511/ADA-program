#include <stdio.h>

void fibonacci(int n) {
    int t1 = 0, t2 = 1, nextTerm;

    for (int i = 3; i <= n; ++i) {
        nextTerm = t1 + t2;
        printf("%d, ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
    } else if (n == 1) {
        printf("Fibonacci Series: 0\n");
    } else if (n == 2) {
        printf("Fibonacci Series: 0, 1\n");
    } else {
        printf("Fibonacci Series: 0, 1, ");
        fibonacci(n);
    }

    return 0;
}