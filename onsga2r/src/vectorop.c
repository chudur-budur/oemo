/**
 * Vector operations code
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

double get_determinant(double **matrix, int n)
{
	int i,j,j1,j2 ;		   // general loop and matrix subscripts
	double det = 0 ;	   // init determinant
	double **m = NULL ;	   // pointer to pointers to implement 2d
	if (n < 1)
	{
		fprintf(stderr, "error: get_determinant() n < 1 !!");
		exit(1);
	}
	else if (n == 1)
		det = matrix[0][0] ;
	else if (n == 2)               
		det = matrix[0][0] * matrix[1][1] 
			- matrix[1][0] * matrix[0][1] ;
	// recursion continues, solve next sub-matrix
	// solve the next minor by building a
	else                               
	{
		// sub matrix
		// initialize determinant of sub-matrix
		det = 0 ;                      
		// for each column in sub-matrix
		for (j1 = 0 ; j1 < n ; j1++)
		{
			// get space for the pointer list
			m = (double **) malloc((n-1)* sizeof(double *)) ;
			for (i = 0 ; i < n-1 ; i++)
				m[i] = (double *) malloc((n-1)* sizeof(double)) ;
			//     i[0][1][2][3]  first malloc
			//  m -> +  +  +  +   space for 4 pointers
			//       |  |  |  |          j  second malloc
			//       |  |  |  +-> _ _ _ [0] pointers to
			//       |  |  +----> _ _ _ [1] and memory for
			//       |  +-------> _ a _ [2] 4 doubles
			//       +----------> _ _ _ [3]
			//
			//                   a[1][2]
			// build sub-matrix with minor elements excluded
			for (i = 1 ; i < n ; i++)
			{
				// start at first sum-matrix column position
				j2 = 0 ;               
				// loop to copy source matrix less one column
				for (j = 0 ; j < n ; j++)
				{
					// don't copy the minor column element
					if (j == j1) continue ;
					// copy source element into new sub-matrix
					m[i-1][j2] = matrix[i][j] ;  
					// i-1 because new sub-matrix is one row
					// (and column) smaller with excluded minors
					// move to next sub-matrix column position
					j2++ ;                  
				}
			}
			det += pow(-1.0,1.0 + j1 + 1.0) * matrix[0][j1] * get_determinant(m,n-1) ;
			// sum x raised to y power
			// recursively get determinant of next
			// sub-matrix which is now one
			// row & column smaller
			for (i = 0 ; i < n-1 ; i++) free(m[i]) ;
			free(m) ;
		}
	}
	return det ;
}

/* prints a vector */
void print_vector(double *x, int length, FILE *fpt)
{
	int i;
	for(i = 0 ; i < length ; i++)
		fprintf(fpt, "%0.4f ", x[i]);
	return ;
}

/* a main to test */
/* #define length 4
int main()
{
	int i, j;
	double v1[4] = {1.0, 2.0, 3.0, 4.0};
	double v2[4] = {1.0, 1.0, 1.0, 1.0};
	double v3[4] = {0.0, 0.0, 0.0, 0.0};
	double v4[3][3] = {{6, 1, 1}, {4, -2, 5}, {2, 8, 7}};
	double **m ;
	m = (double**)malloc(sizeof(double*) * 3);
	for(i = 0 ; i < 3 ; i++)
	{
		m[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0 ; j < 3 ; j++)
			m[i][j] = v4[i][j] ;
	}

	print_vector(v1, length, stdout); fprintf(stdout, "\n");
	print_vector(v2, length, stdout); fprintf(stdout, "\n");
	print_vector(v3, length, stdout); fprintf(stdout, "\n");

	get_unit_vector(v1, length, v3);
	print_vector(v3, length, stdout); fprintf(stdout, "\n");

	clear_vector(v3, length);
	get_mid_point(v1, v2, length, v3);
	print_vector(v3, length, stdout); printf("\n");

	fprintf(stdout, "dot product: %0.2f\n", get_dot_product(v1, v2, length));
	fprintf(stdout, "distance: %0.2f\n", get_vector_distance(v1, v2, length));
	fprintf(stdout, "determinant: %0.2f\n", get_determinant(m, 3));

	return 0;
}*/
