#include<stdio.h>
#include<time.h>  
#include<stdlib.h>  

int rec(int n){ 
    if(n==0){  
        return 0; 
    } 
    else if(n==1){  
        return 1; 
    } 
    else{ 
        return rec(n-1)+rec(n-2); 
    } 
} 

int main(){ 
    for(int i=10;i<=55;i+=5){  
        int x=0; 
        clock_t start=clock();  
        for(int j=0;j<1000;j++){ 
            x=rec(i); 
        } 
        clock_t end=clock(); 
        double t=(double)(end-start)/CLOCKS_PER_SEC/1000;  
        printf("fibonacci no %d is equal to %d\ntime taken=%f sec\n\n",i,x,t); 
    } 
}