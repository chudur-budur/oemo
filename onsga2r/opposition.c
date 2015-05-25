/**
 * Codes for some opposition craps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "global.h"
#include "rand.h"

/*
 * take the current population
 * get the best individual w.r.t. f1: x_1
 * get the best individual w.r.t f2: x_2
 * draw a line between x_1 and x_2
 * get the normal from the mid-point
 * consider the normal as the reference point
 * generate opposite of w.r.t. the reference
 *
 */
/*#define NBEST 10*/
#define debug 0

/* #define zdt1 */
/* #define zdt3 */
/* #define zdt4 */
/* #define pol */
 #define osy 

#ifdef zdt1
	double e_star[2][30] = {{
			0.9993, 0.0000, 0.0000, 0.0002, 0.0000, 
			0.0001, 0.0004, 0.0003, 0.0001, 0.0002, 
			0.0002, 0.0004, 0.0003, 0.0003, 0.0012, 
			0.0004, 0.0007, 0.0003, 0.0001, 0.0010, 
			0.0002, 0.0000, 0.0001, 0.0001, 0.0001, 
			0.0003, 0.0001, 0.0002, 0.0000, 0.0003},
			{
			0.0000, 0.0001, 0.0001, 0.0003, 0.0001, 
			0.0005, 0.0006, 0.0001, 0.0003, 0.0003, 
			0.0001, 0.0007, 0.0016, 0.0003, 0.0009, 
			0.0002, 0.0017, 0.0006, 0.0002, 0.0002, 
			0.0007, 0.0003, 0.0004, 0.0000, 0.0001, 
			0.0001, 0.0003, 0.0000, 0.0001, 0.0003}
			};
#endif
#ifdef zdt4
	double e_star[2][10] = {{
			0.9948, -0.0004, -0.0032,  0.0010, 0.0004, 
			0.0014, -0.0008, -0.0001, -0.0012, 0.0044},
	       		{
			0.0000, -0.0005, -0.0040,  0.0010, 0.0004, 
			0.0014, -0.0006, -0.0000, -0.0012, 0.0044}
			};
#endif
#ifdef zdt3
	double e_star[2][30] = {{
			0.8509, 0.0004, 0.0003, 0.0004, 0.0005, 0.0007, 
			0.0001, 0.0014, 0.0003, 0.0010, 0.0001, 0.0000, 
			0.0001, 0.0000, 0.0002, 0.0014, 0.0021, 0.0008, 
			0.0001, 0.0000, 0.0001, 0.0008, 0.0004, 0.0004, 
			0.0002, 0.0012, 0.0001, 0.0000, 0.0011, 0.0023},
	       		{
			0.0000, 0.0011, 0.0008, 0.0001, 0.0018, 0.0011, 
			0.0006, 0.0003, 0.0002, 0.0001, 0.0001, 0.0001, 
			0.0013, 0.0010, 0.0003, 0.0004, 0.0004, 0.0001, 
			0.0001, 0.0000, 0.0005, 0.0004, 0.0001, 0.0001, 
			0.0005, 0.0017, 0.0001, 0.0003, 0.0006, 0.0008}
			};
#endif
#ifdef pol
	double e_star[2][2] = {{-3.001868e+00,	-9.991395e-01},
       				{1.000358e+00,	1.990154e+00}};	
#endif
#ifdef osy
	double e_star[2][12] = {{
		1.999642e+00, 1.193523e-04, 2.999553e+00, 5.349871e-04,	
		2.026485e-04, 3.705805e-02, 4.999195e+00, 1.000088e+00,	
		4.999796e+00, 6.093375e-06, 4.999761e+00, 1.491880e-01},
	        {
		1.710494e-03, 6.660965e-01, 9.818987e-01, 2.037913e+00, 	
		1.397197e-04, 5.956091e-03, 9.836092e-01, 1.019812e+00, 	
		1.000158e+00, 7.195912e-05, 1.000010e+00, 2.386555e-02}
		};
#endif

double generate_opposite_population_using_attractor(population *pop, int popsize, 
					population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize,
					int gen)
{
	int i, corrupted_genes = 0  ;
	double *x, *t ;

	t = (double*)malloc(sizeof(double) * nreal);

	gather_opposite_source_pop(pop, popsize, opposite_source_pop, opposite_popsize);
	x = (double*)malloc(sizeof(double) * nreal);
	for(i = 0 ; i < opposite_popsize; i++)
	{
		// get_target_scheme1(pop, popsize, opposite_source_pop->ind[i].xreal, t);
		// get_target_scheme2(pop, popsize, opposite_source_pop->ind[i].xreal, t, gen);
		get_target_scheme3(pop, popsize, opposite_source_pop->ind[i].xreal, t);
		corrupted_genes += generate_opposite_vector_q3(opposite_source_pop->ind[i].xreal, t, x);
		memcpy(opposite_pop->ind[i].xreal, x, sizeof(double) * nreal);
		opposite_pop->ind[i].is_opposite = 1 ;
	}	
	free(x);
	free(t);
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

void get_target_scheme3(population *pop, int popsize, double *s, double *t)
{
	int i ;
	double **e ;
	int *idx ;
	int max_index ;
	double dist, max_dist ;
	
	e = (double**)malloc(sizeof(double*) * 2 * nobj);
	for(i = 0 ; i < 2 * nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);


	int no_extreme(individual *ind);
	get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	for(i = 0 ; i < nobj ; i++)
		memcpy(e[i + nobj], e_star[i], sizeof(double) * nreal);
	
	idx = (int*)malloc(sizeof(int) * 2 * nobj);
	get_random_indices(idx, 2 * nobj);
	
	max_dist = get_vector_distance(s, e[idx[0]], nreal);
	max_index = idx[0] ;
	for(i = 1 ; i < nobj ; i++)
	{
		dist = get_vector_distance(s, e[idx[i]], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = idx[i] ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	free(idx);

	for(i = 0 ; i < 2 * nobj ; i++)
		free(e[i]);
	free(e);
}

void get_target_scheme2(population *pop, int popsize, double *s, double *t, int gen)
{
	int i;
	double **e ;
	double dist, max_dist ;
	int max_index ;

	e = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);

	if(gen <= 10)
	{
		for(i = 0 ; i < nobj ; i++)
			memcpy(e[i], e_star[i], sizeof(double) * nreal);
	}
	else
	{
		int no_extreme(individual *ind);
		get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	}
	
	max_dist = get_vector_distance(s, e[0], nreal);
	max_index = 0 ;
	for(i = 1 ; i < nobj ; i++)
	{
		dist = get_vector_distance(s, e[i], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = i ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	
	for(i = 0 ; i < nobj ; i++)
		free(e[i]);
	free(e);
}

void get_target_scheme1(population *pop, int popsize, double *s, double *t)
{
	int i ;
	double **e ;
	double dist, max_dist ;
	int max_index ;

	e = (double**)malloc(sizeof(double*) * 2 * nobj);
	for(i = 0 ; i < 2 * nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);

	int no_extreme(individual *ind);
	get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	for(i = 0 ; i < nobj ; i++)
		memcpy(e[i + nobj], e_star[i], sizeof(double) * nreal);

	max_dist = get_vector_distance(s, e[0], nreal);
	max_index = 0 ;
	for(i = 1 ; i < 2 * nobj ; i++)
	{
		dist = get_vector_distance(s, e[i], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = i ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	
	for(i = 0 ; i < 2 * nobj ; i++)
		free(e[i]);
	free(e);
}

int no_extreme(individual *ind)
{
	if(ind->crowd_dist < INF) return 1 ;
	else return 0 ;
}

int generate_opposite_vector_q3(double *s, double *t, double *d)
{
	double *stu, *s_t, dist ;
	int i, ccount = 0 ;

	s_t = (double*)malloc(sizeof(double) * nreal);
	stu = (double*)malloc(sizeof(double) * nreal);

	dist = get_vector_distance(s, t, nreal);
	vector_subtract(t, s, nreal, s_t);
	get_unit_vector(s_t, nreal, stu);
	multiply_scalar(stu, nreal, rndreal(dist * 0.75, dist));
	vector_add(s, stu, nreal, d);
	
	free(stu);
	free(s_t);
	for(i = 0 ; i < nreal ; i++)
	{
		if(isnan(d[i]))
		{
			d[i] = rndreal(min_realvar[i], max_realvar[i]);
			ccount++ ;
		}
		else if(d[i] < min_realvar[i])
		{
			d[i] = min_realvar[i] ;
			ccount++ ; 
		}
		else if(d[i] > max_realvar[i])
		{
			d[i] = max_realvar[i] ;
			ccount++ ;
		}
	}
	return ccount ;
}

void get_extreme_vectors(population *pop, int popsize, double **vec, int v_size, 
						int (*chooser)(individual *ind))
{
	int i ;
	pop_list *lst = new_list();
	for( i = 0 ; i < popsize ; i++)
		push_back(lst, &(pop->ind[i]));
	for(i = 0 ; i < v_size ; i++)
	{
		node* ptr = get_extreme_node(lst, chooser);
		memcpy(vec[i], ptr->ind->xreal, sizeof(double) * nreal);
		erase(lst, ptr);
	}
	free_list(lst);
}

node* get_extreme_node(pop_list *lst, int (*chooser)(individual *ind))
{
	double max_dist = -1.0 ;
	node *curr = lst->head;
        node *ptr = lst->head ;	
	while(curr != END)
	{
		if(curr->ind->crowd_dist >= max_dist && (*chooser)(curr->ind))
		{
			max_dist = curr->ind->crowd_dist ;
			ptr = curr ;
		}
		curr = curr->next ;
	}
	return ptr ;
}

void gather_opposite_source_pop(population *pop, int popsize, population 
				*opposite_source_pop, int opposite_popsize)
{
	int i ;
	int rank_compare(individual *i1, individual *i2);
	quicksort_(pop, popsize, rank_compare);
	for(i = 0 ; i < opposite_popsize; i++)
		indcpy(&pop->ind[rnd(0, opposite_popsize-1)], &opposite_source_pop->ind[i]);
}

int rank_compare(individual *i1, individual *i2)
{
	if(i1->rank <= i2->rank) return 1;
	else return 0 ;
}

/* count the number of opposite individuals in a population */
int count_opposite(population *pop, int popsize)
{
	int i, count ;
	count = 0 ;
	for(i = 0 ; i < popsize ; i++)
		if(pop->ind[i].is_opposite == 1)
			count++;
	return count ;
}

/* clears all the opposite flag of the individuals in a population */
void clear_opposite_flag(population *pop, int popsize)
{
	int i ;
	for(i = 0 ; i < popsize ; i++)
		pop->ind[i].is_opposite = 0 ;
}

void inject_opposite(population *srcpop, int srcsize, population *destpop)
{
	int i ;
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[i]));	
}

void inject_opposite_shuffle(population *srcpop, int srcsize, population *destpop, int destpopsize)
{
	int i, *index;
	index = (int*)malloc(sizeof(int) * srcsize);
	for(i = 0 ; i < srcsize ; i++) 
		index[i] = rnd(0, destpopsize-1);
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[index[i]]));
	free(index);	
}

void gather_survived_individuals(population *parent_pop, int popsize, pop_list *survived_pop)
{
	int i ;
	for( i = 0 ; i < popsize ; i++)
	{
		if(parent_pop->ind[i].is_opposite)
			push_back(survived_pop, &(parent_pop->ind[i]));
	}
	return ;
}
