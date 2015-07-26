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
void dump_population (population *pop, int popsize, FILE *fpt)
{
	int i ;
	for (i = 0 ; i < popsize ; i++)
	{
		if(fpt == stdout)
		{
			fprintf(fpt, "%d: ", i);
			dumpf_individual(&(pop->ind[i]), fpt);
		}
		else
			dump_individual(&(pop->ind[i]), fpt);
	}
	return;
}

/* dumps an individual onto file/stdout */
void dumpf_individual(individual *ind, FILE *fpt)
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
	fprintf(fpt,"<%d> ",	ind->rank);
	fprintf(fpt,"(%0.2e) ",	ind->crowd_dist);
	fprintf(fpt,"|%d|\n",	ind->is_opposite);
}

void dump_individual(individual *ind, FILE *fpt)
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
void evaluate_and_print_vector(double *x, int nreal, FILE *fpt)
{
	individual *ind ;
	ind = (individual*)malloc(sizeof(individual));
	allocate_memory_ind(ind);
	initialize_ind(ind);
	memcpy(ind->xreal, x, sizeof(double) * nreal);
	evaluate_ind(ind);
	dump_individual(ind, fpt);
	deallocate_memory_ind(ind);
	free(ind);
}

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

void get_extreme_individual_vectors(population *pop, int popsize, double **vec, int size,
                                    int (*comparator)(individual *i1, individual *i2))
{
	int i ;
	pop_list *lst = new_list();
	for( i = 0 ; i < popsize ; i++)
		push_back_ptr(lst, &(pop->ind[i]));
	for(i = 0 ; i < size ; i++)
	{
		node* ptr = get_extreme_node(lst, comparator);
		memcpy(vec[i], ptr->ind->xreal, sizeof(double) * nreal);
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

/* get the individual vector in O(n) w.r.t. some comparison op. */
void get_extreme_individual_vector(population *pop, int popsize, double *best_vec,
                                   int (*comparator)(individual *i1, individual *i2))
{
	int i ;
	individual *best_ind = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if((*comparator)(&pop->ind[i], best_ind))
			best_ind = &(pop->ind[i]) ;
	memcpy(best_vec, best_ind->xreal, sizeof(double) * nreal);
	best_ind = NULL ;
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
