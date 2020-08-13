#include <omp.h>
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
int main()
{
int i;
int n;
scanf("%d",&n);
int a[n];
#pragma omp parallel for schedule(static,2)
for(i=1;i<n;i++)
{
for(int j=2;j<i;j++){
if(i%j==0){
printf("%d\n",i);
break;
}
}}
}
