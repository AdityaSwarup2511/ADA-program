#include <stdio.h> 
#include <windows.h> // For QueryPerformanceCounter & Frequency 

long long memoization(int n, long long arr[]) {  
    if (n == 0) return arr[0] = 0; 
    else if (n == 1) return arr[1] = 1;  
    else if (arr[n] != -1) return arr[n]; 
    return arr[n] = memoization(n - 1, arr) + memoization(n - 2, arr); 
} 

int main() { 
    LARGE_INTEGER freq, start, end;  
    QueryPerformanceFrequency(&freq); // ticks per second

    for (int i = 25; i <= 60; i += 5) {  
        long long arr[i + 1]; 
        long long x = 0; 
        QueryPerformanceCounter(&start); 

        for (int j = 0; j < 1000; j++) { // run 1000 times for averaging  
            for (int k = 0; k <= i; k++) arr[k] = -1; 
            x = memoization(i, arr); 
        } 

        QueryPerformanceCounter(&end); 
        long long elapsed_ticks = end.QuadPart - start.QuadPart; 
        long long elapsed_ns = (elapsed_ticks * 1000000000LL) / freq.QuadPart;  
        double avg_ns = (double)elapsed_ns / 1000.0; 

        printf("fibonacci no %d is equal to %lld\n", i, x);  
        printf("average time per run = %.5f ns\n", avg_ns);  
        printf("average time per run = %e s\n\n", avg_ns/1e9); 
    } 
    return 0; 
}