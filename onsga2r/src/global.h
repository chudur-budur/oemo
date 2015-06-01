/* This file contains the variable and function declarations */

# ifndef _GLOBAL_H_
# define _GLOBAL_H_

# define INF 1.0e14
# define EPS 1.0e-14
# define E  2.71828182845905
# define PI 3.14159265358979
# define GNUPLOT_COMMAND "gnuplot -persist"

typedef struct
{
	int rank;
	double constr_violation;
	double *xreal;
	int **gene;
	double *xbin;
	double *obj;
	double *constr;
	double crowd_dist;
	int is_opposite ;
}
individual;

typedef struct
{
	individual *ind;
}
population;

typedef struct lists
{
	int index;
	struct lists *parent;
	struct lists *child;
}
list;

extern int nreal;
extern int nbin;
extern int nobj;
extern int ncon;
extern int popsize;
extern double pcross_real;
extern double pcross_bin;
extern double pmut_real;
extern double pmut_bin;
extern double eta_c;
extern double eta_m;
extern int ngen;
extern int nbinmut;
extern int nrealmut;
extern int nbincross;
extern int nrealcross;
extern int *nbits;
extern double *min_realvar;
extern double *max_realvar;
extern double *min_binvar;
extern double *max_binvar;
extern int bitlength;
extern int choice;
extern int obj1;
extern int obj2;
extern int obj3;
extern int angle1;
extern int angle2;

void allocate_memory_pop (population *pop, int size);
void allocate_memory_ind (individual *ind);
void deallocate_memory_pop (population *pop, int size);
void deallocate_memory_ind (individual *ind);

double maximum (double a, double b);
double minimum (double a, double b);

void crossover (individual *parent1, individual *parent2, individual *child1, individual *child2);
void realcross (individual *parent1, individual *parent2, individual *child1, individual *child2);
void bincross (individual *parent1, individual *parent2, individual *child1, individual *child2);

void assign_crowding_distance_list (population *pop, list *lst, int front_size);
void assign_crowding_distance_indices (population *pop, int c1, int c2);
void assign_crowding_distance (population *pop, int *dist, int **obj_array, int front_size);

void decode_pop (population *pop);
void decode_ind (individual *ind);

void onthefly_display (population *pop, FILE *gp, int ii);

int check_dominance (individual *a, individual *b);

void evaluate_pop (population *pop);
void evaluate_ind (individual *ind);

void fill_nondominated_sort (population *mixed_pop, population *new_pop);
void crowding_fill (population *mixed_pop, population *new_pop, int count, int front_size, list *cur);

void initialize_pop (population *pop);
void initialize_ind (individual *ind);

void insert (list *node, int x);
list* del (list *node);

void merge(population *pop1, population *pop2, population *pop3);
void copy_ind (individual *ind1, individual *ind2);

void mutation_pop (population *pop);
void mutation_ind (individual *ind);
void bin_mutate_ind (individual *ind);
void real_mutate_ind (individual *ind);

void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

void assign_rank_and_crowding_distance (population *new_pop);

void report_pop (population *pop, FILE *fpt);
void report_feasible (population *pop, FILE *fpt);
void report_ind (individual *ind, FILE *fpt);

void quicksort_front_obj(population *pop, int objcount, int obj_array[], int obj_array_size);
void q_sort_front_obj(population *pop, int objcount, int obj_array[], int left, int right);
void quicksort_dist(population *pop, int *dist, int front_size);
void q_sort_dist(population *pop, int *dist, int left, int right);

void selection (population *old_pop, population *new_pop);
individual* tournament (individual *ind1, individual *ind2);

/**
 * Some functions for list operations.
 * defined in poplist.c
 */
#define END NULL 
#define TRUE 1 
#define FALSE 0

typedef struct node node ;

struct node {
	individual *ind ;
	node *next ;
	node *prev ;
};

typedef struct { 
	node *head ;
	node *tail ;
	int size ;
} pop_list ;

pop_list* new_list();
void free_list(pop_list* lst);
int is_empty(pop_list *lst);
void push_back(pop_list *lst, individual *ind);
void erase(pop_list *lst, node *ptr);

/**
 * For the opposition based variation, scheme-1
 * defined in opposition.c
 */
void gather_opposite_source_pop(population *pop, int popsize, population 
				*opposite_source_pop, int opposite_popsize);
double generate_opposite_population_using_attractor(population *pop, int popsize, 
						population *opposite_source_pop, 
						population *opposite_pop, 
						int opposite_popsize, int gen);

int generate_opposite_vector_q3(double *s, double *t, double *d);

void get_furthest_point_from_entire_pool(population *pop, int popsize, 
		double **pool, int pool_size, double *s, double *t);
void get_furthest_point_from_m_random_select(population *pop, int popsize, 
		double **pool, int pool_size, int m, double *s, double *t);

void make_pool_scheme1(population *pop, int popsize, double **pool, int pool_size, int gen);
void make_pool_scheme2(population *pop, int popsize, double **pool, int pool_size);
void make_pool_scheme3(population *pop, int popsize, double **pool, int pool_size);
void make_pool_scheme4(population *pop, int popsize, double **pool, int pool_size);
void get_nadir_point(population *pop, int popsize, double *w);
double get_hypersimplex_volume(individual **e, int size, double *w);

int count_opposite(population *pop, int popsize);
void clear_opposite_flag(population *pop, int popsize);

void inject_opposite(population *srcpop, int srcsize, population *destpop);
void inject_opposite_shuffle(population *srcpop, int srcsize, population *destpop, int destpopsize);

void gather_survived_individuals(population *parent_pop, int popsize, pop_list *survived_pop);

/**
 * Some random utility functions, implemented on different occassions.
 * defined in misc.c
 */
int factorial(int n);
void dump_population(population *pop, int popsize, FILE *fpt);
void dump_individual(individual *ind, FILE *fpt);
void dumpf_individual(individual *ind, FILE *fpt);
void dump_population_list(pop_list *survived_pop, FILE *fpt_all_survived);
void evaluate_and_print_vector(double *x, int nreal, FILE *fpt);

void get_extreme_individuals(population *pop, int popsize, individual **ind, int size,
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

void evaluate_pop_with_size (population *pop, int poplength);
void initialize_pop_with_size (population *pop, int poplength);
void merge_with_size(population *pop1, int pop1size, 
			population *pop2, int pop2size, 
			population *pop3, int pop3size, 
			population *pop4, int pop4size);
void fill_nondominated_sort_with_size (population *mixed_pop, int mixed_popsize, 
		population *new_pop, int new_popsize);
void crowding_fill_with_size (population *mixed_pop, int mixed_popsize, 
				population *new_pop, int new_popsize, 
				int count, int front_size, list *cur);

/**
 * Some functions for vector operations.
 * defined in vectorop.c
 */
void clear_vector(double *x, int length);
void get_unit_vector(double *x, int length, double *unit_vector);
void get_random_indices(int *x, int length);
void get_random_int_vector(int *x, int length, int min, int max);
void get_radom_double_vector(double *x, int length, double min, double max);
void get_mid_point(double *x_1, double *x_2, int length, double *x_mid);
void multiply_scalar(double *x, int length, double val);
double get_dot_product(double *x, double *y, int length);
double get_vector_distance(double *x, double *y, int length);
void vector_subtract(double *x, double *y, int length, double *z);
void vector_add(double *x, double *y, int length, double *z);
double get_determinant(double **m, int n);
void print_vector(double *x, int length, FILE *fpt);

# endif
