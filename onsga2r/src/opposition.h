# ifndef _OPPOSITION_H_
# define _OPPOSITION_H_

# include "poplist.h"

/**
 * For the opposition based variation, scheme-1
 * defined in opposition.c
 */
extern pop_list *e_star ;
int initialize_extreme_points(int pop_size, int max_gen, double pc, double pm, double etac, double etam);
void free_extreme_points();
void gather_opposite_source_pop(population *pop, int popsize, population 
				*opposite_source_pop, int opposite_popsize);
double generate_opposite_population_using_attractor(population *pop, int popsize, 
						population *opposite_source_pop, 
						population *opposite_pop, 
						int opposite_popsize, int gen);
void inject_extreme_points(population *pop, int popsize);

int generate_opposite_vector_q3(double *s, double *t, double *d);

void get_furthest_point_from_entire_pool(population *pop, int popsize, 
		double **pool, int pool_size, double *s, double *t);
void get_furthest_point_from_m_random_select(pop_list *pool, int m, double *s, double *t);

void make_pool_scheme5(population *pop, int popsize, pop_list *pool);
void get_nadir_point(population *pop, int popsize, double *w);
double get_hypersimplex_volume(individual *e, int size, double *w);
pop_list* select_best_extremes(population *pop, int size);
int weakly_dominates(individual *i1, individual *i2);
int weakly_dominated_by_set(individual *ind, pop_list *lst);

int count_opposite(population *pop, int popsize);
void clear_opposite_flag(population *pop, int popsize);

void inject_opposite(population *srcpop, int srcsize, population *destpop);
void inject_opposite_shuffle(population *srcpop, int srcsize, population *destpop, int destpopsize);

void gather_survived_individuals(population *parent_pop, int popsize, pop_list *survived_pop);

# endif
