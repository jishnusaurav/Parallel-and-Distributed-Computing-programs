Q) Operations MPI_Send and MPI_Recv in MPI That is to say a line of M white boxes. To generate the next row, we define rules to determine the color of a next cell based on the colors of its neighbors on the current row. We define an initial state (first line). If we display the line at each stage of the treatment, depending on the rules and the initial state chosen, we obtain more or less complex patterns, which may be repetitive, present regularities or no longer evolve at all. Rules: a black box surrounded by 2 white boxes becomes white in the next step otherwise it remains black. A white box becomes black in the next step if it has at least one black neighbor. 1. Give the sequential code to simulate this phenomenon. 2. Parallelize this code using the MPI API. You can use the ring seen communication model in TD.

#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
  
// size of array 
#define n 10 
  
int colors_boxes[]={0,0,0,0,0,1,0,0,0,0,0,0};  
  
int main(int argc, char* argv[]) 
{ 
  
    int pid;  
    MPI_Status status; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
    MPI_Comm_size(MPI_COMM_WORLD, &np); 

    if (pid == 0) { 
        int index, i; 
        if (np > 1) {
                MPI_Send(&color, 
                         1, MPI_INT, i, 0, 
                         MPI_COMM_WORLD); 
            }  
        }
        for (int i = 1; i < np; i++) { 
            MPI_Recv(a[i], 1, MPI_INT, 
                     MPI_ANY_SOURCE, 0, 
                     MPI_COMM_WORLD, 
                     &status); 
            int sender = status.MPI_SOURCE; 
        } 
	for (int i = 0; i < np; i++) { 
		    if(arr[i]==1 && arr[i+1]==0 && arr[i-1]==0)
			arr[i]==0;
		} 
	for (int i = 0; i < np; i++) { 
		    if(arr[i]==0 && (arr[i+1]==1 || arr[i-1]==1))
			arr[i]==1;
		} 
	   } 
    // slave processes 
    else { 
	int color=color_boxes[i],a2;
	 MPI_Send(&color, 1, MPI_INT,0, 0, MPI_COMM_WORLD); 
	    } 
	MPI_Recv(&a2, n_elements_recieved, MPI_INT, 0, 0, MPI_COMM_WORLD,&status); 
    MPI_Finalize(); 
  
    return 0; 
} 
