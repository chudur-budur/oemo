# ifndef _MISC_H_
# define _MISC_H_

# include "poplist.h"

/**
 * Some random utility functions, implemented on different occassions.
 * defined in misc.c
 */

void initialize_pop_with_size (population *pop, int poplength);

void dump_population(population *pop, int popsize, FILE *fpt);
void dump_individual(individual *ind, FILE *fpt);
void dumpf_individual(individual *ind, FILE *fpt);
void evaluate_and_print_vector(double *x, int nreal, FILE *fpt);

void get_extreme_individuals(population *pop, int popsize, individual *ind, int size,
                             int (*comparator)(individual *i1, individual *i2));
void get_extreme_individual_vectors(population *pop, int popsize, double **vec, int size,
                                    int (*comparator)(individual *i1, individual *i2));
node* get_extreme_node(pop_list *lst, int (*comparator)(individual *i1, individual *i2));
void get_extreme_individual_vector(population *pop, int popsize, double *best_vec,
                                   int (*comparator)(individual *i1, individual *i2)) ;
void get_extreme_individual(population *pop, int popsize, individual *best_ind,
                            int (*comparator)(individual *i1, individual *i2)) ;

void quicksort_(population *pop, int popsize, int (*comparator)(individual *i1, individual *i2));
void quicksort_inner(population *pop, int p, int r, int (*comparator)(individual *i1, individual *i2));
int partition_(individual *ind, int p, int r, int (*comparator)(individual *i1, individual *i2));

void indcpy(individual *srcind, individual* destind);
void popcpy(population *srcpop, int srcsize, population *destpop);

# endif
