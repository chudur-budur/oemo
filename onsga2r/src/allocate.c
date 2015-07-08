/* Memory allocation and deallocation routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to allocate memory to a population */
void allocate_memory_pop (population *pop, int size)
{
	int i;
	pop->ind = (individual *)malloc(size*sizeof(individual));
	for (i=0; i<size; i++)
		allocate_memory_ind (&(pop->ind[i]));
	return;
}

/* Function to allocate memory to an individual */
void allocate_memory_ind (individual *ind)
{
	/*int i;*/
	int j;
	if (nreal != 0)
	{
		ind->xreal = (double *)malloc(nreal*sizeof(double));
		/*for(i = 0 ; i < nreal ; i++) ind->xreal[i] = 0.0 ;*/
	}
	if (nbin != 0)
	{
		ind->xbin = (double *)malloc(nbin*sizeof(double));
		/*for(i = 0 ; i < nbin ; i++) ind->xbin[i] = 0.0 ;*/
		ind->gene = (int **)malloc(nbin*sizeof(int *));
		for (j = 0; j < nbin; j++)
		{
			ind->gene[j] = (int *)malloc(nbits[j]*sizeof(int));
			/*for(i = 0 ; i < nbits[j] ; i++) ind->gene[j] = 0 ;*/
		}
	}
	ind->obj = (double *)malloc(nobj*sizeof(double));
	/*for(i = 0 ; i < nobj ; i++) ind->obj[i] = 0.0 ;*/
	if (ncon != 0)
	{
		ind->constr = (double *)malloc(ncon*sizeof(double));
		/*for(i = 0 ; i < ncon ; i++) ind->constr[i] =  0.0 ;*/
	}
	ind->rank = -1 ;
	ind->crowd_dist = -1.0 ;
	ind->is_opposite = 0 ;
	return;
}

/* Function to deallocate memory to a population */
void deallocate_memory_pop (population *pop, int size)
{
	int i;
	for (i=0; i<size; i++)
		deallocate_memory_ind (&(pop->ind[i]));
	free (pop->ind);
	return;
}

/* Function to deallocate memory to an individual */
void deallocate_memory_ind (individual *ind)
{
	int j;
	if (nreal != 0)
		free(ind->xreal);
	if (nbin != 0)
	{
		for (j=0; j<nbin; j++)
			free(ind->gene[j]);
		free(ind->xbin);
		free(ind->gene);
	}
	free(ind->obj);
	if (ncon != 0)
		free(ind->constr);
	return;
}
