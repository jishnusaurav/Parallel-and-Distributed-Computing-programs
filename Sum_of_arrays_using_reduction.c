#include <omp.h> 
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int b[10]={0,1,2,3,4,5,6,7,8,9};
    int sum;
    int i;
    
 #pragma omp parallel for reduction(+:sum)
		for (i=0; i < 10; i++) 
		{
		sum += a[i] + b[i]; 
		printf("%d\n",sum);
		}
		printf("%d",sum);
	    } 
