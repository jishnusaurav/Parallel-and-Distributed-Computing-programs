#include <omp.h> 
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{ 
    printf("Enter the number of subjects");
    int n;
    float average=0;
    int minimum=999999;
    int maximum=0;
    scanf("%d",&n);
    printf("Enter the marks of each subject");
    int arr[n];
    for(int j=0;j<n;j++){
	
	scanf("%d",&arr[j]);
		}
    
    	   int i;
     #pragma omp parallel shared(arr,average,minimum,maximum) private(i)
		 {
	   #pragma omp parallel sections 
		{
		#pragma omp section
			{
			for(i=0;i<n;i++)
				average+=(float)arr[i];
			average=average/n;
}
			
					
		#pragma omp section
			{
			for(i=0;i<n;i++){
				if(arr[i]<minimum)
					minimum=arr[i];
					}
			
			}
		#pragma omp section
			{
			for(i=0;i<n;i++){
				if(arr[i]>maximum)
					maximum=arr[i];
					}
			
			}
		}
}
			
printf("The average marks is %f\n",average);
printf("The minimum marks is %d\n",minimum);		
printf("The maximum marks is %d\n",maximum);		
printf("\n");
}
