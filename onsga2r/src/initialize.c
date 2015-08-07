/* Data initializtion routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to initialize a population randomly */
void initialize_pop (population *pop)
{
	int i;
	for (i=0; i<popsize; i++)
		initialize_ind (&(pop->ind[i]));
	return;
}

/* Function to initialize an individual randomly */
void initialize_ind (individual *ind)
{
	int j, k;
	if (nreal!=0)
		for (j=0; j<nreal; j++)
			ind->xreal[j] = rndreal (min_realvar[j], max_realvar[j]);
	if (nbin!=0)
		for (j=0; j<nbin; j++)
		{
			for (k=0; k<nbits[j]; k++)
				if (randomperc() <= 0.5)
					ind->gene[j][k] = 0;
				else
					ind->gene[j][k] = 1;
			ind->xbin[j] = 0.0 ;
		}
	for(j = 0 ; j < nobj ; j++)
		ind->obj[j] = 0.0 ;
	if(ncon!=0)
		for(j = 0 ; j < ncon ; j++)
			ind->constr[j] = 0.0 ;
	ind->rank = 0 ;
	ind->constr_violation = 0.0 ;
	ind->crowd_dist = 0.0 ;
	ind->is_opposite = 0 ;
	return;
}
