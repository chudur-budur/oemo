/**
 * Some misc. utility functions, implemented on different occassions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "global.h"
#include "rand.h"
#include "misc.h"

/* dumps the population to a file/stdout */
void dump_population (FILE *fpt, population *pop, int popsize)
{
	int i ;
	for (i = 0 ; i < popsize ; i++)
	{
		if(fpt == stdout || fpt == stderr)
		{
			fprintf(fpt, "%d: ", i);
			dumpf_individual(fpt, &(pop->ind[i]));
		}
		else
			dump_individual(fpt, &(pop->ind[i]));
	}
	return;
}

/* dumps an individual onto file/stdout */
void dumpf_individual(FILE *fpt, individual *ind)
{
	int j, k ;
	for (j = 0 ; j < nobj ; j++)
	{
		if(j == 0)
			fprintf(fpt,"[%.3f, ", ind->obj[j]);
		else if (j == nobj-1)
			fprintf(fpt,"%.3f] ",  ind->obj[j]);
		else
			fprintf(fpt,"%.3f, ",  ind->obj[j]);
	}
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
		{
			if(j == 0)
				fprintf(fpt,"[[%.3f, ",ind->constr[j]);
			else if (j == ncon-1)
				fprintf(fpt,"%.3f]] ", ind->constr[j]);
			else
				fprintf(fpt,"%.3f, ",  ind->constr[j]);
		}
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
		{
			if(j == 0)
				fprintf(fpt,"{%.3f, ",ind->xreal[j]);
			else if (j == nreal-1)
				fprintf(fpt,"%.3f} ", ind->xreal[j]);
			else
				fprintf(fpt,"%.3f, ", ind->xreal[j]);
		}
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
	fprintf(fpt,"[[%.3f]] ",	ind->constr_violation);
	fprintf(fpt,"<%d> ",		ind->rank);
	fprintf(fpt,"(%0.2e) ",		ind->crowd_dist);
	fprintf(fpt,"|%d|\n",		ind->is_opposite);
}

void dump_individual(FILE *fpt, individual *ind)
{
	int j, k ;
	for (j = 0 ; j < nobj ; j++)
		fprintf(fpt,"%.3f\t", ind->obj[j]);
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
			fprintf(fpt,"%.3f\t",ind->constr[j]);
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
			fprintf(fpt,"%.3f\t",ind->xreal[j]);
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
		{
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
			fprintf(fpt, "\t");
		}
	fprintf(fpt,"%.3f\t",	ind->constr_violation);
	fprintf(fpt,"%d\t",	ind->rank);
	fprintf(fpt,"%0.2e\t",	ind->crowd_dist);
	fprintf(fpt,"%d\n",	ind->is_opposite);
}

/* create a dummy individual from a vector, evaluates and prints it */
void get_extreme_individuals(population *pop, int popsize, individual *ind, int size,
                             int (*comparator)(individual *i1, individual *i2))
{
	int i ;
	pop_list *lst = new_list();
	for( i = 0 ; i < popsize ; i++)
		push_back_ptr(lst, &(pop->ind[i]));
	for(i = 0 ; i < size ; i++)
	{
		node* ptr = get_extreme_node(lst, comparator);
		indcpy(ptr->ind, &ind[i]);
		erase_ptr(lst, ptr);
	}
	free_list_ptr(lst);
}

node* get_extreme_node(pop_list *lst, int (*comparator)(individual *i1, individual *i2))
{
	node *best = lst->head ;
	node *curr = lst->head->next;
	while(curr != END)
	{
		if((*comparator)(curr->ind, best->ind))
			best = curr ;
		curr = curr->next ;
	}
	return best ;
}

/* get the individual in O(n) w.r.t some comparison op. */
void get_extreme_individual(population *pop, int popsize, individual *best_ind,
                            int (*comparator) (individual *i1, individual *i2))
{
	int i ;
	individual *temp_best = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if((*comparator)(&pop->ind[i], temp_best))
			temp_best = &(pop->ind[i]) ;
	indcpy(temp_best, best_ind);
	temp_best = NULL ;
}

/* the next 3 functions are for the quicksort stuffs O(nlogn) */
void quicksort_(population *pop, int popsize, int (*comparator)(individual *i1, individual *i2))
{
	quicksort_inner(pop, 0, popsize-1, comparator);
}

void quicksort_inner(population *pop, int p, int r, int (*comparator)(individual *i1, individual *i2))
{
	int q ;
	if (p < r)
	{
		q = partition_(pop->ind, p, r, comparator);
		quicksort_inner(pop, p, q-1, comparator);
		quicksort_inner(pop, q+1, r, comparator);
	}
}

int partition_(individual *ind, int p, int r, int (*comparator)(individual *i1, individual *i2))
{
	int i, j;
	individual *x = 0, *temp = 0;
	x = (individual*)malloc(sizeof(individual));
	temp = (individual*)malloc(sizeof(individual));

	*x = ind[r];
	i = p - 1 ;
	for(j = p ; j < r ; j++)
	{
		if((*comparator)(&ind[j], x))
		{
			i++ ;
			*temp = ind[i];
			ind[i] = ind[j];
			ind[j] = *temp ;
		}
	}
	*temp = ind[i+1] ;
	ind[i+1] = ind[r] ;
	ind[r] = *temp;
	free(temp);
	free(x);
	return i+1 ;
}

/* use system arraycopy (memcpy) for copying an individual */
void indcpy(individual *srcind, individual *destind)
{
	int i ;
	destind->rank = srcind->rank;
	destind->constr_violation = srcind->constr_violation;
	destind->crowd_dist = srcind->crowd_dist;
	if (nreal!=0) memcpy(destind->xreal, srcind->xreal, sizeof(double) * nreal);
	if (nbin!=0)
	{
		memcpy(destind->xbin, srcind->xbin, sizeof(double) * nbin);
		for (i = 0 ; i < nbin ; i++)
			memcpy(&(destind->gene[i]), &(srcind->gene[i]), sizeof(int) * nbits[i]);
	}
	memcpy(destind->obj, srcind->obj, sizeof(double) * nobj) ;
	if (ncon!=0) memcpy(destind->constr, srcind->constr, sizeof(double) * ncon);
	destind->is_opposite = srcind->is_opposite ;
	return;
}

/* use system arraycopy (memcpy) for copying population */
void popcpy(population *srcpop, int srcsize, population *destpop)
{
	int i ;
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[i]));
}

/** 
 * Initialize the memory locations with dummy values 
 * all the functions below are for shutting the valgrind
 * complains, some function takes extra parameter for array sizes.
 */
void initialize_ind_dummy (individual *ind)
{
	int j, k;
	if (nreal!=0)
		for (j=0; j<nreal; j++)
			ind->xreal[j] = 0.0 ;
	if (nbin!=0)
		for (j=0; j<nbin; j++)
		{
			for (k=0; k<nbits[j]; k++) ind->gene[j][k] = 0;
			ind->xbin[j] = 0.0 ;
		}
	for(j = 0 ; j < nobj ; j++) ind->obj[j] = 0.0 ;
	if(ncon!=0)
		for(j = 0 ; j < ncon ; j++)
			ind->constr[j] = 0.0 ;
	ind->rank = 0 ;
	ind->constr_violation = 0.0 ;
	ind->crowd_dist = 0.0 ;
	ind->is_opposite = 0 ;
	return;
}

void initialize_pop_dummy (population *pop)
{
	int i;
	for (i=0; i<popsize; i++)
		initialize_ind_dummy (&(pop->ind[i]));
	return;
}

void initialize_pop_with_size (population *pop, int poplength)
{
	int i;
	for (i = 0 ; i < poplength ; i++)
		initialize_ind (&(pop->ind[i]));
	return;
}

void initialize_pop_dummy_with_size (population *pop, int poplength)
{
	int i;
	for (i = 0 ; i < poplength ; i++)
		initialize_ind_dummy (&(pop->ind[i]));
	return;
}

