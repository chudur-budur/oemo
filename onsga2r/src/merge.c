/* Routine for mergeing two populations */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Routine to merge two populations into one */
void merge(population *pop1, population *pop2, population *pop3)
{
	int i, k;
	for (i=0; i<popsize; i++)
		copy_ind (&(pop1->ind[i]), &(pop3->ind[i]));
	for (i=0, k=popsize; i<popsize; i++, k++)
		copy_ind (&(pop2->ind[i]), &(pop3->ind[k]));
	return;
}

/* Routine to merge two populations into one */
void merge_with_size(population *pop1, int pop1size,	/* 4: 0, 1, 2, 3 */
                     population *pop2, int pop2size, /* 3: 0, 1, 2 */
                     population *pop3, int pop3size, /* 3: 0, 1, 2 */
                     population *pop4, int pop4size) /* 10: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
{
	int i, j ;
	for(i = 0, j = 0 ; i < pop1size ; i++, j++)
		indcpy(&(pop1->ind[i]), &(pop4->ind[j]));
	for(i = 0 ; i < pop2size ; i++, j++)
		indcpy(&(pop2->ind[i]), &(pop4->ind[j]));
	for(i = 0 ; i < pop3size ; i++, j++)
		indcpy(&(pop3->ind[i]), &(pop4->ind[j]));
	return;
}

/* Routine to copy an individual 'ind1' into another individual 'ind2' */
void copy_ind (individual *ind1, individual *ind2)
{
	int i, j;
	ind2->rank = ind1->rank;
	ind2->constr_violation = ind1->constr_violation;
	ind2->crowd_dist = ind1->crowd_dist;
	if (nreal!=0)
		for (i=0; i<nreal; i++)
			ind2->xreal[i] = ind1->xreal[i];
	if (nbin!=0)
		for (i=0; i<nbin; i++)
		{
			ind2->xbin[i] = ind1->xbin[i];
			for (j=0; j<nbits[i]; j++)
				ind2->gene[i][j] = ind1->gene[i][j];
		}
	for (i=0; i<nobj; i++)
		ind2->obj[i] = ind1->obj[i];
	if (ncon!=0)
		for (i=0; i<ncon; i++)
			ind2->constr[i] = ind1->constr[i];
	ind2->is_opposite = ind1->is_opposite ;
	return;
}
