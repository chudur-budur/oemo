#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rand.h"
#include "global.h"
#include "rga.h"
#include "poplist.h"
#include "vecutils.h"
#include "misc.h"

/**
 * runs a real valued ga with specified population size,
 * generation and the objective to optimize.
 */

int obj_idx ;
individual worst_ind ;
individual best_ind ;
int obj_less_than(individual *i1, individual *i2);
int obj_greater_than(individual *i1, individual *i2);
int obj_greater_than_feasible(individual *i1, individual *i2);
int obj_less_than(individual *i1, individual *i2)
{
	if(i1->obj[obj_idx] < i2->obj[obj_idx])
		return 1 ;
	else
		return 0 ;
}

int obj_greater_than(individual *i1, individual *i2)
{
	if(i1->obj[obj_idx] > i2->obj[obj_idx])
		return 1 ;
	else
		return 0 ;
}

int obj_greater_than_feasible(individual *i1, individual *i2)
{
	if(i1->obj[obj_idx] > i2->obj[obj_idx]
	        && i1->constr_violation == 0.0)
		return 1 ;
	else
		return 0 ;
}
/** fitness evaluation schemes */
void debs_constrained_fitness(individual *ind, int obj_index);
void debs_constrained_fitness_weighted(individual *ind, int obj_index);
void debs_constrained_fitness_bilevel(individual *ind, int obj_index);
void debs_constrained_fitness_aasf(individual *ind, int obj_index);

int rga(int pop_size, int max_gen, double pc, double pm, double etac, double etam,
        int obj_index, pop_list *lst)
{
	int gen, feval = 0 ;
	double pm_orig, pc_orig, etac_orig, etam_orig ;
	individual best_ind ;
	population parent_pop ;
	population child_pop ;

	pm_orig = pmut_real ;
	pmut_real = pm ;
	pc_orig = pcross_real ;
	pcross_real = pc ;
	etac_orig = eta_c ;
	eta_c = etac ;
	etam_orig = eta_m ;
	eta_m = etam ;

	allocate_memory_ind(&worst_ind);
	allocate_memory_ind(&best_ind);

	obj_idx = obj_index ;

	allocate_memory_pop(&parent_pop, pop_size);
	allocate_memory_pop(&child_pop, pop_size);

	initialize_pop_with_size(&parent_pop, pop_size);
	initialize_pop_with_size(&child_pop, pop_size);
	get_extreme_individual(&parent_pop, pop_size, &worst_ind, obj_greater_than_feasible);
	evaluate_population(&parent_pop, pop_size, obj_index, debs_constrained_fitness);
	feval += pop_size ;

	for(gen = 1 ; gen < max_gen ; gen++)
	{
		apply_tournament_selection(&parent_pop, pop_size, &child_pop, pop_size, obj_index);
		mutation_pop_with_size(&child_pop, pop_size);
		popcpy(&child_pop, pop_size, &parent_pop);
		get_extreme_individual(&parent_pop, pop_size, &worst_ind, obj_greater_than_feasible);
		evaluate_population(&parent_pop, pop_size, obj_index, debs_constrained_fitness);
		feval += pop_size ;
	}
	/*fprintf(stdout, "\nfinal pop:\n");
	dump_population(&parent_pop, pop_size, stdout);*/

	get_extreme_individual(&parent_pop, pop_size, &best_ind, obj_less_than);
	push_back(lst, &best_ind);

	fprintf(stdout, "best_ind:\n");
	dumpf_individual(&best_ind, stdout);
	fprintf(stdout, "\n");

	deallocate_memory_pop(&parent_pop, pop_size);
	deallocate_memory_pop(&child_pop, pop_size);
	deallocate_memory_ind(&worst_ind);
	deallocate_memory_ind(&best_ind);

	pmut_real = pm_orig ;
	pcross_real = pc_orig ;
	eta_c = etac_orig ;
	eta_m = etam_orig ;

	return feval ;
}

int rga_bilevel(int pop_size, int max_gen, double pc, double pm, double etac, double etam,
                int obj_index, pop_list *lst)
{
	int gen, feval = 0 ;
	double pm_orig, pc_orig, etac_orig, etam_orig ;
	population parent_pop ;
	population child_pop ;

	pm_orig = pmut_real ;
	pmut_real = pm ;
	pc_orig = pcross_real ;
	pcross_real = pc ;
	etac_orig = eta_c ;
	eta_c = etac ;
	etam_orig = eta_m ;
	eta_m = etam ;

	allocate_memory_ind(&worst_ind);
	allocate_memory_ind(&best_ind);

	obj_idx = obj_index ;

	allocate_memory_pop(&parent_pop, pop_size);
	allocate_memory_pop(&child_pop, pop_size);

	initialize_pop_with_size(&parent_pop, pop_size);
	initialize_pop_with_size(&child_pop, pop_size);
	get_extreme_individual(&parent_pop, pop_size, &worst_ind, obj_greater_than_feasible);
	evaluate_population(&parent_pop, pop_size, obj_index, debs_constrained_fitness);
	feval += pop_size ;

	for(gen = 1 ; gen <= (int)(1 * (max_gen/3)); gen++)
	{
		apply_tournament_selection(&parent_pop, pop_size,
		                           &child_pop, pop_size, obj_index);
		mutation_pop_with_size(&child_pop, pop_size);
		popcpy(&child_pop, pop_size, &parent_pop);
		get_extreme_individual(&parent_pop, pop_size, &worst_ind,
		                       obj_greater_than_feasible);
		evaluate_population(&parent_pop, pop_size, obj_index,
		                    debs_constrained_fitness);
		feval += pop_size ;
	}
	get_extreme_individual(&parent_pop, pop_size, &best_ind, obj_less_than);
	for(gen = 1 ; gen <= (int)(2 * max_gen/3) ; gen++)
	{
		apply_tournament_selection(&parent_pop, pop_size,
		                           &child_pop, pop_size, obj_index);
		mutation_pop_with_size(&child_pop, pop_size);
		popcpy(&child_pop, pop_size, &parent_pop);
		get_extreme_individual(&parent_pop, pop_size, &worst_ind,
		                       obj_greater_than_feasible);
		evaluate_population(&parent_pop, pop_size, obj_index,
		                    debs_constrained_fitness_aasf);
		feval += pop_size ;
	}

	/*fprintf(stdout, "\nfinal pop:\n");
	dump_population(&parent_pop, pop_size, stdout);*/

	/* now save the extreme points */
	get_extreme_individual(&parent_pop, pop_size, &best_ind, obj_less_than);
	fprintf(stdout, "obj: %d, best_ind:\n", obj_idx);
	evaluate_ind(&best_ind);
	dumpf_individual(&best_ind, stdout);
	push_back(lst, &best_ind);

	deallocate_memory_pop(&parent_pop, pop_size);
	deallocate_memory_pop(&child_pop, pop_size);
	deallocate_memory_ind(&worst_ind);
	deallocate_memory_ind(&best_ind);

	pmut_real = pm_orig ;
	pcross_real = pc_orig ;
	eta_c = etac_orig ;
	eta_m = etam_orig ;

	return feval ;
}

void evaluate_population(population *pop, int size, int obj_index,
                         void (*eval_scheme)(individual *ind, int obj_index))
{
	int i ;
	for(i = 0 ; i < size ; i++)
		eval_scheme(&(pop->ind[i]), obj_index);
	return ;
}

void debs_constrained_fitness(individual *ind, int obj_index)
{
	int j;
	test_problem (ind->xreal, ind->xbin, ind->gene, ind->obj, ind->constr);
	if (ncon == 0)
		ind->constr_violation = 0.0;
	else
	{
		ind->constr_violation = 0.0;
		for (j = 0; j < ncon; j++)
			ind->constr_violation += bracket(ind->constr[j]);
	}
	if(ind->constr_violation > 0.0)
		ind->obj[obj_index] = worst_ind.obj[obj_index] + ind->constr_violation ;
	return ;
}

void debs_constrained_fitness_weighted(individual *ind, int obj_index)
{
	int j;
	double fval ;
	test_problem (ind->xreal, ind->xbin, ind->gene, ind->obj, ind->constr);
	if (ncon == 0)
		ind->constr_violation = 0.0;
	else
	{
		ind->constr_violation = 0.0;
		for (j = 0; j < ncon; j++)
			ind->constr_violation += bracket(ind->constr[j]);
	}
	fval = 0.0 ;
	for(j = 0 ; j < nobj ; j++)
	{
		if(j == obj_index)
			fval += ind->obj[obj_index] * 0.9 ;
		else
			fval += ind->obj[j] * ((1.0 - 0.9)/((double)(nobj - 1)));
	}
	ind->obj[obj_index] = fval ;
	if(ind->constr_violation > 0.0)
		ind->obj[obj_index] = worst_ind.obj[obj_index] + ind->constr_violation ;
	return ;
}

void debs_constrained_fitness_bilevel(individual *ind, int obj_index)
{
	int j;
	double cv ;

	test_problem (ind->xreal, ind->xbin, ind->gene, ind->obj, ind->constr);
	if (ncon == 0)
		ind->constr_violation = 0.0;
	else
	{
		ind->constr_violation = 0.0;
		for (j = 0; j < ncon; j++)
			ind->constr_violation += bracket(ind->constr[j]);
	}

	cv = 0.0 ;
	for(j = 0 ; j < nobj ; j++)
		if(j != obj_index && ind->obj[j] > best_ind.obj[j])
			cv += ind->obj[j] - best_ind.obj[j];
	ind->constr_violation += cv ;

	if(ind->constr_violation > 0.0)
		ind->obj[obj_index] = worst_ind.obj[obj_index] + ind->constr_violation ;
	return ;
}

void debs_constrained_fitness_aasf(individual *ind, int obj_index)
{
	int j;
	/* double w1, w2, w3, maxval ; */
	double *w, *f ;

	w = (double*)malloc(sizeof(double) * nobj);
	f = (double*)malloc(sizeof(double) * nobj);

	test_problem (ind->xreal, ind->xbin, ind->gene, ind->obj, ind->constr);
	if (ncon == 0)
		ind->constr_violation = 0.0;
	else
	{
		ind->constr_violation = 0.0;
		for (j = 0; j < ncon; j++)
			ind->constr_violation += bracket(ind->constr[j]);
	}

	for(j = 0 ; j < nobj ; j++)
	{
		if(j == obj_index)
			w[j] = 0.9 ;
		else
			w[j] = 0.1/(((double)nobj) - 1.0) ;
		f[j] = ind->obj[j] - best_ind.obj[j]/w[j] ;
	}
	ind->obj[obj_index] = max_n(f, nobj) + (0.001 * sum_n(f, nobj));


	/*if(obj_index == 0)
	{
		w1 = 0.95 ; w2 = 0.05 ;
		maxval = max((ind->obj[obj_index] - best_ind.obj[obj_index])/w1,
				(ind->obj[1] - best_ind.obj[1])/w2);
		maxval += 0.001 * sum((ind->obj[obj_index] - best_ind.obj[obj_index])/w1,
				(ind->obj[1] - best_ind.obj[1])/w2);
		ind->obj[obj_index] = maxval ;
	}

	if(obj_index == 1)
	{
		w1 = 0.95 ; w2 = 0.05 ;
		maxval = max((ind->obj[obj_index] - best_ind.obj[obj_index])/w1,
				(ind->obj[0] - best_ind.obj[0])/w2);
		maxval += 0.001 * sum((ind->obj[obj_index] - best_ind.obj[obj_index])/w1,
				(ind->obj[0] - best_ind.obj[0])/w2);
		ind->obj[obj_index] = maxval ;
	}*/

	if(ind->constr_violation > 0.0)
		ind->obj[obj_index] = worst_ind.obj[obj_index] + ind->constr_violation ;
	free(w);
	free(f);
	return ;
}

void mutation_pop_with_size (population *pop, int size)
{
	int i;
	for (i = 0; i < size; i++)
		mutation_ind(&(pop->ind[i]));
	return;
}

void apply_tournament_selection(population *parent_pop, int parent_size,
                                population *child_pop, int child_size, int obj_index)
{
	int *idx1, *idx2, i ;
	individual *p1, *p2 ;
	individual* apply_tournament(individual *i1, individual *i2, int obj_index);
	idx1 = (int*)malloc(sizeof(int) * parent_size);
	idx2 = (int*)malloc(sizeof(int) * parent_size);
	get_random_indices(idx1, parent_size);
	get_random_indices(idx2, parent_size);
	for(i = 0 ; i < parent_size ; i+=2)
	{
		p1 = apply_tournament(&(parent_pop->ind[idx1[i]]),
		                      &(parent_pop->ind[idx2[i]]), obj_index);
		p2 = apply_tournament(&(parent_pop->ind[idx1[i+1]]),
		                      &(parent_pop->ind[idx2[i+1]]), obj_index);
		crossover(p1, p2, &(child_pop->ind[i]), &(child_pop->ind[i+1]));
	}
	free(idx1);
	free(idx2);
	return ;
}

individual* apply_tournament(individual *i1, individual *i2, int obj_index)
{
	if(i1->obj[obj_index] < i2->obj[obj_index])
		return i1 ;
	else
		return i2 ;
}
