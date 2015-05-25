/**
 * Some misc. utility functions, implemented on different occassions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "global.h"
#include "rand.h"

/* dumps the population to a file/stdout */
void dump_population (population *pop, int popsize, FILE *fpt)
{
	int i ;
	for (i = 0 ; i < popsize ; i++)
	{
		if(fpt == stdout) {
			fprintf(fpt, "%d: ", i+1);
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
			fprintf(fpt,"[%e, ", ind->obj[j]);
		else if (j == nobj-1)
			fprintf(fpt,"%e] ",  ind->obj[j]);
		else
			fprintf(fpt,"%e, ",  ind->obj[j]);
	}
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
		{
			if(j == 0)		
				fprintf(fpt,"[[%e, ",ind->constr[j]);
			else if (j == ncon-1)
				fprintf(fpt,"%e]] ", ind->constr[j]);
			else
				fprintf(fpt,"%e, ",  ind->constr[j]);
		}
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
		{
			if(j == 0)		
				fprintf(fpt,"{%e, ",ind->xreal[j]);
			else if (j == nreal-1)
				fprintf(fpt,"%e} ", ind->xreal[j]);
			else
				fprintf(fpt,"%e, ", ind->xreal[j]);
		}
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
	fprintf(fpt,"[[%e]] ",	ind->constr_violation);
	fprintf(fpt,"<%d> ",	ind->rank);
	fprintf(fpt,"(%e) ",	ind->crowd_dist);
	fprintf(fpt,"|%d|\n",	ind->is_opposite);
}

void dump_individual(individual *ind, FILE *fpt)
{
	int j, k ;
	for (j = 0 ; j < nobj ; j++)		
		fprintf(fpt,"%e\t", ind->obj[j]);
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
			fprintf(fpt,"%e\t",ind->constr[j]);
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
			fprintf(fpt,"%e\t",ind->xreal[j]);
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
		{
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
			fprintf(fpt, "\t");
		}
	fprintf(fpt,"%e\t",	ind->constr_violation);
	fprintf(fpt,"%d\t",	ind->rank);
	fprintf(fpt,"%e\t",	ind->crowd_dist);
	fprintf(fpt,"%d\n",	ind->is_opposite);
}

void dump_population_list(pop_list *survived_pop, FILE *fpt_all_survived)
{
	int i = 0 ;
	node *curr = survived_pop->head ;
	while(curr != END)
	{
		if(fpt_all_survived == stdout)
			dumpf_individual(curr->ind, fpt_all_survived);
		else
			dump_individual(curr->ind, fpt_all_survived);
		curr = curr->next ;
		i++ ;
	}
	return ;
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

/* get the best individual vector in O(n) */
void get_best_individual_vector(population *pop, int popsize, int obj_index, double *best_vec)
{
	int i ;
	individual *best_ind = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if(pop->ind[i].obj[obj_index] <= best_ind->obj[obj_index])
			best_ind = &(pop->ind[i]) ;
	memcpy(best_vec, best_ind->xreal, sizeof(double) * nreal);
	best_ind = NULL ;
}

/* get the best individual vector in O(n) */
void get_best_individual(population *pop, int popsize, int obj_index, individual *best_ind)
{
	int i ;
	individual *temp_best = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if(pop->ind[i].obj[obj_index] <= temp_best->obj[obj_index])
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
		/*if(ind[j].obj[obj_index] <= x->obj[obj_index])*/
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

/** some functions that may not be used anymore **/
/* same as above, but takes the popsize */
void evaluate_pop_with_size (population *pop, int poplength)
{
	int i;
	for (i=0; i<poplength; i++)	
		evaluate_ind (&(pop->ind[i]));	
	return;
}

/* same function with an popsize argument */
void initialize_pop_with_size (population *pop, int poplength)
{
	int i;
	for (i = 0 ; i < poplength ; i++)
		initialize_ind (&(pop->ind[i]));
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

/* Routine to perform non-dominated sorting */
void fill_nondominated_sort_with_size (population *mixed_pop, int mixed_popsize, 
					population *new_pop, int new_popsize)
{
	int flag;
	int i, j;
	int end;
	int front_size;
	int archieve_size;
	int rank=1;
	list *pool;
	list *elite;
	list *temp1, *temp2;
	pool = (list *)malloc(sizeof(list));
	elite = (list *)malloc(sizeof(list));
	front_size = 0;
	archieve_size=0;
	pool->index = -1;
	pool->parent = NULL;
	pool->child = NULL;
	elite->index = -1;
	elite->parent = NULL;
	elite->child = NULL;
	temp1 = pool;
	for (i = 0; i < mixed_popsize; i++)
	{
		insert (temp1,i);
		temp1 = temp1->child;
	}
	i=0;
	do
	{
		temp1 = pool->child;
		insert (elite, temp1->index);
		front_size = 1;
		temp2 = elite->child;
		temp1 = del (temp1);
		temp1 = temp1->child;
		do
		{
			temp2 = elite->child;
			if (temp1==NULL)
			{
				break;
			}
			do
			{
				end = 0;
				flag = check_dominance (&(mixed_pop->ind[temp1->index]), 
							&(mixed_pop->ind[temp2->index]));
				if (flag == 1)
				{
					insert (pool, temp2->index);
					temp2 = del (temp2);
					front_size--;
					temp2 = temp2->child;
				}
				if (flag == 0)
				{
					temp2 = temp2->child;
				}
				if (flag == -1)
				{
					end = 1;
				}
			}
			while (end!=1 && temp2!=NULL);
			if (flag == 0 || flag == 1)
			{
				insert (elite, temp1->index);
				front_size++;
				temp1 = del (temp1);
			}
			temp1 = temp1->child;
		}
		while (temp1 != NULL);
		temp2 = elite->child;
		j=i;
		if ( (archieve_size+front_size) <= new_popsize)
		{
			do
			{
				copy_ind (&mixed_pop->ind[temp2->index], &new_pop->ind[i]);
				new_pop->ind[i].rank = rank;
				archieve_size+=1;
				temp2 = temp2->child;
				i+=1;
			}
			while (temp2 != NULL);
			assign_crowding_distance_indices (new_pop, j, i-1);
			rank+=1;
		}
		else
		{
			crowding_fill (mixed_pop, new_pop, i, front_size, elite);
			archieve_size = new_popsize;
			for (j = i; j < new_popsize; j++)
			{
				new_pop->ind[j].rank = rank;
			}
		}
		temp2 = elite->child;
		do
		{
			temp2 = del (temp2);
			temp2 = temp2->child;
		}
		while (elite->child !=NULL);
	}
	while (archieve_size < new_popsize);
	while (pool!=NULL)
	{
		temp1 = pool;
		pool = pool->child;
		free (temp1);
	}
	while (elite!=NULL)
	{
		temp1 = elite;
		elite = elite->child;
		free (temp1);
	}
	return;
}

/* Routine to fill a population with individuals in the decreasing order of crowding distance */
void crowding_fill_with_size (population *mixed_pop, int mixed_popsize, 
				population *new_pop, int new_popsize, 
				int count, int front_size, list *elite)
{
	int *dist;
	list *temp;
	int i, j;
	assign_crowding_distance_list (mixed_pop, elite->child, front_size);
	dist = (int *)malloc(front_size*sizeof(int));
	temp = elite->child;
	for (j=0; j<front_size; j++)
	{
		dist[j] = temp->index;
		temp = temp->child;
	}
	quicksort_dist (mixed_pop, dist, front_size);
	for (i=count, j=front_size-1; i<new_popsize; i++, j--)
	{
		copy_ind(&mixed_pop->ind[dist[j]], &new_pop->ind[i]);
	}
	free (dist);
	return;
}
