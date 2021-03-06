# ifndef _OPPOSITION_H_
# define _OPPOSITION_H_

# include "poplist.h"

/**
 * All the opposition based functions are
 * defined in opposition.c
 */

/* used to read a line from a file, assuming there are 80 chars to be handled at a time */
#define LINECHARS 80

extern float op_ratio ;
extern int op_popsize;
extern pop_list *e_star ;

int init_extreme_pts_hardcoded(void);
int init_extreme_pts_hardcoded_weak(void);
int init_extreme_pts_from_file(void);
int init_extreme_pts_from_file_weighted(void);

void inject_extreme_points(population *pop);

void generate_opposite_population(population *pop, pop_list *op_parent, pop_list *op_child, 
		int gen, double *overshoot_stat);

void make_pool(population *pop, pop_list *pool);
pop_list* discard_weakly_dominated_points(population *pop, int size);
int weakly_dominates(individual *i1, individual *i2);

void gather_op_parent(population *pop, pop_list *op_parent);

void get_furthest_point_from_m_random_select(pop_list *pool, int m, double *s, double *t);
void get_random_point_from_m_random_select(pop_list *pool, int m, double *s, double *t);

int generate_opposite_vector_q3(double *s, double *t, double *d);

void clear_opposite_flag(population *pop);
void inject_opposite_shuffle(pop_list *op_child, population *destpop);
void gather_survived_individuals(population *parent_pop, pop_list *survived_pop);
void assign_rank_and_crowding_distance_with_size (population *new_pop, int psize);

# endif
