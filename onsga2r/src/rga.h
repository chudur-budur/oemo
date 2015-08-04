# ifndef _RGA_H_
# define _RGA_H_

#include "poplist.h"

/**
 * the generic real coded ga for single function optimization
 */
int rga(int pop_size, int max_gen, double pc, double pm, double etac, double etam,
        int obj_index, pop_list *lst);
int rga_bilevel(int pop_size, int max_gen, double pc, double pm, double etac, double etam,
                int obj_index, pop_list *lst);
void evaluate_population(population *pop, int size, int obj_index,
                         void (*eval_scheme)(individual *ind, int obj_index));
void mutation_pop_with_size (population *pop, int size);
void apply_tournament_selection(population *parent_pop, int parent_size,
                                population *child_pop, int child_size, int obj_index);

# endif
