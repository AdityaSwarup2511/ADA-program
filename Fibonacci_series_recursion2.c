#include<stdio.h>

int fibonacci(int n){
    int t1=0,t2=1, nextTerm;

    printf("Fibonacci series: ");
     for(int i=1;i<=n; ++i){
        printf("%d, ", t1);
        nextTerm= t1+t2;
        t1=t2;
        t2=nextTerm;
     }
     printf("\n");
}
int main(){
    int n;
    printf("Enter The Number Of Terms: ");
    scanf("%d",&n);

    fibonacci(n);
    return 0;
}