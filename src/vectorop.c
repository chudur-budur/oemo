/**
 * Vector operations code
 */

#include <stdio.h>
#include <math.h>
#include "rand.h"

/* clears a vector in-situ */
void clear_vector(double *x, int length)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		x[i] = 0.0 ;
	return ;
}

/* populate the vector x with random indices 0 to length-1 */
void get_random_indices(int *x, int length)
{
	int i, r, temp ;
	for(i = 0 ; i < length; i++)
		x[i] = i ;
	for(i = 0 ; i < length ; i++)
	{
		r = rnd(0, length-1);
		temp = x[i] ;
		x[i] = x[r] ;
		x[r] = temp ;
	}
}

/* get a random int vector */
void get_random_int_vector(int *x, int length, int min, int max)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		x[i] = rnd(min, max);
}

/* get a random double vector */
void get_radom_double_vector(double *x, int length, double min, double max)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		x[i] = rndreal(min, max);
}

/* returns a unit vector from a given vector */
void get_unit_vector(double *x, int length, double *unit_vector)
{
	int i ;
	double mag;
	mag = 0.0 ;
	for(i = 0 ; i < length ; i++)
		mag += x[i] * x[i];
	mag = sqrt(mag);
	for(i = 0 ; i < length ; i++)
		unit_vector[i] = x[i]/mag ;
	return ;
}

/* get a mid point of a vector */
void get_mid_point(double *x_1, double *x_2, int length, double *x_mid)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		x_mid[i] = (x_1[i] + x_2[i]) * 0.5 ;
	return ;
}

/* scalar multiply */
void multiply_scalar(double *x, int length, double val)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		x[i] *= val ;
	return ;
}

/* dot product */
double get_dot_product(double *x, double *y, int length)
{
	int i ;
	double sum = 0.0 ;
	for(i = 0 ; i < length ; i++)
		sum += x[i] * y[i] ;
	return sum ;
}

/* distance between two vectors */
double get_vector_distance(double *x, double *y, int length)
{
	int i ;
	double dist = 0.0 ;
	for(i = 0 ; i < length ; i++)
		dist += (x[i] - y[i]) * (x[i] - y[i]) ;
	return sqrt(dist);
}

/* the name says it all */
void vector_subtract(double *x, double *y, int length, double *z)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		z[i] = x[i] - y[i];
	return ;
}

/* the name says it all */
void vector_add(double *x, double *y, int length, double *z)
{
	int i ;
	for(i = 0 ; i < length ; i++)
		z[i] = x[i] + y[i];
	return ;
}

/* prints a vector */
void print_vector(double *x, int length, FILE *fpt)
{
	int i;
	for(i = 0 ; i < length ; i++)
		fprintf(fpt, "%0.2f ", x[i]);
	return ;
}

/* a main to test */
/*#define length 4
int main()
{
	double v1[4] = {1.0, 2.0, 3.0, 4.0};
	double v2[4] = {1.0, 1.0, 1.0, 1.0};
	double v3[4] = {0.0, 0.0, 0.0, 0.0};

	print_vector(v1, length); printf("\n");
	print_vector(v2, length); printf("\n");
	print_vector(v3, length); printf("\n");

	get_unit_vector(v1, length, v3);
	print_vector(v3, length); printf("\n");

	clear_vector(v3, length);
	get_mid_point(v1, v2, length, v3);
	print_vector(v3, length); printf("\n");

	printf("dot product: %0.2f\n", get_dot_product(v1, v2, length));
	printf("distance: %0.2f\n", get_vector_distance(v1, v2, length));

	return 0;
}*/
