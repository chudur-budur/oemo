/**
 * Codes for some opposition craps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "global.h"
#include "rand.h"

#define debug 0

/* #define zdt1 */
/* #define zdt2 */
/* #define zdt3 */
/* #define zdt4 */
 #define zdt6
/* #define pol */
/* #define osy */

/* #define dtlz1 */
/* #define dtlz2 */
/* #define dtlz3 */
/* #define dtlz4 */
/* #define dtlz5 */
/* #define dtlz6 */
/* #define dtlz7 */

#ifdef zdt1
	double e_star[2][30] = {{
			9.992492e-01, 2.327980e-04, 1.345857e-04, 1.358861e-05, 1.956658e-04, 
			7.563202e-05, 6.145617e-06, 3.252514e-04, 1.490042e-04, 5.651175e-04,
			3.827200e-05, 2.428821e-04, 4.078095e-04, 3.745609e-04, 3.341747e-04,
			6.851307e-05, 4.936276e-05, 1.506193e-03, 7.898634e-04, 1.028294e-04,
			1.160133e-04, 9.793699e-05, 1.384222e-05, 2.727065e-04, 9.804717e-06,
			5.509704e-04, 6.057900e-04, 5.323575e-05, 3.321190e-04, 3.827791e-04},
			{
			7.333534e-08, 6.813504e-04, 2.151707e-04, 3.381928e-04, 1.750262e-03, 
			2.220822e-04, 2.171309e-05, 7.171244e-04, 1.203925e-03, 4.141504e-04,
			2.672924e-04, 6.309293e-04, 1.248312e-04, 1.156844e-03, 2.687615e-04,
			8.212292e-04, 6.019056e-04, 8.462657e-04, 3.272088e-05, 9.648083e-04,
			3.227733e-05, 8.223722e-04, 1.365859e-03, 2.357370e-04, 1.958483e-04,
			7.904188e-04, 3.570866e-05, 5.238472e-04, 1.691631e-04, 1.414751e-03}
			};
#endif

#ifdef zdt2
	double e_star[2][30] = {{
			9.999117e-01, 1.357128e-03, 2.190893e-04, 3.472831e-04, 5.518381e-04, 
			9.621146e-05, 1.404635e-04, 1.267040e-04, 2.866037e-04, 1.214981e-04,
			8.478345e-05, 8.483969e-05, 1.076381e-04, 2.421979e-04, 2.240639e-05,
			2.757290e-05, 2.195108e-04, 6.428559e-05, 2.500776e-05, 6.826129e-04,
			5.119989e-04, 9.880269e-05, 4.305283e-04, 7.344245e-05, 4.183553e-05,
			3.397567e-04, 8.310119e-04, 4.409582e-04, 8.871618e-05, 1.070245e-05},
			{
			2.239256e-12, 3.626408e-05, 8.705896e-05, 3.191323e-04, 4.660397e-04, 
			1.018963e-04, 8.750589e-04, 7.125756e-04, 2.739404e-04, 9.543259e-05,
			1.134457e-04, 1.198473e-04, 4.746592e-04, 7.174455e-04, 4.018896e-04,
			2.241113e-04, 4.880848e-04, 1.124217e-04, 2.599218e-05, 7.237181e-04,
			4.102724e-04, 1.337159e-05, 3.839438e-04, 1.428445e-04, 1.047508e-04,
			3.735666e-04, 1.308571e-03, 2.485873e-04, 8.701451e-05, 9.363877e-05}
			};
#endif

#ifdef zdt3
	double e_star[2][30] = {{
			8.516830e-01, 5.809745e-04, 3.945575e-06, 1.319513e-04, 8.557168e-04, 
			2.973133e-04, 6.476476e-04, 2.493152e-04, 7.252119e-04, 2.924352e-03,
			3.770534e-04, 1.165612e-03, 3.186198e-04, 2.156870e-04, 7.869838e-04,
			1.256553e-03, 1.992499e-03, 2.493609e-04, 6.703100e-04, 3.580130e-04,
			4.398291e-04, 1.104766e-04, 1.473257e-04, 9.343540e-04, 7.474311e-05,
			1.065195e-03, 3.138475e-04, 6.004780e-04, 6.252331e-04, 3.619383e-04},
	       		{
			1.664504e-08, 8.430653e-04, 2.911235e-04, 3.674899e-04, 9.003495e-04, 
			1.568993e-04, 7.114079e-04, 2.551109e-04, 1.582047e-04, 2.161640e-03,
			2.955146e-04, 1.206236e-03, 3.776277e-04, 1.833342e-04, 4.137815e-04,
			1.957801e-04, 1.789657e-04, 1.615388e-04, 1.121109e-03, 6.768148e-04,
			1.241929e-04, 1.038961e-05, 1.387445e-05, 7.199262e-04, 2.786778e-04,
			2.971143e-04, 3.810230e-04, 1.533421e-04, 5.622700e-06, 3.645322e-04}
			};
#endif

#ifdef zdt4
	double e_star[2][10] = {{
			9.999769e-01, 2.993182e-04, -7.067956e-04, 3.850841e-04, 7.606947e-04,	
			1.435050e-03, -7.191367e-05, 2.906952e-03, -8.182666e-04, -4.415261e-04},
	       		{
			1.485687e-17, 9.199880e-05, -4.616606e-04, -2.961500e-04, 7.312215e-04,	
			1.509527e-03, -8.123022e-06, 4.439154e-03, -8.102794e-04, -2.717245e-04}
			};
#endif

#ifdef zdt6
	double e_star[2][10] = {{
			8.145779e-02, 1.534988e-11, 4.387386e-12, 5.707769e-11, 8.918706e-13,	
			7.957061e-12, 2.372546e-11, 1.542414e-10, 2.381327e-11, 1.991800e-11},
	       		{
			1.679339e-01, 1.871541e-11, 3.476851e-13, 1.249846e-11, 1.012897e-11,	
			2.338439e-11, 1.512753e-11, 2.753128e-12, 1.182686e-11, 1.622554e-11}
			};
#endif

#ifdef pol
	double e_star[2][2] = {{-3.001868e+00,	-9.991395e-01},
       				{1.000358e+00,	1.990154e+00}};	
#endif

#ifdef osy
	double e_star[2][12] = {{
		1.999642e+00, 1.193523e-04, 2.999553e+00, 5.349871e-04,	
		2.026485e-04, 3.705805e-02, 4.999195e+00, 1.000088e+00,	
		4.999796e+00, 6.093375e-06, 4.999761e+00, 1.491880e-01},
	        {
		1.710494e-03, 6.660965e-01, 9.818987e-01, 2.037913e+00, 	
		1.397197e-04, 5.956091e-03, 9.836092e-01, 1.019812e+00, 	
		1.000158e+00, 7.195912e-05, 1.000010e+00, 2.386555e-02}
		};
#endif

#ifdef dtlz1
	double e_star[3][7] = {
	{1.518001e-10, 4.416157e-07, 5.000093e-01, 5.001138e-01, 5.000324e-01, 5.000372e-01, 5.000360e-01},
	{1.000000e+00, 1.528660e-01, 5.000343e-01, 5.001009e-01, 4.999997e-01, 5.000091e-01, 5.001080e-01},
	{4.641804e-12, 1.000000e+00, 5.000146e-01, 5.001410e-01, 5.000250e-01, 5.000207e-01, 5.000422e-01}};
#endif

#ifdef dtlz2
	double e_star[3][12] = {{
			9.999999e-01, 2.068654e-02, 4.210980e-01, 4.943366e-01,	
			4.945734e-01, 4.954986e-01, 5.266967e-01, 5.019754e-01,	
			5.042300e-01, 4.984148e-01, 5.017677e-01, 4.975327e-01},
			{
			2.575339e-06, 5.241525e-01, 5.097762e-01, 5.092035e-01,
			4.971620e-01, 4.915429e-01, 5.016564e-01, 5.121870e-01,	
			5.029136e-01, 4.957531e-01, 4.986117e-01, 4.934615e-01},
			{
			9.999999e-01, 9.999918e-01, 5.038060e-01, 5.144292e-01,	
			4.913250e-01, 4.946533e-01, 4.982629e-01, 4.878274e-01,	
			4.972269e-01, 4.976784e-01, 4.951525e-01, 4.972794e-01}
			};
#endif

#ifdef dtlz3
	double e_star[3][12] = {{
			1.000000e+00, 3.015651e-17, 5.000008e-01, 5.000926e-01,	
			5.000270e-01, 5.000088e-01, 4.999538e-01, 4.999871e-01,	
			4.999301e-01, 5.000281e-01, 5.000003e-01, 5.000287e-01},
			{
			1.000000e+00, 1.000000e+00, 5.000115e-01, 5.000805e-01,	
			5.000196e-01, 4.999977e-01, 4.999412e-01, 4.999881e-01,	
			4.999653e-01, 5.000662e-01, 5.000006e-01, 5.000255e-01},
			{
			1.603818e-17, 2.507028e-01, 5.000127e-01, 5.000749e-01,	
			5.000210e-01, 4.999960e-01, 4.999553e-01, 5.000067e-01,	
			4.999978e-01, 5.000153e-01, 4.999992e-01, 5.000390e-01}
			};
#endif

#ifdef dtlz4
	double e_star[3][12] = {{
			9.999999e-01, 9.999936e-01, 4.951966e-01, 5.064815e-01,	
			4.924490e-01, 4.995276e-01, 4.979789e-01, 5.009201e-01,	
			4.996556e-01, 5.046379e-01, 4.941011e-01, 5.042929e-01},
			{
			9.938179e-01, 4.311857e-06, 4.967517e-01, 5.059470e-01,	
			4.920211e-01, 4.946013e-01, 4.937855e-01, 5.064931e-01,	
			5.034025e-01, 5.012390e-01, 5.038550e-01, 5.013487e-01},
			{
			3.109724e-05, 9.864765e-01, 4.925116e-01, 5.056041e-01,	
			5.061607e-01, 5.022251e-01, 5.066173e-01, 4.994877e-01,	
			4.962075e-01, 5.206323e-01, 5.042736e-01, 4.955822e-01}
			};
#endif

#ifdef dtlz5
	double e_star[3][12] = {{
			2.019607e-05, 4.691999e-03, 4.998126e-01, 4.998191e-01,	
			4.997985e-01, 5.004007e-01, 5.004654e-01, 4.985565e-01,	
			5.007254e-01, 5.006066e-01, 5.003787e-01, 5.009204e-01},
			{
			9.999995e-01, 5.958631e-02, 4.995468e-01, 4.998111e-01,
			4.998534e-01, 5.003983e-01, 5.004524e-01, 4.985724e-01,	
			5.003780e-01, 5.014114e-01, 5.005870e-01, 4.997269e-01},
			{
			9.999995e-01, 3.426279e-03, 4.995468e-01, 4.998111e-01,	
			4.998614e-01, 5.003983e-01, 5.004646e-01, 4.985644e-01,	
			5.003780e-01, 5.014114e-01, 4.991804e-01, 4.996749e-01}
			};
#endif

#ifdef dtlz6
	double e_star[3][12] = {{
			1.000000e+00, 9.974290e-01, 1.524748e-16, 0.000000e+00,	
			0.000000e+00, 4.040056e-16, 0.000000e+00, 6.684228e-18,	
			1.065101e-16, 9.675644e-16, 1.030307e-16, 2.002856e-16},
			{
			1.000000e+00, 5.476236e-03, 4.145254e-17, 0.000000e+00,	
			0.000000e+00, 4.040056e-16, 0.000000e+00, 6.684228e-18,	
			0.000000e+00, 9.675644e-16, 2.140530e-16, 2.002856e-16},
			{
			1.783298e-14, 1.947983e-01, 1.611822e-17, 1.287583e-16,	
			2.546368e-16, 2.507170e-18, 6.422436e-16, 2.649740e-17,	
			3.026288e-17, 0.000000e+00, 0.000000e+00, 0.000000e+00}
			};
#endif

#ifdef dtlz7
	double e_star[3][22] = {{
			1.284353e-01, 2.189343e-16, 2.930163e-05, 4.354765e-05, 1.820315e-05, 
			3.752028e-05, 2.406706e-05, 3.900316e-05, 1.802562e-05, 3.204943e-05,
			7.783208e-05, 4.226695e-05, 1.004431e-04, 1.393878e-04, 1.947388e-04,
			1.946992e-05, 1.630548e-05, 1.691152e-04, 2.285285e-04, 2.871427e-07,
			1.340409e-04, 1.724859e-05},
			{
			8.561563e-01, 8.603832e-01, 1.070907e-04, 7.042681e-06, 8.530980e-06,  
			3.459961e-05, 1.128565e-04, 2.467800e-04, 3.266559e-05, 3.182198e-05, 
			7.753045e-06, 1.895454e-04, 1.014680e-04, 1.100796e-06, 2.734151e-05, 
			1.011304e-05, 1.642499e-05, 2.949661e-05, 2.803044e-05, 1.428371e-06, 
			1.712368e-06, 4.230554e-06},
			{
			1.734470e-10, 1.625798e-01, 1.846982e-05, 1.720799e-04, 1.095058e-04, 
			2.736409e-04, 6.024500e-05, 1.357000e-04, 2.846853e-02, 6.946536e-05,
			9.281912e-05, 1.324629e-05, 7.452940e-05, 2.288953e-04, 1.966254e-04,
			9.450860e-06, 2.335544e-05, 9.642324e-05, 2.035835e-06, 1.157488e-04,
			1.221824e-04, 7.156969e-05}
			};
#endif



double generate_opposite_population_using_attractor(population *pop, int popsize, 
					population *opposite_source_pop, 
					population *opposite_pop, int opposite_popsize,
					int gen)
{
	int i, corrupted_genes = 0  ;
	double *x, *t ;

	t = (double*)malloc(sizeof(double) * nreal);

	gather_opposite_source_pop(pop, popsize, opposite_source_pop, opposite_popsize);
	x = (double*)malloc(sizeof(double) * nreal);
	for(i = 0 ; i < opposite_popsize; i++)
	{
		// get_target_scheme1(pop, popsize, opposite_source_pop->ind[i].xreal, t);
		// get_target_scheme2(pop, popsize, opposite_source_pop->ind[i].xreal, t, gen);
		get_target_scheme3(pop, popsize, opposite_source_pop->ind[i].xreal, t);
		corrupted_genes += generate_opposite_vector_q3(opposite_source_pop->ind[i].xreal, t, x);
		memcpy(opposite_pop->ind[i].xreal, x, sizeof(double) * nreal);
		opposite_pop->ind[i].is_opposite = 1 ;
	}	
	free(x);
	free(t);
	return corrupted_genes/((double)(opposite_popsize * nreal)) * 100.0 ;
}

void get_target_scheme3(population *pop, int popsize, double *s, double *t)
{
	int i ;
	double **e ;
	int *idx ;
	int max_index ;
	double dist, max_dist ;
	
	e = (double**)malloc(sizeof(double*) * 2 * nobj);
	for(i = 0 ; i < 2 * nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);


	int no_extreme(individual *ind);
	get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	for(i = 0 ; i < nobj ; i++)
		memcpy(e[i + nobj], e_star[i], sizeof(double) * nreal);
	
	idx = (int*)malloc(sizeof(int) * 2 * nobj);
	get_random_indices(idx, 2 * nobj);
	
	max_dist = get_vector_distance(s, e[idx[0]], nreal);
	max_index = idx[0] ;
	for(i = 1 ; i < nobj ; i++)
	{
		dist = get_vector_distance(s, e[idx[i]], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = idx[i] ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	free(idx);

	for(i = 0 ; i < 2 * nobj ; i++)
		free(e[i]);
	free(e);
}

void get_target_scheme2(population *pop, int popsize, double *s, double *t, int gen)
{
	int i;
	double **e ;
	double dist, max_dist ;
	int max_index ;

	e = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);

	if(gen <= 10)
	{
		for(i = 0 ; i < nobj ; i++)
			memcpy(e[i], e_star[i], sizeof(double) * nreal);
	}
	else
	{
		int no_extreme(individual *ind);
		get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	}
	
	max_dist = get_vector_distance(s, e[0], nreal);
	max_index = 0 ;
	for(i = 1 ; i < nobj ; i++)
	{
		dist = get_vector_distance(s, e[i], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = i ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	
	for(i = 0 ; i < nobj ; i++)
		free(e[i]);
	free(e);
}

void get_target_scheme1(population *pop, int popsize, double *s, double *t)
{
	int i ;
	double **e ;
	double dist, max_dist ;
	int max_index ;

	e = (double**)malloc(sizeof(double*) * 2 * nobj);
	for(i = 0 ; i < 2 * nobj ; i++)
		e[i] = (double*)malloc(sizeof(double) * nreal);

	int no_extreme(individual *ind);
	get_extreme_vectors(pop, popsize, e, nobj, no_extreme);
	for(i = 0 ; i < nobj ; i++)
		memcpy(e[i + nobj], e_star[i], sizeof(double) * nreal);

	max_dist = get_vector_distance(s, e[0], nreal);
	max_index = 0 ;
	for(i = 1 ; i < 2 * nobj ; i++)
	{
		dist = get_vector_distance(s, e[i], nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_index = i ;
		}
	}
	
	memcpy(t, e[max_index], sizeof(double) * nreal);
	
	for(i = 0 ; i < 2 * nobj ; i++)
		free(e[i]);
	free(e);
}

int no_extreme(individual *ind)
{
	if(ind->crowd_dist < INF) return 1 ;
	else return 0 ;
}

int generate_opposite_vector_q3(double *s, double *t, double *d)
{
	double *stu, *s_t, dist ;
	int i, ccount = 0 ;

	s_t = (double*)malloc(sizeof(double) * nreal);
	stu = (double*)malloc(sizeof(double) * nreal);

	dist = get_vector_distance(s, t, nreal);
	vector_subtract(t, s, nreal, s_t);
	get_unit_vector(s_t, nreal, stu);
	multiply_scalar(stu, nreal, rndreal(dist * 0.75, dist));
	vector_add(s, stu, nreal, d);
	
	free(stu);
	free(s_t);
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

void get_extreme_vectors(population *pop, int popsize, double **vec, int v_size, 
						int (*chooser)(individual *ind))
{
	int i ;
	pop_list *lst = new_list();
	for( i = 0 ; i < popsize ; i++)
		push_back(lst, &(pop->ind[i]));
	for(i = 0 ; i < v_size ; i++)
	{
		node* ptr = get_extreme_node(lst, chooser);
		memcpy(vec[i], ptr->ind->xreal, sizeof(double) * nreal);
		erase(lst, ptr);
	}
	free_list(lst);
}

node* get_extreme_node(pop_list *lst, int (*chooser)(individual *ind))
{
	double max_dist = -1.0 ;
	node *curr = lst->head;
        node *ptr = lst->head ;	
	while(curr != END)
	{
		if(curr->ind->crowd_dist >= max_dist && (*chooser)(curr->ind))
		{
			max_dist = curr->ind->crowd_dist ;
			ptr = curr ;
		}
		curr = curr->next ;
	}
	return ptr ;
}

void gather_opposite_source_pop(population *pop, int popsize, population 
				*opposite_source_pop, int opposite_popsize)
{
	int i ;
	int rank_compare(individual *i1, individual *i2);
	quicksort_(pop, popsize, rank_compare);
	for(i = 0 ; i < opposite_popsize; i++)
		indcpy(&pop->ind[rnd(0, opposite_popsize-1)], &opposite_source_pop->ind[i]);
}

int rank_compare(individual *i1, individual *i2)
{
	if(i1->rank <= i2->rank) return 1;
	else return 0 ;
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
			push_back(survived_pop, &(parent_pop->ind[i]));
	}
	return ;
}