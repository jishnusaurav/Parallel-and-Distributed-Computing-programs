
#include <omp.h> 
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{
    int a[2][2]={0,1,2,3};
     int b[2][2]={5,6,7,8};
    int sum[2][2];
        int diff[2][2];
    int i;
 #pragma omp parallel sections
		{
		#pragma omp section
	   #pragma omp parallel for schedule(static,2)
		for (i=0; i < 2; i++) 
		{
	   #pragma omp parallel for schedule(static,2)
		for (int j=0; j < 2; j++) {
		sum[i][j] = a[i][j] + b[i][j]; 
			}
		}
	#pragma omp section
	   #pragma omp parallel for schedule(static,2)
		for (i=0; i < 2; i++) 
		{
	   #pragma omp parallel for schedule(static,2)
		for (int j=0; j < 2; j++) {
		diff[i][j] = a[i][j] - b[i][j]; 
			}
		}
}
printf("Matrix addition\n");
for (int l=0; l < 2; l++) {
for (int k=0; k < 2; k++) {
		printf("%d  ",sum[l][k]);
			}
		printf("\n");
			}
		
	    
printf("Matrix subtraction\n");
for (int l=0; l < 2; l++) {
for (int k=0; k < 2; k++) {
		printf("%d  ",diff[l][k]);
			}
		printf("\n");
			}
		
	    } 
