#include <omp.h>
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
#include <time.h>int main ()
{
int a[10]={0,1,2,3,4,5,6,7,8,9};
int b[10]={0,1,2,3,4,5,6,7,8,9};
int sum[10];
int i;
clock_t t;
t = clock();
for (i=0; i < 10; i++)
{
sum[i] = a[i] + b[i];
}
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf(" took %f seconds to execute \n", time_taken);

int a[10]={0,1,2,3,4,5,6,7,8,9};
int b[10]={0,1,2,3,4,5,6,7,8,9};
int sum[10];
int i;
int p=sched_getcpu();
clock_t t;
t = clock();
#pragma omp parallel for schedule(static,2)
for (i=0; i < 10; i++)
{
sum[i] = a[i] + b[i];
}
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("took %f seconds to execute \n", time_taken);
}}
