
#include "mpi.h"      // must have a system with an MPI library
#include <stdio.h>    //printf
#include <stdlib.h>   //malloc


#define MASTER 0         //One process will take care of initialization
#define ARRAY_SIZE 8     //Size of arrays that will be added together.

/*
 *  In MPI programs, the main function for the program is run on every
 *  process that gets initialized when you start up this code using mpirun.
 */
int main (int argc, char *argv[]) 
{
	// elements of arrays a and b will be added
	// and placed in array c
	int * a;
	int * b; 
	int * c;
	
	int total_proc;	 // total nuber of processes	
	int rank;        // rank of each process
	int n_per_proc;	// elements per process	
	int n = ARRAY_SIZE;   // number of array elements
	int i;       // loop index
		
	MPI_Status status;   // not used in this arguably poor example
	                     // that is devoid of error checking.

	// 1. Initialization of MPI environment
	MPI_Init (&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &total_proc);
	// 2. Now you know the total number of processes running in parallel
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	// 3. Now you know the rank of the current process
	
	// Smaller arrays that will be held on each separate process
    	int * ap;
	int * bp;
	int * cp;
	
	// 4. We choose process rank 0 to be the root, or master,
	// which will be used to  initialize the full arrays.
	if (rank == MASTER)  {
		a = (int *) malloc(sizeof(int)*n);
		b = (int *) malloc(sizeof(int)*n);
		c = (int *) malloc(sizeof(int)*n);
		
		// initialize arrays a and b with consecutive integer values
		// as a simple example
		for(i=0;i<n;i++)
			a[i] = i;
		for(i=0;i<n;i++)
			b[i] = i;
	}
	
	// All processes take part in the calculations concurrently
		
	// determine how many elements each process will work on
	n_per_proc = n/total_proc;
	/////// NOTE:
	// In this simple version, the number of processes needs to
	// divide evenly into the number of elements in the array
	///////////
	
	// 5. Initialize my smaller subsections of the larger array
	ap = (int *) malloc(sizeof(int)*n_per_proc);
	bp = (int *) malloc(sizeof(int)*n_per_proc);
	cp = (int *) malloc(sizeof(int)*n_per_proc);
	
	// 6.
	//scattering array a from MASTER node out to the other nodes
	MPI_Scatter(a, n_per_proc, MPI_INT, ap, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD); 
	//scattering array b from MASTER node out to the other node
	MPI_Scatter(b, n_per_proc, MPI_INT, bp, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD); 
	
	// 7. Compute the addition of elements in my subsection of the array
	for(i=0;i<n_per_proc;i++)
		cp[i] = ap[i]+bp[i];
	
	// 8. MASTER node gathering array c from the workers
	MPI_Gather(cp, n_per_proc, MPI_INT, c, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD);

/////////////////////// all concurrent processes are finished once they all communicate
/////////////////////// data back to the master via the gather function.

	// Master process gets to here only when it has been able to gather from all processes
	if (rank == MASTER)  {			
		// sanity check the result  (a test we would eventually leave out)
		int good = 1;
		for(i=0;i<n;i++) {
			printf ("%d ", c[i]);
			
			}	
	}
	// clean up memory
	if (rank == MASTER)  {
		free(a);  free(b); free(c);
	}
	free(ap);  free(bp); free(cp);
	
	// 9. Terminate MPI Environment and Processes
	MPI_Finalize();  
	
	return 0;
}
