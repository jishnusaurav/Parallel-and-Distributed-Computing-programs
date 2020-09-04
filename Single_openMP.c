#include <omp.h>
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
int main()
{#pragma omp parallel
{
printf("Hello world!!\n");
#pragma omp single
printf("%d\n", omp_get_num_threads());
}}
