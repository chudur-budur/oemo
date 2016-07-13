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
#include "extremes.h"
#include "poplist.h"
#include "misc.h"
#include "vecutils.h"

#define debug 0
#define showmap 0

pop_list *e_star ;
int popsize ;
int op_popsize ;
char prob_name[16] ;
int nobj ;
int nreal ;

int init_extreme_pts_hardcoded(void)
{
	double **extremes ;
	int feval = 0, i;
	individual ind ;
	extremes = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++) extremes[i] = (double*)malloc(sizeof(double) * nreal);
	
	if(strcmp(prob_name, "zdt1") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt1_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "zdt2") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt2_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "zdt3") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt3_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "zdt4") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt4_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "zdt6") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt6_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "pol") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &pol_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "osy") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &osy_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz1") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz1_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz2") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz2_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz3") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz3_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz4") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz4_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz5") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz5_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz6") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz6_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz7") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz7_extremes[i], sizeof(double) * nreal);
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
	individual ind ;
	extremes = (double**)malloc(sizeof(double*) * nobj);
	for(i = 0 ; i < nobj ; i++) extremes[i] = (double*)malloc(sizeof(double) * nreal);
	
	if(strcmp(prob_name, "zdt4") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &zdt4_weak_extremes[i], sizeof(double) * nreal);
	else if(strcmp(prob_name, "dtlz1") == 0)
		for(i = 0 ; i < nobj ; i++)
			memcpy(extremes[i], &dtlz1_weak_extremes[i], sizeof(double) * nreal);
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

int init_extreme_pts_from_file(void)
{
	FILE *fp ;
	char nadir_path[LINECHARS];
	int i, j, k, lines, token_count, feval ; char *line = NULL ;
	size_t len = 0 ; ssize_t read ;
	double **vals ; int index ;
	individual *ind ;
	sprintf(nadir_path, "chimps/%s-chimps.out", prob_name);
	fprintf(stdout, "\n*********** loading from file: %s\n", nadir_path);
	lines = count_lines(nadir_path);
	vals = (double**)malloc(sizeof(double*) * lines);
	fp = open_file(nadir_path, "r");
	i = 0 ;
	while((read = getline(&line, &len, fp)) != -1)
	{
		token_count = count_tokens(line);
		vals[i] = (double*)malloc(sizeof(double) * token_count);
		parse_double_array(line, vals[i]);
		i++ ;
	}
	free(line);
	fclose(fp);
	index = 2 * rnd(0, lines/nobj );
	fprintf(stdout, "\nindex: %d\n", index);
	ind = (individual*)malloc(sizeof(individual) * nobj);
	feval = 0 ;
	for(i = index, k = 0 ; i < index + nobj ; i++, k++)
	{
		allocate_memory_ind(&ind[k]); initialize_ind_dummy(&ind[k]);
		for(j = 0 ; j < nreal ; j++) ind[k].xreal[j] = vals[i][j];
		push_back(e_star, &ind[k]);
		feval += ((int)vals[i][(nreal + nobj)]);
	}
	free(ind);
	/* free the array */
	for(i = 0 ; i < lines ; i++) free(vals[i]) ;
	free(vals);
	fprintf(stdout, "feval: %d, e_star:\n", feval);
	dump_pop_list(stdout, e_star);
	return feval ;
}

int init_extreme_pts_from_file_weighted(void)
{
	/* not done yet */
	FILE *fp ;
	char nadir_path[LINECHARS];
	int i, j, k, lines, token_count, feval ; char *line = NULL ;
	size_t len = 0 ; ssize_t read ;
	double **vals ; int index ;
	individual *ind ;
	sprintf(nadir_path, "chimps/%s-chimps.out", prob_name);
	fprintf(stdout, "\n*********** loading from file: %s\n", nadir_path);
	lines = count_lines(nadir_path);
	vals = (double**)malloc(sizeof(double*) * lines);
	fp = open_file(nadir_path, "r");
	i = 0 ;
	while((read = getline(&line, &len, fp)) != -1)
	{
		token_count = count_tokens(line);
		vals[i] = (double*)malloc(sizeof(double) * token_count);
		parse_double_array(line, vals[i]);
		i++ ;
	}
	free(line);
	fclose(fp);
	index = 2 * rnd(0, lines/nobj );
	fprintf(stdout, "\nindex: %d\n", index);
	ind = (individual*)malloc(sizeof(individual) * nobj);
	feval = 0 ;
	for(i = index, k = 0 ; i < index + nobj ; i++, k++)
	{
		allocate_memory_ind(&ind[k]); initialize_ind_dummy(&ind[k]);
		for(j = 0 ; j < nreal ; j++) ind[k].xreal[j] = vals[i][j];
		push_back(e_star, &ind[k]);
		feval += ((int)vals[i][(nreal + nobj)]);
	}
	free(ind);
	/* free the array */
	for(i = 0 ; i < lines ; i++) free(vals[i]) ;
	free(vals);
	fprintf(stdout, "feval: %d, e_star:\n", feval);
	dump_pop_list(stdout, e_star);
	return feval ;
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
		/*get_furthest_point_from_m_random_select(pool, nobj, ptr->ind->xreal, t);*/
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
