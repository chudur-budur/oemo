/**
 * Codes for some opposition craps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rand.h"
#include "global.h"
#include "problemdef.h"
#include "opposition.h"
#include "poplist.h"
#include "sosolver.h"
#include "misc.h"
#include "vecutils.h"

#define debug 0
#define showmap 0

pop_list *e_star ;
int popsize ;
int op_popsize ;
char prob_name[16] ;

int init_extreme_pts_hardcoded(void)
{
	double **extremes ;
	int feval = 0, i;
	/* e_star = new_list(); */
	individual ind ;
	extremes = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++) extremes[i] = (double*)malloc(sizeof(double) * nreal);
	
	if(strcmp(prob_name, "zdt1") == 0)
	{
		double zdt1_extremes[2][30] = {{
			9.992492e-01, 2.327980e-04, 1.345857e-04, 1.358861e-05, 1.956658e-04,
			7.563202e-05, 6.145617e-06, 3.252514e-04, 1.490042e-04, 5.651175e-04,
			3.827200e-05, 2.428821e-04, 4.078095e-04, 3.745609e-04, 3.341747e-04,
			6.851307e-05, 4.936276e-05, 1.506193e-03, 7.898634e-04, 1.028294e-04,
			1.160133e-04, 9.793699e-05, 1.384222e-05, 2.727065e-04, 9.804717e-06,
			5.509704e-04, 6.057900e-04, 5.323575e-05, 3.321190e-04, 3.827791e-04
		},
		{
			7.333534e-08, 6.813504e-05, 2.151707e-05, 3.381928e-04, 1.750262e-03,
			2.220822e-04, 2.171309e-05, 7.171244e-04, 1.203925e-03, 4.141504e-04,
			2.672924e-04, 6.309293e-04, 1.248312e-04, 1.156844e-03, 2.687615e-04,
			8.212292e-04, 6.019056e-04, 8.462657e-04, 3.272088e-05, 9.648083e-04,
			3.227733e-05, 8.223722e-04, 1.365859e-03, 2.357370e-04, 1.958483e-04,
			7.904188e-04, 3.570866e-05, 5.238472e-04, 1.691631e-04, 1.414751e-03
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt1_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "zdt2") == 0)
	{
		double zdt2_extremes[2][30] = {{
			9.999117e-01, 1.357128e-03, 2.190893e-04, 3.472831e-04, 5.518381e-04,
			9.621146e-05, 1.404635e-04, 1.267040e-04, 2.866037e-04, 1.214981e-04,
			8.478345e-05, 8.483969e-05, 1.076381e-04, 2.421979e-04, 2.240639e-05,
			2.757290e-05, 2.195108e-04, 6.428559e-05, 2.500776e-05, 6.826129e-04,
			5.119989e-04, 9.880269e-05, 4.305283e-04, 7.344245e-05, 4.183553e-05,
			3.397567e-04, 8.310119e-04, 4.409582e-04, 8.871618e-05, 1.070245e-05
		},
		{
			2.239256e-12, 3.626408e-05, 8.705896e-05, 3.191323e-04, 4.660397e-04,
			1.018963e-04, 8.750589e-04, 7.125756e-04, 2.739404e-04, 9.543259e-05,
			1.134457e-04, 1.198473e-04, 4.746592e-04, 7.174455e-04, 4.018896e-04,
			2.241113e-04, 4.880848e-04, 1.124217e-04, 2.599218e-05, 7.237181e-04,
			4.102724e-04, 1.337159e-05, 3.839438e-04, 1.428445e-04, 1.047508e-04,
			3.735666e-04, 1.308571e-03, 2.485873e-04, 8.701451e-05, 9.363877e-05
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt2_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "zdt3") == 0)
	{
		double zdt3_extremes[2][30] = {{
			8.516830e-01, 5.809745e-04, 3.945575e-06, 1.319513e-04, 8.557168e-04,
			2.973133e-04, 6.476476e-04, 2.493152e-04, 7.252119e-04, 2.924352e-03,
			3.770534e-04, 1.165612e-03, 3.186198e-04, 2.156870e-04, 7.869838e-04,
			1.256553e-03, 1.992499e-03, 2.493609e-04, 6.703100e-04, 3.580130e-04,
			4.398291e-04, 1.104766e-04, 1.473257e-04, 9.343540e-04, 7.474311e-05,
			1.065195e-03, 3.138475e-04, 6.004780e-04, 6.252331e-04, 3.619383e-04
		},
		{
			1.664504e-08, 8.430653e-04, 2.911235e-04, 3.674899e-04, 9.003495e-04,
			1.568993e-04, 7.114079e-04, 2.551109e-04, 1.582047e-04, 2.161640e-03,
			2.955146e-04, 1.206236e-03, 3.776277e-04, 1.833342e-04, 4.137815e-04,
			1.957801e-04, 1.789657e-04, 1.615388e-04, 1.121109e-03, 6.768148e-04,
			1.241929e-04, 1.038961e-05, 1.387445e-05, 7.199262e-04, 2.786778e-04,
			2.971143e-04, 3.810230e-04, 1.533421e-04, 5.622700e-06, 3.645322e-04
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt3_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "zdt4") == 0)
	{
		double zdt4_extremes[2][10] = {{
			1.000,	-0.001,	-0.001,	0.000,	0.000,	-0.001,	0.002,	-0.001,	-0.001,	-0.001
		},
		{
			0.000,	-0.004,	0.000,	0.000,	0.001,	-0.001,	0.000,	-0.000,	-0.002,	-0.001
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt4_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "zdt6") == 0)
	{
		double zdt6_extremes[2][10] = {{
			8.145779e-02, 1.534988e-11, 4.387386e-12, 5.707769e-11, 8.918706e-13,
			7.957061e-12, 2.372546e-11, 1.542414e-10, 2.381327e-11, 1.991800e-11
		},
		{
			1.679339e-01, 1.871541e-11, 3.476851e-13, 1.249846e-11, 1.012897e-11,
			2.338439e-11, 1.512753e-11, 2.753128e-12, 1.182686e-11, 1.622554e-11
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt6_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "pol") == 0)
	{
		double pol_extremes[2][2] = {{
			-3.001868e+00, -9.991395e-01
		},
		{
			1.000358e+00,	1.990154e+00
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &pol_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "osy") == 0)
	{
		double osy_extremes[2][6] = {{
			4.999195e+00, 1.000088e+00, 4.999796e+00, 
			6.093375e-06, 4.999761e+00, 1.491880e-01
		},
		{
			9.836092e-01, 1.019812e+00, 1.000158e+00, 
			7.195912e-05, 1.000010e+00, 2.386555e-02
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &osy_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz1") == 0)
	{
		double dtlz1_extremes[3][12] = {{
			0.979,	1.000,	0.637,	0.977,	0.235,	0.171,	
			0.502,	0.580,	0.394,	0.758,	0.730,	0.462
		},
		{
			1.000,	0.000,	0.486,	0.498,	0.499,	0.500,	
			0.554,	0.596,	0.518,	0.384,	0.497,	0.334
		},
		{
			0.000,	0.000,	0.500,	0.491,	0.391,	0.500,	
			0.500,	0.491,	0.500,	0.500,	0.610,	0.610
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz1_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz2") == 0)
	{
		double dtlz2_extremes[3][12] = {{
			9.999693e-01, 1.344506e-04, 5.117398e-01, 4.964069e-01,
			4.968327e-01, 4.964390e-01, 5.027085e-01, 4.977617e-01,
			4.904257e-01, 4.999348e-01, 4.943774e-01, 5.035261e-01
		},
		{
			9.681968e-07, 6.327744e-01, 5.032704e-01, 5.045669e-01,
			5.043110e-01, 5.059398e-01, 4.997366e-01, 4.967710e-01,
			5.022653e-01, 5.023801e-01, 5.032009e-01, 4.979508e-01
		},
		{
			9.999562e-01, 9.999980e-01, 5.001320e-01, 4.966535e-01,
			4.991596e-01, 5.083829e-01, 5.017878e-01, 4.952228e-01,
			5.045672e-01, 5.017501e-01, 5.060027e-01, 5.000449e-01
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz2_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz3") == 0)
	{
		double dtlz3_extremes[3][12] = {{
			1.000000e+00, 3.015651e-17, 5.000008e-01, 5.000926e-01,
			5.000270e-01, 5.000088e-01, 4.999538e-01, 4.999871e-01,
			4.999301e-01, 5.000281e-01, 5.000003e-01, 5.000287e-01
		},
		{
			1.000000e+00, 1.000000e+00, 5.000115e-01, 5.000805e-01,
			5.000196e-01, 4.999977e-01, 4.999412e-01, 4.999881e-01,
			4.999653e-01, 5.000662e-01, 5.000006e-01, 5.000255e-01
		},
		{
			1.603818e-17, 2.507028e-01, 5.000127e-01, 5.000749e-01,
			5.000210e-01, 4.999960e-01, 4.999553e-01, 5.000067e-01,
			4.999978e-01, 5.000153e-01, 4.999992e-01, 5.000390e-01
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz3_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz4") == 0)
	{
		double dtlz4_extremes[3][12] = {{
			9.999999e-01, 9.999936e-01, 4.951966e-01, 5.064815e-01,
			4.924490e-01, 4.995276e-01, 4.979789e-01, 5.009201e-01,
			4.996556e-01, 5.046379e-01, 4.941011e-01, 5.042929e-01
		},
		{
			9.938179e-01, 4.311857e-06, 4.967517e-01, 5.059470e-01,
			4.920211e-01, 4.946013e-01, 4.937855e-01, 5.064931e-01,
			5.034025e-01, 5.012390e-01, 5.038550e-01, 5.013487e-01
		},
		{
			3.109724e-05, 9.864765e-01, 4.925116e-01, 5.056041e-01,
			5.061607e-01, 5.022251e-01, 5.066173e-01, 4.994877e-01,
			4.962075e-01, 5.206323e-01, 5.042736e-01, 4.955822e-01
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz4_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz5") == 0)
	{
		double dtlz5_extremes[3][12] = {{
			2.019607e-05, 4.691999e-03, 4.998126e-01, 4.998191e-01,
			4.997985e-01, 5.004007e-01, 5.004654e-01, 4.985565e-01,
			5.007254e-01, 5.006066e-01, 5.003787e-01, 5.009204e-01
		},
		{
			9.999995e-01, 5.958631e-02, 4.995468e-01, 4.998111e-01,
			4.998534e-01, 5.003983e-01, 5.004524e-01, 4.985724e-01,
			5.003780e-01, 5.014114e-01, 5.005870e-01, 4.997269e-01
		},
		{
			9.999995e-01, 3.426279e-03, 4.995468e-01, 4.998111e-01,
			4.998614e-01, 5.003983e-01, 5.004646e-01, 4.985644e-01,
			5.003780e-01, 5.014114e-01, 4.991804e-01, 4.996749e-01
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz5_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz6") == 0)
	{
		double dtlz6_extremes[3][12] = {{
			1.000000e+00, 9.974290e-01, 1.524748e-16, 0.000000e+00,
			0.000000e+00, 4.040056e-16, 0.000000e+00, 6.684228e-18,
			1.065101e-16, 9.675644e-16, 1.030307e-16, 2.002856e-16
		},
		{
			1.000000e+00, 5.476236e-03, 4.145254e-17, 0.000000e+00,
			0.000000e+00, 4.040056e-16, 0.000000e+00, 6.684228e-18,
			0.000000e+00, 9.675644e-16, 2.140530e-16, 2.002856e-16
		},
		{
			1.783298e-14, 1.947983e-01, 1.611822e-17, 1.287583e-16,
			2.546368e-16, 2.507170e-18, 6.422436e-16, 2.649740e-17,
			3.026288e-17, 0.000000e+00, 0.000000e+00, 0.000000e+00
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz6_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz7") == 0)
	{
		double dtlz7_extremes[3][22] = {{
			1.284353e-01, 2.189343e-16, 2.930163e-05, 4.354765e-05, 1.820315e-05,
			3.752028e-05, 2.406706e-05, 3.900316e-05, 1.802562e-05, 3.204943e-05,
			7.783208e-05, 4.226695e-05, 1.004431e-04, 1.393878e-04, 1.947388e-04,
			1.946992e-05, 1.630548e-05, 1.691152e-04, 2.285285e-04, 2.871427e-07,
			1.340409e-04, 1.724859e-05
		},
		{
			8.561563e-01, 8.603832e-01, 1.070907e-04, 7.042681e-06, 8.530980e-06,
			3.459961e-05, 1.128565e-04, 2.467800e-04, 3.266559e-05, 3.182198e-05,
			7.753045e-06, 1.895454e-04, 1.014680e-04, 1.100796e-06, 2.734151e-05,
			1.011304e-05, 1.642499e-05, 2.949661e-05, 2.803044e-05, 1.428371e-06,
			1.712368e-06, 4.230554e-06
		},
		{
			1.734470e-10, 1.625798e-01, 1.846982e-05, 1.720799e-04, 1.095058e-04,
			2.736409e-04, 6.024500e-05, 1.357000e-04, 2.846853e-02, 6.946536e-05,
			9.281912e-05, 1.324629e-05, 7.452940e-05, 2.288953e-04, 1.966254e-04,
			9.450860e-06, 2.335544e-05, 9.642324e-05, 2.035835e-06, 1.157488e-04,
			1.221824e-04, 7.156969e-05
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz7_extremes[i], sizeof(double) * nreal);
	}
	else
	{
		fprintf(stdout, " Error: wrong problem string or problem not defined. \n");
		exit(1);
	}
	for(i = 0 ; i < nobj; i++)
	{
		fprintf(stdout, "\n********** using hardcoded extremes:\n");
		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, extremes[i], sizeof(double) * nreal);
		push_back(e_star, &ind);
		deallocate_memory_ind(&ind);
		feval += 1 ;
	}
	for(i = 0 ; i < nobj ; i++) free(extremes[i]);
	free(extremes);
	return feval ;
}

int init_extreme_pts_hardcoded_weak(void)
{
	double **extremes ;
	int feval = 0, i;
	/* e_star = new_list(); */
	individual ind ;
	extremes = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++) extremes[i] = (double*)malloc(sizeof(double) * nreal);
	
	if(strcmp(prob_name, "zdt4") == 0)
	{
		double zdt4_extremes[2][10] = {{
			1.000,	-0.009,	0.473,	0.508,	0.498,	0.393,	0.519,	0.804,	0.618,	0.384
		},
		{
			0.000,	0.616,	0.531,	1.029,	0.690,	1.101,	0.687,	-0.538,	0.051,	0.391
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt4_extremes[i], sizeof(double) * nreal);
	}
	else if(strcmp(prob_name, "dtlz1") == 0)
	{
		double dtlz1_extremes[3][12] = {{
			0.073,	0.000,	0.499,	0.494,	0.399,	0.500,	
			0.500,	0.491,	0.501,	0.491,	0.601,	0.589
		},
		{
			0.000,	0.031,	0.500,	0.499,	0.392,	0.506,
			0.499,	0.492,	0.500,	0.500,	0.201,	0.610
		},
		{
			1.000,	0.993,	0.500,	0.491,	0.515,	0.500,	
			0.509,	0.596,	0.487,	0.498,	0.507,	0.609
		}};
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz1_extremes[i], sizeof(double) * nreal);
	}
	else
	{
		fprintf(stdout, " Error: wrong problem string or problem not defined. \n");
		exit(1);
	}
	for(i = 0 ; i < nobj; i++)
	{
		fprintf(stdout, "\n********** using hardcoded extremes:\n");
		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, extremes[i], sizeof(double) * nreal);
		push_back(e_star, &ind);
		deallocate_memory_ind(&ind);
		feval += 1 ;
	}
	for(i = 0 ; i < nobj ; i++) free(extremes[i]);
	free(extremes);
	return feval ;
}

int init_extreme_pts_sosolver(double seed)
{
	int feval = 0 ;
	/* e_star = new_list(); */
	fprintf(stdout, "\n********** sosolver:\n");
	feval += sosolver(e_star, seed);
	fprintf(stdout, "e_star:\n");
	dump_pop_list(stdout, e_star);
	return feval;
}

int init_extreme_pts_sosolver_weighted(double seed)
{
	int feval = 0 ;
	/* e_star = new_list(); */
	fprintf(stdout, "\n********** sosolver:\n");
	feval += sosolver_weighted(e_star, seed);
	fprintf(stdout, "e_star:\n");
	dump_pop_list(stdout, e_star);
	return feval;
}

void inject_extreme_points(population *pop)
{
	int i, *idx ;
	node *ptr ;
	idx = (int*)malloc(sizeof(int) * popsize);
	get_random_indices(idx, popsize);
	if(debug) fprintf(stdout, "\ninjecting into:\n");
	for(i = 0, ptr = e_star->head ; ptr != END ; ptr = ptr->next, i++)
	{
		if(debug) fprintf(stdout, "%d: ", idx[i]);
		memcpy(pop->ind[idx[i]].xreal, ptr->ind->xreal, sizeof(double) * nreal);
		if(debug) {
			evaluate_ind(ptr->ind);
			dumpf_individual(stdout, ptr->ind);
		}
	}
	free(idx);
	return ;
}

void generate_opposite_population(population *pop, pop_list *op_parent, pop_list *op_child, int gen,
		double *overshoot_stat)
{
	int any_gene_corrupted = 0, max_gene_corrupted = 0, all_correct = 0 ;
	int sum_genes_corrupted = 0  ;
	double *x, *t ;
	pop_list *pool ;
	node *ptr ;
	individual ind ;

	t = (double*)malloc(sizeof(double) * nreal);
	x = (double*)malloc(sizeof(double) * nreal);

	/* pool size may not be constant */
	pool = new_list();
	make_pool(pop, pool);

	gather_op_parent(pop, op_parent);
	if(showmap) fprintf(stdout, "\ngen = %d\n", gen);
	for(ptr = op_parent->head; ptr != END ; ptr = ptr->next)
	{
		get_furthest_point_from_m_random_select(pool, nobj, ptr->ind->xreal, t);
		int genes_corrupted = generate_opposite_vector_q3(ptr->ind->xreal, t, x);
		
		if(showmap) {
			individual p ;
			allocate_memory_ind(&p) ;
			initialize_ind_dummy(&p) ;
			memcpy(p.xreal, t, sizeof(double) * nreal);
			evaluate_ind(&p);
			/* parent */
			dump_individual(stdout, ptr->ind);
			/* pivot */
			dump_individual(stdout, &p);
			deallocate_memory_ind(&p);
		}
		/* fprintf(stdout, "\n\t\tgenes_corrupted = %d", genes_corrupted);*/
		
		/* some stats for gene overshoot */
		if(genes_corrupted > 0) any_gene_corrupted++ ;
		if(genes_corrupted == 30) max_gene_corrupted++ ;
		if(genes_corrupted == 0) all_correct++;
		sum_genes_corrupted += genes_corrupted ;

		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, x, sizeof(double) * nreal);
		ind.is_opposite = 1 ;
		push_back(op_child, &ind);
		evaluate_ind(&ind);
		if(showmap) { 
			/* child */
			dump_individual(stdout, &ind); 
			fprintf(stdout, "\n");
		}
		deallocate_memory_ind(&ind);
	}
	free(x);
	free(t);
	free_list(pool);
	overshoot_stat[0] = (any_gene_corrupted / (double)op_popsize) * 100.0 ;
	overshoot_stat[1] = (sum_genes_corrupted/ (double)(op_popsize * nreal))/(double)op_popsize;
	overshoot_stat[2] = (max_gene_corrupted/(double)op_popsize) * 100.0 ;
	overshoot_stat[3] = (all_correct/(double)op_popsize) * 100.0 ;
	return;
}

void generate_opposite_population_inverse(population *pop, pop_list *op_parent, pop_list *op_child, int gen,
		double *overshoot_stat)
{
	int any_gene_corrupted = 0, max_gene_corrupted = 0, all_correct = 0 ;
	int sum_genes_corrupted = 0  ;
	double *x, *t ;
	pop_list *pool ;
	node *ptr ;
	individual ind ;

	t = (double*)malloc(sizeof(double) * nreal);
	x = (double*)malloc(sizeof(double) * nreal);

	/* pool size may not be constant */
	pool = new_list();
	make_pool(pop, pool);

	gather_op_parent(pop, op_parent);
	if(showmap) fprintf(stdout, "\ngen = %d\n", gen);
	for(ptr = op_parent->head; ptr != END ; ptr = ptr->next)
	{
		get_closest_point_from_m_random_select(pool, nobj, ptr->ind->xreal, t);
		int genes_corrupted = generate_opposite_vector_q3(ptr->ind->xreal, t, x);
		
		if(showmap) {
			individual p ;
			allocate_memory_ind(&p) ;
			initialize_ind_dummy(&p) ;
			memcpy(p.xreal, t, sizeof(double) * nreal);
			evaluate_ind(&p);
			/* parent */
			dump_individual(stdout, ptr->ind);
			/* pivot */
			dump_individual(stdout, &p);
			deallocate_memory_ind(&p);
		}
		/* fprintf(stdout, "\n\t\tgenes_corrupted = %d", genes_corrupted);*/
		
		/* some stats for gene overshoot */
		if(genes_corrupted > 0) any_gene_corrupted++ ;
		if(genes_corrupted == 30) max_gene_corrupted++ ;
		if(genes_corrupted == 0) all_correct++;
		sum_genes_corrupted += genes_corrupted ;

		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, x, sizeof(double) * nreal);
		ind.is_opposite = 1 ;
		push_back(op_child, &ind);
		evaluate_ind(&ind);
		if(showmap) { 
			/* child */
			dump_individual(stdout, &ind); 
			fprintf(stdout, "\n");
		}
		deallocate_memory_ind(&ind);
	}
	free(x);
	free(t);
	free_list(pool);
	overshoot_stat[0] = (any_gene_corrupted / (double)op_popsize) * 100.0 ;
	overshoot_stat[1] = (sum_genes_corrupted/ (double)(op_popsize * nreal))/(double)op_popsize;
	overshoot_stat[2] = (max_gene_corrupted/(double)op_popsize) * 100.0 ;
	overshoot_stat[3] = (all_correct/(double)op_popsize) * 100.0 ;
	return;
}

void generate_opposite_population_random(population *pop, pop_list *op_parent, pop_list *op_child, int gen,
		double *overshoot_stat)
{
	int any_gene_corrupted = 0, max_gene_corrupted = 0, all_correct = 0 ;
	int sum_genes_corrupted = 0  ;
	double *x, *t ;
	pop_list *pool ;
	node *ptr ;
	individual ind ;

	t = (double*)malloc(sizeof(double) * nreal);
	x = (double*)malloc(sizeof(double) * nreal);

	/* pool size may not be constant */
	pool = new_list();
	make_pool(pop, pool);

	gather_op_parent(pop, op_parent);
	if(showmap) fprintf(stdout, "\ngen = %d\n", gen);
	for(ptr = op_parent->head; ptr != END ; ptr = ptr->next)
	{
		get_random_point_from_m_random_select(pool, nobj, ptr->ind->xreal, t);
		int genes_corrupted = generate_opposite_vector_q3(ptr->ind->xreal, t, x);
		
		if(showmap) {
			individual p ;
			allocate_memory_ind(&p) ;
			initialize_ind_dummy(&p) ;
			memcpy(p.xreal, t, sizeof(double) * nreal);
			evaluate_ind(&p);
			/* parent */
			dump_individual(stdout, ptr->ind);
			/* pivot */
			dump_individual(stdout, &p);
			deallocate_memory_ind(&p);
		}
		/* fprintf(stdout, "\n\t\tgenes_corrupted = %d", genes_corrupted);*/
		
		/* some stats for gene overshoot */
		if(genes_corrupted > 0) any_gene_corrupted++ ;
		if(genes_corrupted == 30) max_gene_corrupted++ ;
		if(genes_corrupted == 0) all_correct++;
		sum_genes_corrupted += genes_corrupted ;

		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, x, sizeof(double) * nreal);
		ind.is_opposite = 1 ;
		push_back(op_child, &ind);
		evaluate_ind(&ind);
		if(showmap) { 
			/* child */
			dump_individual(stdout, &ind); 
			fprintf(stdout, "\n");
		}
		deallocate_memory_ind(&ind);
	}
	free(x);
	free(t);
	free_list(pool);
	overshoot_stat[0] = (any_gene_corrupted / (double)op_popsize) * 100.0 ;
	overshoot_stat[1] = (sum_genes_corrupted/ (double)(op_popsize * nreal))/(double)op_popsize;
	overshoot_stat[2] = (max_gene_corrupted/(double)op_popsize) * 100.0 ;
	overshoot_stat[3] = (all_correct/(double)op_popsize) * 100.0 ;
	return;
}

/**
 * generate opposite population with lateral and non-lateral jump 
 * Algorithm:
 * 	op_popsize = total number of opposites
 * 	maxrank = number of ranks in population
 *	v = (int)floor((2.0 * op_popsize) / 3.0) ;
 *	
 *	op_parent = gather v numbers of op_parent fron N to 2 if possible
 *	ref = take front 1 as reference
 *	if(op_parent != empty)
 *	{
 *		for each individual i from op_parent
 *		do
 *			t = pick closest point to i fron ref
 *			x = generate opposite using t, i using jump double jump distance
 *			push x into op_child
 *		done
 *	}
 *
 *	pool = make_pool
 *	op_parent = gather (op_popsize - v) numbers of op_parent using all fronts
 * 	for each individual i from op_parent
 * 	do
 * 		t = pick one using the furthest distance with m random select from pool
 *		x = generate opposite using t, i with retry
 *		push x into op_child
 *	done
 */
void generate_opposite_population_jump(population *pop, pop_list *op_parent, 
					pop_list *op_child, int gen, double *overshoot_stat)
{
	int any_gene_corrupted = 0, max_gene_corrupted = 0; 
	int all_correct = 0, sum_genes_corrupted = 0  ;
	double *x, *t ;
	pop_list *pool, *refs ;
	node *ptr ;
	individual ind ;
	int v ;

	t = (double*)malloc(sizeof(double) * nreal);
	x = (double*)malloc(sizeof(double) * nreal);
	
	v = (int)floor((2.0 * op_popsize) / 3.0) ;
	gather_op_parent_skip_pareto(pop, op_parent, v);
	v = op_parent->size ;
	refs = new_list();
	gather_ref_points(pop, refs);
	if(v > 0)
	{
		for(ptr = op_parent->head; ptr != END ; ptr = ptr->next)
		{
			get_closest_point_from_refs(refs, ptr->ind->xreal, t, gen);
			/*get_random_double_vector(t, nreal, 0.0, 1.0);*/
			/*int genes_corrupted = generate_opposite_vector_q3(
						ptr->ind->xreal, t, x);*/
			int genes_corrupted = generate_opposite_vector_q3_retry(
			 			ptr->ind->xreal, t, x, 1.01, 5.0);
			/*int genes_corrupted = generate_opposite_hadamard_q3(
			 			ptr->ind->xreal, t, x);*/
			/*int genes_corrupted = generate_opposite_hadamard_q3_retry(
			 			ptr->ind->xreal, t, x, 1.01, 5.0);*/

			/* some stats for gene overshoot */
			if(genes_corrupted > 0) any_gene_corrupted++ ;
			if(genes_corrupted == nreal) max_gene_corrupted++ ;
			if(genes_corrupted == 0) all_correct++;
			sum_genes_corrupted += genes_corrupted ;

			allocate_memory_ind(&ind); 
			/* to shut the valgrind complains :-( */
			initialize_ind_dummy(&ind);
			memcpy(ind.xreal, x, sizeof(double) * nreal);
			ind.is_opposite = 1 ;
			push_back(op_child, &ind);
			evaluate_ind(&ind);
			deallocate_memory_ind(&ind);
		}
	}
	make_empty_ptr(op_parent);

	/* pool size may not be constant */
	pool = new_list();
	make_pool(pop, pool);

	gather_op_parent_with_size(pop, op_parent, op_popsize - v);
	if(showmap) fprintf(stdout, "\ngen = %d\n", gen);
	for(ptr = op_parent->head; ptr != END ; ptr = ptr->next)
	{
		get_furthest_point_from_m_random_select(pool, nobj, ptr->ind->xreal, t);
		int genes_corrupted = generate_opposite_vector_q3(ptr->ind->xreal, t, x);
		
		/* this section shows the mapping from parent to child */
		if(showmap) {
			individual p ;
			allocate_memory_ind(&p) ;
			initialize_ind_dummy(&p) ;
			memcpy(p.xreal, t, sizeof(double) * nreal);
			evaluate_ind(&p);
			/* parent */
			dump_individual(stdout, ptr->ind);
			/* pivot */
			dump_individual(stdout, &p);
			deallocate_memory_ind(&p);
		}
		/* fprintf(stdout, "\n\t\tgenes_corrupted = %d", genes_corrupted);*/
		
		/* some stats for gene overshoot */
		if(genes_corrupted > 0) any_gene_corrupted++ ;
		if(genes_corrupted == nreal) max_gene_corrupted++ ;
		if(genes_corrupted == 0) all_correct++;
		sum_genes_corrupted += genes_corrupted ;

		allocate_memory_ind(&ind); 
		/* to shut the valgrind complains :-( */
		initialize_ind_dummy(&ind);
		memcpy(ind.xreal, x, sizeof(double) * nreal);
		ind.is_opposite = 1 ;
		push_back(op_child, &ind);
		evaluate_ind(&ind);
		if(showmap) { 
			/* child */
			dump_individual(stdout, &ind); 
			fprintf(stdout, "\n");
		}
		deallocate_memory_ind(&ind);
	}
	free(x);
	free(t);
	free_list(pool);
	free_list_ptr(refs);
	overshoot_stat[0] = (any_gene_corrupted / (double)op_popsize) * 100.0 ;
	overshoot_stat[1] = (sum_genes_corrupted/ (double)(op_popsize * nreal))/(double)op_popsize;
	overshoot_stat[2] = (max_gene_corrupted/(double)op_popsize) * 100.0 ;
	overshoot_stat[3] = (all_correct/(double)op_popsize) * 100.0 ;

	return;
}

/**
 * Pool making scheme:
 * 	1. get extremes from the current population, e 
 * 	2. get the true extreme points found at the start-up e*
 * 	3. make set E = {e U e*}
 * 	4. filter out the weakly dominated points in E, 
 * 		and keep the strongly dominated points 'e'
 * 	5. update e* with e_
 * 	6. get the points 'g' on the intermediary 
 * 		gaps from the current front
 * 	7. pool p = {e_ U g}
 */
void make_pool(population *pop, pop_list *pool)
{
	int i, E_size, g_size;
	population E_ ;
	population g ;
	pop_list *e_ ;
	node *ptr ;

	int with_infinity(individual *i1, individual *i2);
	int no_infinity_pf(individual *i1, individual *i2);

	E_size = nobj + e_star->size ;
	g_size = nobj ;
	/* we need to do this in array as we are going to apply NDS on it */
	allocate_memory_pop(&E_, E_size); initialize_pop_dummy_with_size(&E_, E_size);
	allocate_memory_pop(&g, g_size); initialize_pop_dummy_with_size(&g, g_size);

	/* extreme points 'e' from the current population */
	get_extreme_individuals(pop, popsize, E_.ind, nobj, with_infinity);
	/* copy the provided extremes 'e*' */
	for(ptr = e_star->head, i = 0 ; ptr != END ; ptr = ptr->next, i++)
	{
		memcpy(E_.ind[nobj + i].xreal, ptr->ind->xreal, sizeof(double) * nreal);
		evaluate_ind(&(E_.ind[nobj + i]));
	}
	/**
	 * now, E = {e U e*}, get the pareto extreme points from current 
	 * population extremes and provided extremes, |e_| could be < nobj 
	 **/
	e_ = discard_weakly_dominated_points(&E_, E_size);
	make_empty(e_star);
	/* save the selected extremes for future use */
	for(ptr = e_->head; ptr != END ; ptr = ptr->next)
	{
		push_back(e_star, ptr->ind);
		push_back(pool, ptr->ind);
	}

	/* get the intermediary gaps 'g' from the current population pf */
	get_extreme_individuals(pop, popsize, g.ind, nobj, no_infinity_pf);
	for(i = 0; i < nobj ; i++)
		push_back(pool, &(g.ind[i]));

	free_list_ptr(e_);
	deallocate_memory_pop(&E_, E_size);
	deallocate_memory_pop(&g, nobj);
	return ;
}
/* Inner functions */
int no_infinity_pf(individual *curr, individual *best) {
	if(best->crowd_dist == INF) return 1 ;
	else if(curr->rank == 1 && curr->crowd_dist < INF
	        && best->rank == 1 && curr->crowd_dist >= best->crowd_dist) return 1 ;
	else return 0 ;
}

/* Inner functions */
int with_infinity(individual *curr, individual *best) {
	if(curr->crowd_dist >= best->crowd_dist) return 1 ;
	else return 0 ;
}

/**
 * discard the weakly dominated points:
 * 	1. First sort the set E by non-domination
 * 	2. now partition E into two sets E = {b U r} such that -- 
 * 	   set b contains only the points on the pareto front and with INF crowding dist 
 * 	   and set r contains the point except those in b
 * 	3. ... needs to be fixed
 */
pop_list* discard_weakly_dominated_points(population *E_, int size)
{
	node *rptr, *bptr;
	pop_list *rest, *best ;
	int mod ;

	/* apply NDS to set E */
	assign_rank_and_crowding_distance_with_size(E_, size);

	/* now partition them to best and non-best */
	rest = new_list();
	best = new_list();
	to_list_ptr(E_, size, rest); /* make the array to list */

	rptr = rest->head ;
	while(rptr != END)
	{
		if(rptr->ind->rank == 1 && rptr->ind->crowd_dist == INF)
		{
			push_back_ptr(best, rptr->ind);
			rptr = erase_ptr(rest, rptr);
		}
		else
			rptr = rptr->next ;
	}
	/* now rest contains all points on the PF and crowd. dist == INF */

	/* for debugging */
	if(debug)
	{
		fprintf(stdout, "\nE: \n");
		dump_population(stdout, E_, size);
	}

	/* if there is any point in rest that weakly dominates any point in best, then do this */
	mod = 0 ;
	for(rptr = rest->head; rptr != END; rptr = rptr->next)
	{
		bptr = best->head ;
		while(bptr != END)
		{
			if(weakly_dominates(rptr->ind, bptr->ind))
			{
				/*fprintf(stdout, "\n[%0.3f, %0.3f] --> [%0.3f, %0.3f]\n",
						rptr->ind->obj[0], rptr->ind->obj[1],
						bptr->ind->obj[0], bptr->ind->obj[1]);*/
				bptr = erase_ptr(best, bptr);
				push_back_ptr(best, rptr->ind);
				mod = 1 ;
			}
			else
				bptr = bptr->next ;
		}
	}

	/* for debugging */
	if(debug) 
	{
		if(mod)
		{
			fprintf(stdout, "----> modified rest %d: \n", rest->size);
			dump_pop_list(stdout, rest);
			fprintf(stdout, "----> modified best %d: \n", best->size);
			dump_pop_list(stdout, best);
		}
		else
		{
			fprintf(stdout, "rest %d: \n", rest->size);
			dump_pop_list(stdout, rest);
			fprintf(stdout, "best %d: \n", best->size);
			dump_pop_list(stdout, best);
		}
	}

	free_list_ptr(rest);
	return best ;
}

/* checks if i1 weakly dominates i2 */
int weakly_dominates(individual *i1, individual *i2)
{
	int equal = 0 ;
	int less_than = 0 ;
	int greater_than = 0 ;
	int i ;

	for(i = 0 ; i < nobj ; i++)
	{
		if(fltcmp(i1->obj[i], i2->obj[i], 0.001) == 0)
			equal++ ;
		if(fltcmp(i1->obj[i], i2->obj[i], 0.001) == -1)
			less_than++ ;
		if(fltcmp(i1->obj[i], i2->obj[i], 0.001) == 1)
			greater_than++;
	}
	if(less_than == 1 && equal == nobj - 1)
		return 1 ;
	else
		return 0 ;
}

void gather_op_parent(population *pop, pop_list *op_parent)
{
	int i ;
	int rank_compare_asc(individual *i1, individual *i2);
	int *idx = (int*)malloc(sizeof(int) * op_popsize);
	get_random_indices(idx, op_popsize);
	quicksort_(pop, popsize, rank_compare_asc);
	for(i = 0 ; i < op_popsize; i++)
		push_back_ptr(op_parent, &pop->ind[idx[i]]);
	free(idx);
	return ;
}

void gather_op_parent_with_size(population *pop, pop_list *op_parent, int sz)
{
	int i ;
	int rank_compare_asc(individual *i1, individual *i2);
	int *idx = (int*)malloc(sizeof(int) * sz);
	get_random_indices(idx, sz);
	quicksort_(pop, popsize, rank_compare_asc);
	for(i = 0 ; i < sz; i++)
		push_back_ptr(op_parent, &pop->ind[idx[i]]);
	free(idx);
	return ;
}

void gather_op_parent_skip_pareto(population *pop, pop_list *op_parent, int sz)
{
	int i, pushcount ;
	int rank_compare_desc(individual *i1, individual *i2);
	quicksort_(pop, popsize, rank_compare_desc);
	pushcount = 0 ;
	for(i = 0 ; i < popsize ; i++) 
		if(pop->ind[i].rank > 1) {
			push_back_ptr(op_parent, &pop->ind[i]);
			pushcount++ ;
			if(pushcount == sz) break ;
		}
	return ;
}

void gather_ref_points(population *pop, pop_list *refs)
{
	int i ;
	for(i = 0 ; i < popsize ; i++) 
		if(pop->ind[i].rank == 1) {
			push_back_ptr(refs, &pop->ind[i]);
		}
	return ;
}

/* inner functions */
int rank_compare_asc(individual *i1, individual *i2) 
	{ if(i1->rank <= i2->rank) return 1; else return 0 ;}
int rank_compare_desc(individual *i1, individual *i2) 
	{ if(i1->rank <= i2->rank) return 0; else return 1 ;}

/** 
 * from the pool, select m number of points randomly
 * and then select the one which is furthest from s,
 * where m == no of objectives.
 */
void get_furthest_point_from_m_random_select(pop_list *pool, int m, double *s, double *t)
{
	int i, index ;
	double max_dist, dist ;
	pop_list *selected ;
	node *ptr, *max_ptr ;
	selected = new_list();

	while(selected->size != m)
	{
		index = rnd(0, pool->size-1);
		for(ptr = pool->head, i = 0 ; ptr != END ; ptr = ptr->next, i++)
			if(i == index)
			{
				push_back_ptr(selected, ptr->ind);
				break ;
			}
	}

	max_dist = get_vector_distance(s, selected->head->ind->xreal, nreal);
	max_ptr = selected->head ;
	for(ptr = selected->head->next ; ptr != END ; ptr = ptr->next)
	{
		dist = get_vector_distance(s, ptr->ind->xreal, nreal);
		if(dist >= max_dist)
		{
			max_dist = dist ;
			max_ptr = ptr ;
		}
	}

	memcpy(t, max_ptr->ind->xreal, sizeof(double) * nreal);
	free_list_ptr(selected);
	return ;
}

void get_closest_point_from_m_random_select(pop_list *pool, int m, double *s, double *t)
{
	int i, index ;
	double min_dist, dist ;
	pop_list *selected ;
	node *ptr, *min_ptr ;
	selected = new_list();

	while(selected->size != m)
	{
		index = rnd(0, pool->size-1);
		for(ptr = pool->head, i = 0 ; ptr != END ; ptr = ptr->next, i++)
			if(i == index)
			{
				push_back_ptr(selected, ptr->ind);
				break ;
			}
	}

	min_dist = get_vector_distance(s, selected->head->ind->xreal, nreal);
	min_ptr = selected->head ;
	for(ptr = selected->head->next ; ptr != END ; ptr = ptr->next)
	{
		dist = get_vector_distance(s, ptr->ind->xreal, nreal);
		if(dist <= min_dist)
		{
			min_dist = dist ;
			min_ptr = ptr ;
		}
	}

	memcpy(t, min_ptr->ind->xreal, sizeof(double) * nreal);
	free_list_ptr(selected);
	return ;
}

void get_random_point_from_m_random_select(pop_list *pool, int m, double *s, double *t)
{
	int i, index ;
	pop_list *selected ;
	node *ptr, *sel_ptr ;
	selected = new_list();

	while(selected->size != m)
	{
		index = rnd(0, pool->size-1);
		for(ptr = pool->head, i = 0 ; ptr != END ; ptr = ptr->next, i++)
			if(i == index)
			{
				push_back_ptr(selected, ptr->ind);
				break ;
			}
	}

	index = rnd(0, selected->size-1) ;
	for(ptr = selected->head, i = 0 ; ptr != END ; ptr = ptr->next, i++)
	{
		if(i == index)
		{
			sel_ptr = ptr ;
			break ;
		}
	}

	memcpy(t, sel_ptr->ind->xreal, sizeof(double) * nreal);
	free_list_ptr(selected);
	return ;
}

void get_closest_point_from_refs(pop_list *refs, double *s, double *t, int gen)
{
	double min_dist, dist ;
	node *ptr, *min_ptr ;
	min_dist = get_vector_distance(s, refs->head->ind->xreal, nreal);
	for(min_ptr = refs->head, ptr = refs->head->next ; ptr != END ; ptr = ptr->next)
	{
		dist = get_vector_distance(s, ptr->ind->xreal, nreal);
		if(dist <= min_dist)
		{
			min_dist = dist ;
			min_ptr = ptr ;
		}
	}
	memcpy(t, min_ptr->ind->xreal, sizeof(double) * nreal);
	return ;
}

/**
 * from s and t find the opposite vector d using mirroring.
 */ 
int generate_opposite_vector_q3(double *s, double *t, double *d)
{
	double *stu, *s_t, dist ;
	int i, shootouts = 0 ;

	s_t = (double*)malloc(sizeof(double) * nreal);
	stu = (double*)malloc(sizeof(double) * nreal);

	dist = get_vector_distance(s, t, nreal);
	if(dist > 0.001)
	{
		vector_subtract(t, s, nreal, s_t);
		get_unit_vector(s_t, nreal, stu);
		if(rndreal(0.0, 1.0) < 0.5)
			multiply_scalar(stu, nreal, rndreal(dist * 0.75, dist));
		else
			multiply_scalar(stu, nreal, rndreal(dist, dist * 1.25));
		vector_add(s, stu, nreal, d);
	}
	else
		memcpy(d, s, sizeof(double) * nreal);

	free(stu);
	free(s_t);

	/** shoot out correction */
	for(i = 0 ; i < nreal ; i++)
	{
		if(isnan(d[i]) || d[i] < min_realvar[i] || d[i] > max_realvar[i])
		{
			d[i] = t[i] ;
			shootouts++ ;
		}
	}
	return shootouts ;
}

int generate_opposite_vector_q3_retry(double *s, double *t, double *d, 
		double minjmp, double maxjmp)
{
	double *stu, *stu_, *s_t, dist ;

	s_t = (double*)malloc(sizeof(double) * nreal);
	stu = (double*)malloc(sizeof(double) * nreal);
	stu_ = (double*)malloc(sizeof(double) * nreal);

	dist = get_vector_distance(s, t, nreal);
	if(fabs(dist) > 0.0001)
	{
		vector_subtract(t, s, nreal, s_t);
		get_unit_vector(s_t, nreal, stu);
		multiply_scalar(stu, nreal, rndreal(dist * minjmp, dist * maxjmp)); // 1.01, 1.5
		vector_add(s, stu, nreal, d);
		if(sum_overshoot(d) > 0) 
		{
			get_unit_vector(s_t, nreal, stu_);
			multiply_scalar(stu_, nreal, rndreal(dist * 0.75, dist));
			vector_add(s, stu_, nreal, d);
		}
	}
	else
		memcpy(d, s, sizeof(double) * nreal);

	free(stu);
	free(stu_);
	free(s_t);

	return sum_overshoot(d);
}

/**
 * from s and t find the opposite vector d using mirroring, with no vector op.
 */ 
int generate_opposite_hadamard_q3(double *s, double *t, double *d)
{
	int i, shootouts = 0 ;
	double dist, close, far ;

	for(i = 0 ; i < nreal ; i++)
	{
		dist = fabs(s[i] - t[i]); 
		if(dist > 0.001)
		{
			close = rndreal(0.75, 1.0);
			far = rndreal(1.0, 1.5);
			if(rndreal(0.0,1.0) < 0.5) d[i] = s[i] + close ;
			else 
			{
				d[i] = s[i] + far ;
				if(isnan(d[i]) || d[i] < min_realvar[i] || d[i] > max_realvar[i])
				{
					close = rndreal(0.75, 1.0);
					d[i] = s[i] + close ;
					shootouts++ ;
				}
			}
		}
	}
	return shootouts ;
}

int generate_opposite_hadamard_q3_retry(double *s, double *t, double *d, 
		double minjmp, double maxjmp)
{
	int i, shootouts = 0 ;
	double dist, close, far ;

	for(i = 0 ; i < nreal ; i++)
	{
		dist = fabs(s[i] - t[i]); 
		if(dist > 0.001)
		{
			close = rndreal(1.0, minjmp);
			far = rndreal(1.0, maxjmp);
			if(rndreal(0.0,1.0) < 0.5) d[i] = s[i] + close ;
			else d[i] = s[i] + far ;
			if(isnan(d[i]) || d[i] < min_realvar[i] || d[i] > max_realvar[i])
			{
				close = rndreal(0.75, 1.0);
				d[i] = s[i] + close ;
				shootouts++ ;
			}
		}
	}
	return shootouts ;
}

int sum_overshoot(double *d)
{
	int i, overshoot = 0 ;
	for(i = 0 ; i < nreal ; i++)
		if(isnan(d[i]) || d[i] < min_realvar[i] || d[i] > max_realvar[i])
			overshoot++;
	return overshoot ;
}

/* clears all the opposite flag of the individuals in a population */
void clear_opposite_flag(population *pop)
{
	int i ;
	for(i = 0 ; i < popsize ; i++) pop->ind[i].is_opposite = 0 ;
	return ;
}

void inject_opposite_shuffle(pop_list *op_child, population *destpop)
{
	int i, *index; node *ptr ;
	index = (int*)malloc(sizeof(int) * popsize);
	get_random_indices(index, popsize);
	for(i = 0, ptr = op_child->head ; i < op_popsize ; i++, ptr = ptr->next)
		indcpy(ptr->ind, &(destpop->ind[index[i]]));
	free(index);
	return ;
}

void gather_survived_individuals(population *parent_pop, pop_list *survived_pop)
{
	int i ;
	for( i = 0 ; i < popsize ; i++)
		if(parent_pop->ind[i].is_opposite)
			push_back_ptr(survived_pop, &(parent_pop->ind[i]));
	return ;
}

void assign_rank_and_crowding_distance_with_size (population *new_pop, int psize)
{
	int flag;
	int i;
	int end;
	int front_size;
	int rank=1;
	list *orig;
	list *cur;
	list *temp1, *temp2;
	orig = (list *)malloc(sizeof(list));
	cur = (list *)malloc(sizeof(list));
	front_size = 0;
	orig->index = -1;
	orig->parent = NULL;
	orig->child = NULL;
	cur->index = -1;
	cur->parent = NULL;
	cur->child = NULL;
	temp1 = orig;
	for (i = 0; i < psize; i++)
	{
		insert (temp1,i);
		temp1 = temp1->child;
	}
	do
	{
		if (orig->child->child == NULL)
		{
			new_pop->ind[orig->child->index].rank = rank;
			new_pop->ind[orig->child->index].crowd_dist = INF;
			break;
		}
		temp1 = orig->child;
		insert (cur, temp1->index);
		front_size = 1;
		temp2 = cur->child;
		temp1 = del (temp1);
		temp1 = temp1->child;
		do
		{
			temp2 = cur->child;
			do
			{
				end = 0;
				flag = check_dominance (&(new_pop->ind[temp1->index]), &(new_pop->ind[temp2->index]));
				if (flag == 1)
				{
					insert (orig, temp2->index);
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
				insert (cur, temp1->index);
				front_size++;
				temp1 = del (temp1);
			}
			temp1 = temp1->child;
		}
		while (temp1 != NULL);
		temp2 = cur->child;
		do
		{
			new_pop->ind[temp2->index].rank = rank;
			temp2 = temp2->child;
		}
		while (temp2 != NULL);
		assign_crowding_distance_list (new_pop, cur->child, front_size);
		temp2 = cur->child;
		do
		{
			temp2 = del (temp2);
			temp2 = temp2->child;
		}
		while (cur->child !=NULL);
		rank+=1;
	}
	while (orig->child!=NULL);
	if(orig->child != NULL)
	{
		temp1 = orig->child ;
		del(temp1);
	}
	free (orig);
	free (cur);
	return;
}

int count_max_rank(population *pop)
{
	int maxrank = -1 ;
	for(int i = 0 ; i < popsize ; i++)
		if(pop->ind[i].rank >= maxrank)
			maxrank = pop->ind[i].rank ;
	return maxrank ;
}
