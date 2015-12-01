# ifndef _VECUTILS_H_
# define _VECUTILS_H_

/**
 * Some functions for vector operations.
 * defined in vecutil.c
 */
void clear_vector(double *x, int length);
void get_unit_vector(double *x, int length, double *unit_vector);
void get_random_indices(int *x, int length);
void get_random_int_vector(int *x, int length, int min, int max);
void get_random_double_vector(double *x, int length, double min, double max);
void get_mid_point(double *x_1, double *x_2, int length, double *x_mid);
void multiply_scalar(double *x, int length, double val);
void hadamard_product(double *x, double *y, int length);
double get_dot_product(double *x, double *y, int length);
double get_vector_distance(double *x, double *y, int length);
void vector_subtract(double *x, double *y, int length, double *z);
void vector_add(double *x, double *y, int length, double *z);
void vector_abs(double *x, int length, double *y);
double get_determinant(double **m, int n);
int fltcmp(double a, double b, double delta); /* a == b, a < b, a > b */
double bracket(double x); /* <x> operator */
int factorial(int n);
double max(double a, double b);
double max_n(double *x, int length);
double sum(double a, double b);
double sum_n(double *x, int length);
void print_vector(FILE *fpt, double *x, int length);

# endif
