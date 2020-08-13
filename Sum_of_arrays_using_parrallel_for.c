#include <omp.h> 
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int b[10]={0,1,2,3,4,5,6,7,8,9};
    int sum[10];
    
    int i;
      int p=sched_getcpu();
	   #pragma omp parallel for schedule(static,2)
		for (i=0; i < 10; i++) 
		{
		sum[i] = a[i] + b[i]; 
		printf("CPU:%d\tThread:%d\tValue%d\t at i%d\n",p,omp_get_thread_num(),sum[i],i);
		}
		
	    } 
