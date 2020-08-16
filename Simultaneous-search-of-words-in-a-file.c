
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h> 
#define _GNU_SOURCE 
#include <sched.h>
#define BUFFER_SIZE 1000

int indexOf(FILE *fptr, const char *word, int *line, int *col);

int main(){


	   
     #pragma omp parallel 
		 {
		 #pragma omp sections nowait
			 { 
			#pragma omp section 
				{
				FILE *fptr;
				char path[100]="/home/jishnu/Desktop/desktop.txt";
				fptr = fopen(path, "r");
				char word1[50]="milk";
				int line1, col1;
				indexOf(fptr, word1, &line1, &col1);
			        if (line1 != -1)
				     printf("'%s' found at line: %d, col: %d\n", word1, line1 + 1, col1 + 1);
			        else
				     printf("'%s' does not exists.", word1);
			 	}
			#pragma omp section 
				{
				FILE *fptr;
				char path[100]="/home/jishnu/Desktop/desktop.txt";
				fptr = fopen(path, "r");
				char word[50]="plum";
				int line, col;
				indexOf(fptr, word, &line, &col);
			    	if (line != -1)
					printf("'%s' found at line: %d, col: %d\n", word, line + 1, col + 1);
			     	else
				 	printf("'%s' does not exists.", word);
						}
			#pragma omp section 
				{
				FILE *fptr;
				char path[100]="/home/jishnu/Desktop/desktop.txt";
				fptr = fopen(path, "r");
				char word[50]="best";
				int line, col;
				indexOf(fptr, word, &line, &col);
			    	if (line != -1)
					printf("'%s' found at line: %d, col: %d\n", word, line + 1, col + 1);
			     	else
				 	printf("'%s' does not exists.", word);
						}
			#pragma omp section 
				{
				FILE *fptr;
				char path[100]="/home/jishnu/Desktop/desktop.txt";
				fptr = fopen(path, "r");
				char word[50]="Hi";
				int line, col;
				indexOf(fptr, word, &line, &col);
			    	if (line != -1)
					printf("'%s' found at line: %d, col: %d\n", word, line + 1, col + 1);
			     	else
				 	printf("'%s' does not exists.", word);
						}
				
			 }  
		  } 
return 0;
}
int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, word);
        if (pos != NULL)
        {
            *col = (pos - str);
            break;
        	}
	 }
}
