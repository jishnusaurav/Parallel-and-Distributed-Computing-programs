#include <omp.h>
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
int main()
{
int N;
N=10;
#pragma omp parallel
{
#pragma omp for nowait
for (int i=0; i<N; i++)
printf("I am from loop one %d\n",i);
#pragma omp for
for (int i=0; i<N; i++)
printf("I am from loop two %d\n",i+50);
}
}
