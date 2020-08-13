//PRINT HELLO WORLD
#include<stdio.h>
#include<omp.h>
int main()
{
#pragma omp parallel
printf("Hello\n");
}
