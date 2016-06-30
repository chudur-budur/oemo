# ifndef _MISC_H_
# define _MISC_H_

# include "poplist.h"

/**
 * Some random utility functions, some of them are used in opposition.c
 * some of them are written for statistical purposes, not part of the actual algorithm
 */

/* printing op */
void dump_population(FILE *fpt, population *pop, int popsize);
void dump_individual(FILE *fpt, individual *ind);
void dumpf_individual(FILE *fpt, individual *ind);

/** some O(n) search operations */
void get_extreme_individuals(population *pop, int popsize, individual *ind, int size,
                             int (*comparator)(individual *i1, individual *i2));
node* get_extreme_node(pop_list *lst, int (*comparator)(individual *i1, individual *i2));
void get_extreme_individual(population *pop, int popsize, individual *best_ind,
                            int (*comparator)(individual *i1, individual *i2)) ;

/** custom quicksort O(nlogn) */
void quicksort_(population *pop, int popsize, int (*comparator)(individual *i1, individual *i2));
void quicksort_inner(population *pop, int p, int r, int (*comparator)(individual *i1, individual *i2));
int partition_(individual *ind, int p, int r, int (*comparator)(individual *i1, individual *i2));

/** custom memory op */
void indcpy(individual *srcind, individual* destind);
void popcpy(population *srcpop, int srcsize, population *destpop);

/** 
 * all these below are for shutting the valgrind complains
 */
void initialize_pop_dummy (population *pop);
void initialize_ind_dummy (individual *ind);
void initialize_pop_with_size(population *pop, int poplength);
void initialize_pop_dummy_with_size(population *pop, int poplength);

# endif
