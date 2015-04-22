/**
 * Codes for some opposition craps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "global.h"
#include "rand.h"

/*
 * take the current population
 * get the best individual w.r.t. f1: x_1
 * get the best individual w.r.t f2: x_2
 * draw a line between x_1 and x_2
 * get the normal from the mid-point
 * consider the normal as the reference point
 * generate opposite of w.r.t. the reference
 *
 */
/*#define NBEST 10*/
#define debug 0

individual *extreme_indivs ;
int nreal ;
int nobj ;

double generate_opposite_population_using_attractor(population *pop, int popsize, 
					population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize)
{
	int i, j, corrupted_genes = 0  ;
	double *x ;
	double **attractors ;

	attractors = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++)
		attractors[i] = (double*)malloc(sizeof(double) * nreal);
	initialize_attractors(attractors);

	/* gather the opposite_source_pop */
	gather_opposite_source_pop(pop, popsize, opposite_source_pop, opposite_popsize);
	x = (double*)malloc(sizeof(double) * nreal);
	for(i = 0 ; i < opposite_popsize; i++)
	{
		corrupted_genes += generate_attracted_vector(opposite_source_pop->ind[i].xreal, 
								attractors, x);
		memcpy(opposite_pop->ind[i].xreal, x, sizeof(double) * nreal);
	}	
	free(x);
	for(i = 0 ; i < nobj ; i++)
		free(attractors[i]);
	free(attractors);
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

void initialize_attractors(double **t)
{
	/*#ifdef zdt1*/
	int i, j ;
	double zdt1x[2][30] = {{
				0.9993, 0.0000, 0.0000, 0.0002, 0.0000, 
				0.0001, 0.0004, 0.0003, 0.0001, 0.0002, 
				0.0002, 0.0004, 0.0003, 0.0003, 0.0012, 
				0.0004, 0.0007, 0.0003, 0.0001, 0.0010, 
				0.0002, 0.0000, 0.0001, 0.0001, 0.0001, 
				0.0003, 0.0001, 0.0002, 0.0000, 0.0003},
				{
				0.0000, 0.0001, 0.0001, 0.0003, 0.0001, 
				0.0005, 0.0006, 0.0001, 0.0003, 0.0003, 
				0.0001, 0.0007, 0.0016, 0.0003, 0.0009, 
				0.0002, 0.0017, 0.0006, 0.0002, 0.0002, 
				0.0007, 0.0003, 0.0004, 0.0000, 0.0001, 
				0.0001, 0.0003, 0.0000, 0.0001, 0.0003,
				}};

	/*double zdt1x[2][2] = {{0.9993, 0.5000}, {0.0000, 0.5001}};*/

		for(i = 0 ; i < nobj ; i++)
			for(j = 0 ; j < nreal ; j++)
				t[i][j] = zdt1x[i][j] ;
	/*#endif*/
}

int generate_attracted_vector(double *s, double **t, double *d)
{
	double d0, d1 ;
	double *stu, *s_t ;
	individual *ind ;
	int i, j, ccount = 0 ;
	
	ind = (individual*)malloc(sizeof(individual));
	allocate_memory_ind(ind);
	s_t = (double*)malloc(sizeof(double) * nreal);
	stu = (double*)malloc(sizeof(double) * nreal);

	d0 = get_vector_distance(s, t[0], nreal);	
	d1 = get_vector_distance(s, t[1], nreal);

	/*fprintf(stdout, "\nt: ");
	for(i = 0 ; i < nobj ; i++)
		for(j = 0 ; j < nreal ; j++)
			fprintf(stdout, "%f ", t[i][j]);
	fprintf(stdout,"\n");*/
	if(d0 > d1)
	{
		vector_subtract(t[0], s, nreal, s_t);
		get_unit_vector(s_t, nreal, stu);
		multiply_scalar(stu, nreal, rndreal(d0 * 0.75, d0));
		vector_add(s, stu, nreal, d);

		/*fprintf(stdout, "\nd0 > d1 (%f, %f):\n", d0, d1);
		memcpy(ind->xreal, s, sizeof(double) * nreal);
		evaluate_ind(ind);
		fprintf(stdout, "%f,%f: ", ind->obj[0], ind->obj[1]);
		for(i = 0 ; i < nreal ; i++)
			fprintf(stdout, "%f ", ind->xreal[i]);*/

		/*memcpy(ind->xreal, d, sizeof(double) * nreal);
		evaluate_ind(ind);
		fprintf(stdout, "\n%f,%f: ", ind->obj[0], ind->obj[1]);
		for(i = 0 ; i < nreal ; i++)
			fprintf(stdout, "%f ", ind->xreal[i]);*/
		/*vector_subtract(s, stu, nreal, d);*/
	}
	else
	{
		vector_subtract(t[1], s, nreal, s_t);
		get_unit_vector(s_t, nreal, stu);
		multiply_scalar(stu, nreal, rndreal(d1 * 0.75, d1));
		vector_add(s, stu, nreal, d);
		
		/*fprintf(stdout, "\nd0 < d1 (%f, %f):\n", d0, d1);
		memcpy(ind->xreal, s, sizeof(double) * nreal);
		evaluate_ind(ind);
		fprintf(stdout, "%f,%f: ", ind->obj[0], ind->obj[1]);
		for(i = 0 ; i < nreal ; i++)
			fprintf(stdout, "%f ", ind->xreal[i]);
		
		memcpy(ind->xreal, d, sizeof(double) * nreal);
		evaluate_ind(ind);
		fprintf(stdout, "\n%f,%f: ", ind->obj[0], ind->obj[1]);
		for(i = 0 ; i < nreal ; i++)
			fprintf(stdout, "%f ", ind->xreal[i]);*/
		/*vector_subtract(s, stu, nreal, d);*/
	}	
	free(stu);
	free(s_t);
	deallocate_memory_ind(ind);
	free(ind);
	for(i = 0 ; i < nreal ; i++)
	{
		if(isnan(d[i]))
		{
			d[i] = rndreal(min_realvar[i], max_realvar[i]);
			ccount++ ;
		}
		else if(d[i] < min_realvar[i])
		{
			d[i] = min_realvar[i] ;
			ccount++ ; 
		}
		else if(d[i] > max_realvar[i])
		{
			d[i] = max_realvar[i] ;
			ccount++ ;
		}
	}
	return ccount ;
}

void gather_opposite_source_pop(population *pop, int popsize, population 
				*opposite_source_pop, int opposite_popsize)
{
	int i ;
	quicksort_by_rank(pop, popsize);
	for(i = 0 ; i < opposite_popsize; i++)
		indcpy(&pop->ind[rnd(0, opposite_popsize-1)], &opposite_source_pop->ind[i]);
}

double generate_opposite_population_interval_from_archive(population *pop, int popsize, 
					population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize, 
					int div, int gen)
{
	int i, k, corrupted_genes = 0 ;
	double *x1, *x2, *y1, *y2;
	double *x1_x2, *xu, **x2v ;
	double extreme_dist, deltax ;

	if(debug)
	{
		dump_population(pop, popsize, stdout);
		printf("\n");
	}
	
	x1 = (double*)malloc(sizeof(double) * nreal);
	x2 = (double*)malloc(sizeof(double) * nreal);
	x1_x2 = (double*)malloc(sizeof(double) * nreal);
	xu = (double*)malloc(sizeof(double) * nreal);
	if(div == 0 || div < 0)
		div = 1 ;
	else
	{
		/* *---*---*---* */
		x2v = (double**)malloc(sizeof(double*) * div);
		for(k = 0 ; k < div ; k++) 
			x2v[k] = (double*)malloc(sizeof(double) * nreal);
	}
	

	get_bi_extreme_points_archive(x1, x2, pop, popsize, gen);
	/* get_bi_extreme_points_all(x1, x2, pop, popsize); */
	/* get_bi_extreme_points_pareto(x1, x2, pop, popsize); */ /* pareto based extreme is bad */
 	
	extreme_dist = get_vector_distance(x1, x2, nreal);
	deltax = extreme_dist * 1.0/(double)div ;

	for(k = 0 ; k < div ; k++)
	{
		clear_vector(xu, nreal);
		vector_subtract(x2, x1, nreal, x1_x2);
		get_unit_vector(x1_x2, nreal, xu);
		multiply_scalar(xu, nreal, deltax * ((double)k + 1.0));
		clear_vector(x2v[k], nreal);	
		vector_add(x1, xu, nreal, x2v[k]);
	}
	free(xu);
	free(x1_x2);

	if(debug) printf("\nopposite_popsize: %d\n\n", opposite_popsize);

	for(i = 0 ; i < opposite_popsize ; i++)
	{
		y1 = (double*)malloc(nreal * sizeof(double));
		y2 = (double*)malloc(nreal * sizeof(double));
		memcpy(y1, pop->ind[i].xreal, sizeof(double) * nreal);
		indcpy(&(pop->ind[i]), &(opposite_source_pop->ind[i]));
		
		if(debug) printf("---------------------------------- pass: %d\n", i);
		/**
		 * generate opposite of y1, y1 is an arbitrary point.
		 * x1: best point in obj 1
		 * x2: best point in obj 2
		 * y2: opposite of y1
		 */
		generate_opposite_vector(x1, x2v[rnd(0,div-1)], y1, y2);

		/* now inject y2 into the opposite pop*/
		for(k = 0 ; k < nreal ; k++)
		{
			/* precise overshoot correction */
			if(y2[k] < min_realvar[k])
			{	
				opposite_pop->ind[i].xreal[k] = min_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(y2[k] > max_realvar[k])
			{
				opposite_pop->ind[i].xreal[k] = max_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(isnan(y2[k]))
			{
				opposite_pop->ind[i].xreal[k] = 
			       		rndreal(min_realvar[k], max_realvar[k]) ;
				corrupted_genes++ ;
			}
			else
				opposite_pop->ind[i].xreal[k] = y2[k] ;

			/* correct overshoot of the individuals from the other end f2 */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					pop->ind[(popsize-1)-i].xreal[k];
				corrupted_genes++ ;	
			}*/
			
			/* correct overshoot using random re-initialization */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					rndreal (min_realvar[k], max_realvar[k]) ;
				corrupted_genes++;
			}*/

			/* no correction */
			/* opposite_pop->ind[i].xreal[k] = y2[k];*/
		}
		opposite_pop->ind[i].is_opposite = 1;
		if(debug)
		{
			printf("y2[%d]:\n", i);
			evaluate_and_print_vector(y2, nreal, stdout);
			printf("\n");
		} 
		free(y1); free(y2);
	}
	free(x1) ; free(x2) ;
	for(i = 0 ; i < div ; i++) free(x2v[i]);
	free(x2v);
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

double generate_opposite_population_interval(population *pop, int popsize, 
					population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize, 
					int div)
{
	int i, k, corrupted_genes = 0 ;
	double *x1, *x2, *y1, *y2;
	double *x1_x2, *xu, **x2v ;
	double extreme_dist, deltax ;

	if(debug)
	{
		dump_population(pop, popsize, stdout);
		printf("\n");
	}
	
	x1 = (double*)malloc(sizeof(double) * nreal);
	x2 = (double*)malloc(sizeof(double) * nreal);
	x1_x2 = (double*)malloc(sizeof(double) * nreal);
	xu = (double*)malloc(sizeof(double) * nreal);
	if(div == 0 || div < 0)
		div = 1 ;
	else
	{
		/* *---*---*---* */
		x2v = (double**)malloc(sizeof(double*) * div);
		for(k = 0 ; k < div ; k++) 
			x2v[k] = (double*)malloc(sizeof(double) * nreal);
	}
	
	get_bi_extreme_points_all(x1, x2, pop, popsize); 
	/* get_bi_extreme_points_pareto(x1, x2, pop, popsize); */ /* pareto based extreme is bad */
 	
	extreme_dist = get_vector_distance(x1, x2, nreal);
	deltax = extreme_dist * 1.0/(double)div ;

	for(k = 0 ; k < div ; k++)
	{
		clear_vector(xu, nreal);
		vector_subtract(x2, x1, nreal, x1_x2);
		get_unit_vector(x1_x2, nreal, xu);
		multiply_scalar(xu, nreal, deltax * ((double)k + 1.0));
		clear_vector(x2v[k], nreal);	
		vector_add(x1, xu, nreal, x2v[k]);
	}
	free(xu);
	free(x1_x2);

	if(debug) printf("\nopposite_popsize: %d\n\n", opposite_popsize);

	for(i = 0 ; i < opposite_popsize ; i++)
	{
		y1 = (double*)malloc(nreal * sizeof(double));
		y2 = (double*)malloc(nreal * sizeof(double));
		memcpy(y1, pop->ind[i].xreal, sizeof(double) * nreal);
		indcpy(&(pop->ind[i]), &(opposite_source_pop->ind[i]));
		
		if(debug) printf("---------------------------------- pass: %d\n", i);
		/**
		 * generate opposite of y1, y1 is an arbitrary point.
		 * x1: best point in obj 1
		 * x2: best point in obj 2
		 * y2: opposite of y1
		 */
		generate_opposite_vector(x1, x2v[rnd(0,div-1)], y1, y2);

		/* now inject y2 into the opposite pop*/
		for(k = 0 ; k < nreal ; k++)
		{
			/* precise overshoot correction */
			if(y2[k] < min_realvar[k])
			{	
				opposite_pop->ind[i].xreal[k] = min_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(y2[k] > max_realvar[k])
			{
				opposite_pop->ind[i].xreal[k] = max_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(isnan(y2[k]))
			{
				opposite_pop->ind[i].xreal[k] = 
			       		rndreal(min_realvar[k], max_realvar[k]) ;
				corrupted_genes++ ;
			}
			else
				opposite_pop->ind[i].xreal[k] = y2[k] ;

			/* correct overshoot of the individuals from the other end f2 */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					pop->ind[(popsize-1)-i].xreal[k];
				corrupted_genes++ ;	
			}*/
			
			/* correct overshoot using random re-initialization */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					rndreal (min_realvar[k], max_realvar[k]) ;
				corrupted_genes++;
			}*/

			/* no correction */
			/* opposite_pop->ind[i].xreal[k] = y2[k];*/
		}
		opposite_pop->ind[i].is_opposite = 1;
		if(debug)
		{
			printf("y2[%d]:\n", i);
			evaluate_and_print_vector(y2, nreal, stdout);
			printf("\n");
		} 
		free(y1); free(y2);
	}
	free(x1) ; free(x2) ;
	for(i = 0 ; i < div ; i++) free(x2v[i]);
	free(x2v);
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

double generate_opposite_population(population *pop, int popsize, population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize)
{
	int i, k, corrupted_genes = 0 ;
	double *x1, *x2, *y1, *y2;

	if(debug)
	{
		dump_population(pop, popsize, stdout);
		printf("\n");
	}

	x1 = (double*)malloc(sizeof(double) * nreal);
	x2 = (double*)malloc(sizeof(double) * nreal);
	get_bi_extreme_points_all(x1, x2, pop, popsize);
	/* get_bi_extreme_points_pareto(x1, x2, pop, popsize); */
 	
	if(debug) printf("\nopposite_popsize: %d\n\n", opposite_popsize);

	for(i = 0 ; i < opposite_popsize ; i++)
	{
		y1 = (double*)malloc(nreal * sizeof(double));
		y2 = (double*)malloc(nreal * sizeof(double));
		memcpy(y1, pop->ind[i].xreal, sizeof(double) * nreal);
		indcpy(&(pop->ind[i]), &(opposite_source_pop->ind[i]));
		
		if(debug) printf("---------------------------------- pass: %d\n", i);
		
		generate_opposite_vector(x1, x2, y1, y2);

		/* now inject y2 into the opposite pop*/
		for(k = 0 ; k < nreal ; k++)
		{
			/* precise overshoot correction */
			if(y2[k] < min_realvar[k])
			{	
				opposite_pop->ind[i].xreal[k] = min_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(y2[k] > max_realvar[k])
			{
				opposite_pop->ind[i].xreal[k] = max_realvar[k] ;
				corrupted_genes++ ;
			}
			else if(isnan(y2[k]))
			{
				opposite_pop->ind[i].xreal[k] = 
			       		rndreal(min_realvar[k], max_realvar[k]) ;
				corrupted_genes++ ;
			}
			else
				opposite_pop->ind[i].xreal[k] = y2[k] ;

			/* correct overshoot of the individuals from the other end f2 */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					pop->ind[(popsize-1)-i].xreal[k];
				corrupted_genes++ ;	
			}*/
			
			/* correct overshoot using random re-initialization */
			/*if(y2[k] <= max_realvar[k] && y2[k] >= min_realvar[k]) 
				opposite_pop->ind[i].xreal[k] = y2[k];
			else
			{
				opposite_pop->ind[i].xreal[k] = 
					rndreal (min_realvar[k], max_realvar[k]) ;
				corrupted_genes++;
			}*/

			/* no correction */
			/* opposite_pop->ind[i].xreal[k] = y2[k];*/
		}
		opposite_pop->ind[i].is_opposite = 1;
		if(debug)
		{
			printf("y2[%d]:\n", i);
			evaluate_and_print_vector(y2, nreal, stdout);
			printf("\n");
		} 
		free(y1); free(y2);
	}
	free(x1) ; free(x2) ;
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

/** 
 * sort by the 2nd objective first, because 
 * we are trying to map from 1st objective space
 * to the 2nd objective space, assuming that the
 * 2nd objective is hard to optimize.
 */
void get_bi_extreme_points_all(double *x1, double *x2, population *pop, int popsize)
{
	get_best_individual_vector(pop, popsize, 0, x1);		/* O(n) */
	get_best_individual_vector(pop, popsize, 1, x2);		/* O(n) */
	/* quicksort_by_objective(pop, popsize, 0); */			/* O(nlogn) */
	/* memcpy(x1, pop->ind[0].xreal, sizeof(double) * nreal); */	/* O(1) */
									/* O(n + n) */
	return ;
}

/* do the same as before, except get the whole individual instead of just the vector */
void get_bi_extreme_indivs_all(individual *i1, individual *i2, population *pop, int popsize)
{
	get_best_individual(pop, popsize, 0, i1);	/* O(n) */
	get_best_individual(pop, popsize, 1, i2);	/* O(n) */
	/*quicksort_by_objective(pop, popsize, 0);*/	/* O(nlogn) */
	/*indcpy(pop->ind[0], i1);*/			/* O(1) */
							/* O(n + n) */
	return ;
}

/* heuristically update the archive of the extreme points */
void get_bi_extreme_points_archive(double *x1, double *x2, population *pop, int popsize, int gen)
{
	int i, domflag1, domflag2;
	individual *i1, *i2 ;
	i1 = (individual*)malloc(sizeof(individual));
	i2 = (individual*)malloc(sizeof(individual));
	allocate_memory_ind(i1) ;
	allocate_memory_ind(i2) ;
	get_bi_extreme_indivs_all(i1, i2, pop, popsize);
	if(gen == 1)
	{
		extreme_indivs = (individual*)malloc(sizeof(individual) * nobj);
		for(i = 0 ; i < nobj ; i++)
			allocate_memory_ind(&extreme_indivs[i]);
		indcpy(i1, &extreme_indivs[0]);
		indcpy(i2, &extreme_indivs[1]);
		memcpy(x1, extreme_indivs[0].xreal, sizeof(double) * nreal);
		memcpy(x2, extreme_indivs[1].xreal, sizeof(double) * nreal);
	}
	else
	{
		domflag1 = check_dominance(i1, &extreme_indivs[0]);
		domflag2 = check_dominance(i2, &extreme_indivs[1]);

		if((domflag1 == 1) && !(i1->obj[0] < extreme_indivs[0].obj[0]))
			indcpy(i1, &extreme_indivs[0]);
		
		if((domflag2 == 1) && !(i2->obj[1] < extreme_indivs[1].obj[1]))
			indcpy(i2, &extreme_indivs[1]);

		memcpy(x1, extreme_indivs[0].xreal, sizeof(double) * nreal);
		memcpy(x2, extreme_indivs[1].xreal, sizeof(double) * nreal);
	}

	deallocate_memory_ind(i1);
	deallocate_memory_ind(i2);
	free(i1);
	free(i2);
}

/**
 * 1. Get the best individual vector w.r.t obj 0 (extreme f0)	-- O(n)
 * 2. copy it to x1
 * 1. Get the pareto front as a list 				-- O(n)
 * 2. Go through the list and get the best individual on obj 1	-- O(f), f < n
 * 3. copy to x2
 * 6. quicksort the whole population w.r.t obj 0		-- O(nlogn)
 * O(n) + O(n) + O(f) + O(nlogn) ~ O(nlogn)
 */
void get_bi_extreme_points_pareto(double *x1, double *x2, population *pop, int popsize)
{
	int i ;
	individual *best_f1_indp ;
	get_best_individual_vector(pop, popsize, 0, x1);		/* O(n) */

	pop_list *pareto = new_list();
	for(i = 0 ; i < popsize ; i++)
		if(pop->ind[i].rank == 1)
		{
			individual *ind = (individual*)malloc(sizeof(individual));
			allocate_memory_ind(ind);
			indcpy(&(pop->ind[i]), ind);
			push_front(pareto, ind);
		}

	best_f1_indp = pareto->head->ind ;
	node *current = pareto->head->next ;
	while(current != END)
	{
		if(current->ind->obj[1] <= best_f1_indp->obj[1])
			best_f1_indp = current->ind ;
		current = current->next ;
	}
	memcpy(x2, best_f1_indp->xreal, sizeof(double) * nreal);	/* O(1) */
	quicksort_by_objective(pop, popsize, 0);			/* O(nlogn) */
	best_f1_indp = NULL ;
	free_list(pareto);
	return ;
}

/**
 * x1: best point in obj 1
 * x2: best point in obj 2
 * y1: arbitrary point
 * y2: opposite of y1 
 */
void generate_opposite_vector(double *x1, double *x2, double *y1, double *y2)
{
	double *xm, *yu, *x2_y1, *xm_x1;
	
	xm = (double*)malloc(nreal * sizeof(double));
	yu = (double*)malloc(nreal * sizeof(double));
	x2_y1 = (double*)malloc(nreal * sizeof(double));
	xm_x1 = (double*)malloc(nreal * sizeof(double));
	
	/* get mid point x_m = (x_1 + x_2)/2 */	
	get_mid_point(x1, x2, nreal, xm);
	if(debug)
	{
		printf("mid point:\n");
		print_vector(xm, nreal, stdout);
		printf("\n\n");
	}
	/* direction vector x2_y1 = x2 - y1 */
	vector_subtract(x2, y1, nreal, x2_y1);
	if(debug)
	{
		printf("x2-y1:\n");
		print_vector(x2_y1, nreal, stdout);
		printf("\n\n");
	}

	/* direction vector xm_x1 = xm - x1 */
	vector_subtract(xm, x1, nreal, xm_x1);
	if(debug)
	{
		printf("xm-x1:\n");
		print_vector(xm_x1, nreal, stdout);
		printf("\n\n");
	}

	/* unit vector yu = x2_y1 / |x2_y1| */
	get_unit_vector(x2_y1, nreal, yu);
	if(debug)
	{
		printf("unit vector:\n");
		print_vector(yu, nreal, stdout);
		printf("\n\n");
	}

	/**
	 * get opposite vector y2
	 * yu = (xm_x1 . yu)
	 * yu = 2 yu
	 * y2 = yu + y1
	 */
	multiply_scalar(yu, nreal, get_dot_product(xm_x1, yu, nreal));
	multiply_scalar(yu, nreal, 2.0);
	vector_add(yu, y1, nreal, y2);
	
	free(xm_x1);
	free(x2_y1);
	free(yu);
	free(xm);	
	return;
}

/* get the best individual vector in O(n) */
void get_best_individual_vector(population *pop, int popsize, int obj_index, double *best_vec)
{
	int i ;
	individual *best_ind = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if(pop->ind[i].obj[obj_index] <= best_ind->obj[obj_index])
			best_ind = &(pop->ind[i]) ;
	memcpy(best_vec, best_ind->xreal, sizeof(double) * nreal);
	best_ind = NULL ;
}

/* get the best individual vector in O(n) */
void get_best_individual(population *pop, int popsize, int obj_index, individual *best_ind)
{
	int i ;
	individual *temp_best = &(pop->ind[0]) ;
	for (i = 1 ; i < popsize ; i++)
		if(pop->ind[i].obj[obj_index] <= temp_best->obj[obj_index])
			temp_best = &(pop->ind[i]) ;
	indcpy(temp_best, best_ind);
	temp_best = NULL ;
}

/* the next 3 functions are for the quicksort stuffs O(nlogn) */
void quicksort_by_objective(population *pop, int popsize, int obj_index)
{
	quicksort_obj(pop, 0, popsize-1, obj_index);
}

void quicksort_obj(population *pop, int p, int r, int obj_index)
{
	int q ;
	if (p < r)
	{
		q = partition_obj(pop->ind, p, r, obj_index);
		quicksort_obj(pop, p, q-1, obj_index);
		quicksort_obj(pop, q+1, r, obj_index);
	}
}

int partition_obj(individual *ind, int p, int r, int obj_index)
{
	int i, j;
	individual *x = 0, *temp = 0;
	x = (individual*)malloc(sizeof(individual));
	temp = (individual*)malloc(sizeof(individual));

	*x = ind[r];
	i = p - 1 ;
	for(j = p ; j < r ; j++)
	{
		if(ind[j].obj[obj_index] <= x->obj[obj_index])
		{
			i++ ;
			*temp = ind[i];
			ind[i] = ind[j];
			ind[j] = *temp ;
		}
	}
	*temp = ind[i+1] ;
	ind[i+1] = ind[r] ;
	ind[r] = *temp;
	free(temp);
	free(x);
	return i+1 ;
}

/* next 3 functions are for sorting by rank */
void quicksort_by_rank(population *pop, int popsize)
{
	quicksort_rank(pop, 0, popsize-1);
}

void quicksort_rank(population *pop, int p, int r)
{
	int q ;
	if (p < r)
	{
		q = partition_rank(pop->ind, p, r);
		quicksort_rank(pop, p, q-1);
		quicksort_rank(pop, q+1, r);
	}
}

int partition_rank(individual *ind, int p, int r)
{
	int i, j;
	individual *x = 0, *temp = 0;
	x = (individual*)malloc(sizeof(individual));
	temp = (individual*)malloc(sizeof(individual));

	*x = ind[r];
	i = p - 1 ;
	for(j = p ; j < r ; j++)
	{
		if(ind[j].rank <= x->rank)
		{
			i++ ;
			*temp = ind[i];
			ind[i] = ind[j];
			ind[j] = *temp ;
		}
	}
	*temp = ind[i+1] ;
	ind[i+1] = ind[r] ;
	ind[r] = *temp;
	free(temp);
	free(x);
	return i+1 ;
}

/* dumps the population to a file/stdout */
void dump_population (population *pop, int popsize, FILE *fpt)
{
	int i ;
	for (i = 0 ; i < popsize ; i++)
	{
		if(fpt == stdout) {
			fprintf(fpt, "%d: ", i+1);
			dumpf_individual(&(pop->ind[i]), fpt);
		}
		else
			dump_individual(&(pop->ind[i]), fpt);
	}
	return;
}

/* dumps an individual onto file/stdout */
void dumpf_individual(individual *ind, FILE *fpt)
{
	int j, k ;
	for (j = 0 ; j < nobj ; j++)
	{
		if(j == 0)		
			fprintf(fpt,"[%e, ", ind->obj[j]);
		else if (j == nobj-1)
			fprintf(fpt,"%e] ",  ind->obj[j]);
		else
			fprintf(fpt,"%e, ",  ind->obj[j]);
	}
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
		{
			if(j == 0)		
				fprintf(fpt,"[[%e, ",ind->constr[j]);
			else if (j == ncon-1)
				fprintf(fpt,"%e]] ", ind->constr[j]);
			else
				fprintf(fpt,"%e, ",  ind->constr[j]);
		}
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
		{
			if(j == 0)		
				fprintf(fpt,"{%e, ",ind->xreal[j]);
			else if (j == nreal-1)
				fprintf(fpt,"%e} ", ind->xreal[j]);
			else
				fprintf(fpt,"%e, ", ind->xreal[j]);
		}
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
	fprintf(fpt,"[[%e]] ",	ind->constr_violation);
	fprintf(fpt,"<%d> ",	ind->rank);
	fprintf(fpt,"(%e) ",	ind->crowd_dist);
	fprintf(fpt,"|%d|\n",	ind->is_opposite);
}

void dump_individual(individual *ind, FILE *fpt)
{
	int j, k ;
	for (j = 0 ; j < nobj ; j++)		
		fprintf(fpt,"%e\t", ind->obj[j]);
	if (ncon != 0)
		for (j = 0 ; j < ncon ; j++)
			fprintf(fpt,"%e\t",ind->constr[j]);
	if (nreal != 0)
		for (j = 0 ; j < nreal ; j++)
			fprintf(fpt,"%e\t",ind->xreal[j]);
	if (nbin != 0)
		for (j = 0 ; j < nbin ; j++)
		{
			for (k = 0 ; k < nbits[j] ; k++)
				fprintf(fpt,"%d", ind->gene[j][k]);
			fprintf(fpt, "\t");
		}
	fprintf(fpt,"%e\t",	ind->constr_violation);
	fprintf(fpt,"%d\t",	ind->rank);
	fprintf(fpt,"%e\t",	ind->crowd_dist);
	fprintf(fpt,"%d\n",	ind->is_opposite);
}

/* create a dummy individual from a vector, evaluates and prints it */
void evaluate_and_print_vector(double *x, int nreal, FILE *fpt)
{
	individual *ind ;
	ind = (individual*)malloc(sizeof(individual));
	allocate_memory_ind(ind);
	initialize_ind(ind);
	memcpy(ind->xreal, x, sizeof(double) * nreal);
	evaluate_ind(ind);
	dump_individual(ind, fpt);
	deallocate_memory_ind(ind);
	free(ind);
}

/* count the number of opposite individuals in a population */
int count_opposite(population *pop, int popsize)
{
	int i, count ;
	count = 0 ;
	for(i = 0 ; i < popsize ; i++)
		if(pop->ind[i].is_opposite == 1)
			count++;
	return count ;
}

/* clears all the opposite flag of the individuals in a population */
void clear_opposite_flag(population *pop, int popsize)
{
	int i ;
	for(i = 0 ; i < popsize ; i++)
		pop->ind[i].is_opposite = 0 ;
}

/* use system arraycopy (memcpy) for copying an individual */
void indcpy(individual *srcind, individual *destind)
{
	int i ;
	destind->rank = srcind->rank;
	destind->constr_violation = srcind->constr_violation;
	destind->crowd_dist = srcind->crowd_dist;
	if (nreal!=0) memcpy(destind->xreal, srcind->xreal, sizeof(double) * nreal);
	if (nbin!=0)
	{
		memcpy(destind->xbin, srcind->xbin, sizeof(double) * nbin);
		for (i = 0 ; i < nbin ; i++)
			memcpy(&(destind->gene[i]), &(srcind->gene[i]), sizeof(int) * nbits[i]);
	}
	memcpy(destind->obj, srcind->obj, sizeof(double) * nobj) ;
	if (ncon!=0) memcpy(destind->constr, srcind->constr, sizeof(double) * ncon);
	destind->is_opposite = srcind->is_opposite ;
	return;
}

/* use system arraycopy (memcpy) for copying population */
void popcpy(population *srcpop, int srcsize, population *destpop)
{
	int i ;
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[i]));	
}

void inject_opposite(population *srcpop, int srcsize, population *destpop)
{
	int i ;
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[i]));	
}

void inject_opposite_shuffle(population *srcpop, int srcsize, population *destpop, int destpopsize)
{
	int i, *index;
	index = (int*)malloc(sizeof(int) * srcsize);
	for(i = 0 ; i < srcsize ; i++) 
		index[i] = rnd(0, destpopsize-1);
	for(i = 0 ; i < srcsize ; i++)
		indcpy(&(srcpop->ind[i]), &(destpop->ind[index[i]]));
	free(index);	
}

void gather_survived_individuals(population *parent_pop, int popsize, pop_list *survived_pop)
{
	int i ;
	for( i = 0 ; i < popsize ; i++)
	{
		if(parent_pop->ind[i].is_opposite)
		{
			individual *ind = (individual*)malloc(sizeof(individual));
			allocate_memory_ind(ind);
			indcpy(&(parent_pop->ind[i]), ind);
			push_front(survived_pop, ind);
		}
	}
	return ;
}

void dump_population_list(pop_list *survived_pop, FILE *fpt_all_survived)
{
	node *curr ;
	curr = survived_pop->head ;
	while(curr != END)
	{
		if(fpt_all_survived == stdout)
			dumpf_individual(curr->ind, fpt_all_survived);
		else
			dump_individual(curr->ind, fpt_all_survived);
		curr = curr->next ;
	}
	return ;
}


/** some functions that may not be used anymore **/
/* same as above, but takes the popsize */
void evaluate_pop_with_size (population *pop, int poplength)
{
	int i;
	for (i=0; i<poplength; i++)	
		evaluate_ind (&(pop->ind[i]));	
	return;
}

/* same function with an popsize argument */
void initialize_pop_with_size (population *pop, int poplength)
{
	int i;
	for (i = 0 ; i < poplength ; i++)
		initialize_ind (&(pop->ind[i]));
	return;
}

/* Routine to merge two populations into one */
void merge_with_size(population *pop1, int pop1size,	/* 4: 0, 1, 2, 3 */
			population *pop2, int pop2size, /* 3: 0, 1, 2 */
			population *pop3, int pop3size, /* 3: 0, 1, 2 */
			population *pop4, int pop4size) /* 10: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
{
	int i, j ;
	for(i = 0, j = 0 ; i < pop1size ; i++, j++)
		indcpy(&(pop1->ind[i]), &(pop4->ind[j]));
	for(i = 0 ; i < pop2size ; i++, j++)
		indcpy(&(pop2->ind[i]), &(pop4->ind[j]));
	for(i = 0 ; i < pop3size ; i++, j++)
		indcpy(&(pop3->ind[i]), &(pop4->ind[j]));
	return;
}

/* Routine to perform non-dominated sorting */
void fill_nondominated_sort_with_size (population *mixed_pop, int mixed_popsize, 
					population *new_pop, int new_popsize)
{
	int flag;
	int i, j;
	int end;
	int front_size;
	int archieve_size;
	int rank=1;
	list *pool;
	list *elite;
	list *temp1, *temp2;
	pool = (list *)malloc(sizeof(list));
	elite = (list *)malloc(sizeof(list));
	front_size = 0;
	archieve_size=0;
	pool->index = -1;
	pool->parent = NULL;
	pool->child = NULL;
	elite->index = -1;
	elite->parent = NULL;
	elite->child = NULL;
	temp1 = pool;
	for (i = 0; i < mixed_popsize; i++)
	{
		insert (temp1,i);
		temp1 = temp1->child;
	}
	i=0;
	do
	{
		temp1 = pool->child;
		insert (elite, temp1->index);
		front_size = 1;
		temp2 = elite->child;
		temp1 = del (temp1);
		temp1 = temp1->child;
		do
		{
			temp2 = elite->child;
			if (temp1==NULL)
			{
				break;
			}
			do
			{
				end = 0;
				flag = check_dominance (&(mixed_pop->ind[temp1->index]), 
							&(mixed_pop->ind[temp2->index]));
				if (flag == 1)
				{
					insert (pool, temp2->index);
					temp2 = del (temp2);
					front_size--;
					temp2 = temp2->child;
				}
				if (flag == 0)
				{
					temp2 = temp2->child;
				}
				if (flag == -1)
				{
					end = 1;
				}
			}
			while (end!=1 && temp2!=NULL);
			if (flag == 0 || flag == 1)
			{
				insert (elite, temp1->index);
				front_size++;
				temp1 = del (temp1);
			}
			temp1 = temp1->child;
		}
		while (temp1 != NULL);
		temp2 = elite->child;
		j=i;
		if ( (archieve_size+front_size) <= new_popsize)
		{
			do
			{
				copy_ind (&mixed_pop->ind[temp2->index], &new_pop->ind[i]);
				new_pop->ind[i].rank = rank;
				archieve_size+=1;
				temp2 = temp2->child;
				i+=1;
			}
			while (temp2 != NULL);
			assign_crowding_distance_indices (new_pop, j, i-1);
			rank+=1;
		}
		else
		{
			crowding_fill (mixed_pop, new_pop, i, front_size, elite);
			archieve_size = new_popsize;
			for (j = i; j < new_popsize; j++)
			{
				new_pop->ind[j].rank = rank;
			}
		}
		temp2 = elite->child;
		do
		{
			temp2 = del (temp2);
			temp2 = temp2->child;
		}
		while (elite->child !=NULL);
	}
	while (archieve_size < new_popsize);
	while (pool!=NULL)
	{
		temp1 = pool;
		pool = pool->child;
		free (temp1);
	}
	while (elite!=NULL)
	{
		temp1 = elite;
		elite = elite->child;
		free (temp1);
	}
	return;
}

/* Routine to fill a population with individuals in the decreasing order of crowding distance */
void crowding_fill_with_size (population *mixed_pop, int mixed_popsize, 
				population *new_pop, int new_popsize, 
				int count, int front_size, list *elite)
{
	int *dist;
	list *temp;
	int i, j;
	assign_crowding_distance_list (mixed_pop, elite->child, front_size);
	dist = (int *)malloc(front_size*sizeof(int));
	temp = elite->child;
	for (j=0; j<front_size; j++)
	{
		dist[j] = temp->index;
		temp = temp->child;
	}
	quicksort_dist (mixed_pop, dist, front_size);
	for (i=count, j=front_size-1; i<new_popsize; i++, j--)
	{
		copy_ind(&mixed_pop->ind[dist[j]], &new_pop->ind[i]);
	}
	free (dist);
	return;
}

void inject_spread(population *child_pop, int popsize)
{
	int len ;
	int *index = malloc(sizeof(int) * popsize);
	for(int i = 0 ; i < popsize ; i++)
		index[i] = i ;
	for(int i = 0 ; i < popsize ; i++)
		index[i] = index[rnd(0,popsize-1)];

	len = (int)(popsize * 0.1) ;
	for(int i = 0 ; i <  len ; i++)
	{
		for(int j = 1 ; j < nreal ; j++)
			child_pop->ind[index[i]].xreal[j] = 
				rndreal (min_realvar[j], max_realvar[j]);
	}
}

