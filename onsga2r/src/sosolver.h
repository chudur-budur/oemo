# ifndef _SOSOLVER_H_
# define _SOSOLVER_H_

# include "poplist.h"
# include "libsosolver.h" 

int sosolver(pop_list *lst);
void display(const mxArray* in);
void parse_result(double *x, int *feval, const mxArray *in);
void load_path(char *dest);

# endif
