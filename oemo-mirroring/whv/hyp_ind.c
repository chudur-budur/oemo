/*===========================================================================*
 * hyp_ind.c: implements the unary hypervolume indicator as proposed in
 *    zt1998b Zitzler, E., and Thiele, L. (1998): Multiobjective Optimization
 *            Using Evolutionary Algorithms - A Comparative Case Study.
 *            Parallel Problem Solving from Nature (PPSN-V), 292-301; a more
 *            detailed discussion can be found in
 *  ztlf2003a Zitzler, E., Thiele, L., Laumanns, M., Fonseca, C., and
 *            Grunert da Fonseca, V (2003): Performance Assessment of
 *            Multiobjective Optimizers: An Analysis and Review. IEEE
 *            Transactions on Evolutionary Computation, 7(2), 117-132
 *            as well as its generalization to arbitrary weight distribution
 *            functions in
 *   zbt2007a Zitzler, E., Brockhoff, D., and Thiele, L. (2007): The
 *            Hypervolume Indicator Revisited: On the Design of
 *            Pareto-compliant Indicators Via Weighted Integration.
 *            Conference on Evolutionary Multi-Criterion Optimization
 *            (EMO 2007), volume 4403 of LNCS, pages 862-876, Springer
 *
 *
 * Compile:
 *   gcc -lm -o hyp_ind hyp_ind.c
 *
 * Usage:
 *   hyp_ind [<param_file>] <data_file> <reference_set> <output_file>
 *
 *   <param_file> specifies the name of the parameter file for eps_ind; the
 *     file has the following format:
 *
 *       dim <integer>
 *       obj <+|-> <+|-> ...
 *       method <0|1>
 *       nadir <real> <real> ...
 *       ideal <real> <real> ...
 *       wdf <integer>
 *       hyp_ind_type <integer>
 *       reference_point <real> <real> ...
 *     The first line defines the number of objectives, the second for each
 *     objective whether it is minimized (-) or maximized, the third
 *     line determines whether the hypervolume is calculated relative to
 *     the reference set (1) or not (0). The forth and fifth line gives the
 *     coordinates of the nadir point, and ideal point respectively. Please
 *     ensure that they are conform with the minimization/maximization of
 *     the objectives according to the second line. With the wdf line, one
 *     chooses the underlying weight distribution function (0: usual
 *     hypervolume with constant weight distribution function; 1,2,3: weight
 *     distribution functions as described in zbt2007a.
 *     In addition, if hyp_ind_type == 0 no scaling is performed. Please ensure
 *     that all objective values are in [0,1] if you use other wdfs than 0.
 *     If hyp_ind_type == 1, the usual hypervolume is computed with an added
 *     term, the integral of an additional weight distribution function
 *     near the Pareto-optimal front, i.e., in [0,1] x ... x [0,1]
 *     If hyp_ind_type == 2, the usual hypervolume indicator is computed as
 *     with hyp_ind_type == 0. Furthermore, line integrals of constant weight
 *     distribution functions on the axes are added as described in
 *     zbt2007a (Section and Figure 3).
 *     The last line of the parameter file contains the coordinates of a
 *     reference point only used with the third weight distribution function
 *     (has only an influence iff wdf == 3).
 *
 *     If the parameter file is omitted, the number of objectives is determined
 *     from the data file and it is assumed that all objectives are to be
 *     minimized, that the nadir point is (2.1, 2.1, ..., 2.1), the ideal
 *     point is (0,0,...,0), and that a reference set is given (method=1).
 *
 *   <data_file> specifies a file that contains the output of one or
 *     several runs of a selector/variator pair; the format corresponds to
 *     the one defined in the specification of the PISA monitor program.
 *
 *   <reference_set> is the name of a file that contains the reference set
 *     according to which the indicator values are calculated; the file
 *     format is the same as for the data file.
 *
 *   <output_file> defines the name of the file to which the computed
 *     indicator values are written to.
 *
 * IMPORTANT: In order to make the output of this tool consistent with
 *   the other indicator tools, for method 0 (no reference set) the
 *   negative hypervolume is outputted as indicator value. Thus,
 *   independently of which type of problem (minimization,
 *   maximization, mixed minimization/maximization) and of which type
 *   of method (with or without reference set) one considers, a lower
 *   indicator value corresponds to a better approximation set.
 *
 * Author:
 *   Eckart Zitzler, February 3, 2005 / last update August 9, 2005
 *   Dimo Brockhoff, update on August 10, 2007
 *                   update on July 30, 2008 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "premo_wdfs.h"

#define error(X,Y)  if (X) fprintf(stderr, Y "\n"), exit(1)

#define MAX_LINE_LENGTH  2048 /* maximal length of lines in the files */
#define MAX_STR_LENGTH  256 /* maximal length of strings in the files */

/* Variables from parameter file */
int     dim;     /* number of objectives */
int     *obj;    /* obj[i] = 0 means objective i is to be minimized */
int     method;  /* 0 = no reference set, 1 = with respect to reference set */
double  *nadir;  /* nadir point for hypervolume calculation */
double  *ideal;  /* ideal point for hypervolume calculation */
int     wdf;     /* weight distribution function according to zbt2007a */
int     hyp_ind_type; /* no scaling if =0, usual hypervolume plus wdf based
                    hypervolume in [0,1]^{dim} if =1, usual hypervolume plus
						  additional line integrals on axes if =2*/
double* reference_point; /* reference point for 3rd weight distribution function*/

/* Global internal variables */
double* refPoints; /* needed for hypervolume calculation */

int  dominates(double  *point1, double  *point2, int  no_objectives)
/* returns true if 'point1' dominates 'points2' with respect to the
 * to the first 'no_objectives' objectives
 */
{
	int  i;
	int  better_in_any_objective, worse_in_any_objective;

	better_in_any_objective = 0;
	worse_in_any_objective = 0;
	for (i = 0; i < no_objectives && !worse_in_any_objective; i++)
		if (point1[i] > point2[i])
			better_in_any_objective = 1;
		else if (point1[i] < point2[i])
			worse_in_any_objective = 1;
	return (!worse_in_any_objective && better_in_any_objective);
}

int  weakly_dominates(double  *point1, double  *point2, int  no_objectives)
/* returns true if 'point1' weakly dominates 'points2' with respect to the
 * to the first 'no_objectives' objectives
 */
{
	int  i;
	int  worse_in_any_objective;

	worse_in_any_objective = 0;
	for (i = 0; i < no_objectives &&  !worse_in_any_objective; i++)
		if (point1[i] < point2[i])
			worse_in_any_objective = 1;
	return (!worse_in_any_objective);
}

void  swap(double  *front, int  i, int  j)
{
	int  k;
	double  temp;

	for (k = 0; k < dim; k++)
	{
		temp = front[i * dim + k];
		front[i * dim + k] = front[j * dim + k];
		front[j * dim + k] = temp;
	}
}

int  filter_nondominated_set(double  *front, int  no_points,
                             int  no_objectives)
/* all nondominated points regarding the first 'no_objectives' dimensions
 * are collected; the points 0..no_points-1 in 'front' are
 * considered; the points in 'front' are resorted, such that points
 * [0..n-1] represent the nondominated points; n is returned
 */
{
	int  i, j;
	int  n;

	n = no_points;
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (dominates(&(front[i * dim]), &(front[j * dim]),
			              no_objectives))
			{
				/* remove point 'j' */
				n--;
				swap(front, j, n);
			}
			else if (dominates(&(front[j * dim]), &(front[i * dim]),
			                   no_objectives))
			{
				/* remove point 'i'; ensure that the point copied to index 'i'
				   is considered in the next outer loop (thus, decrement i) */
				n--;
				swap(front, i, n);
				i--;
				break;
			}
			else
				j++;
		}
		i++;
	}
	return n;
}

double  surface_unchanged_to(double  *front, int  no_points, int  objective)
/* calculate next value regarding dimension 'objective'; consider
 * points 0..no_points-1 in 'front'
 */
{
	int     i;
	double  min, value;

	error(no_points < 1, "run-time error");
	min = front[objective];
	for (i = 1; i < no_points; i++)
	{
		value = front[i * dim + objective];
		if (value < min)
			min = value;
	}
	return min;
}

int  reduce_nondominated_set(double  *front, int  no_points, int  objective,
                             double  threshold)
/* remove all points which have a value <= 'threshold' regarding the
 * dimension 'objective'; the points [0..no_points-1] in 'front' are
 * considered; 'front' is resorted, such that points [0..n-1] represent
 * the remaining points; 'n' is returned
 */
{
	int  n;
	int  i;

	n = no_points;
	for (i = 0; i < n; i++)
		if (front[i * dim + objective] <= threshold)
		{
			n--;
			swap(front, i, n);
		}

	return n;
}

double  calc_hypervolume_cubewise(double  *front, double  *refs,
                                  int  no_points, int  no_objectives, double *ref_point)
{
	int     n;
	double  volume, distance;

	volume = 0;
	distance = 0;
	n = no_points;
	refs[no_objectives - 1] = 0.0;
	while (n > 0)
	{
		int     no_nondominated_points;
		double  temp_vol, temp_dist;

		no_nondominated_points = filter_nondominated_set(front, n,
		                         no_objectives - 1);

		temp_dist = surface_unchanged_to(front, n, no_objectives - 1);
		refs[dim + no_objectives - 1] = temp_dist;

		temp_vol = 0;
		if (no_objectives < 3)
		{
			assert(no_nondominated_points > 0);
			refs[0] = 0.0;
			refs[dim] = front[0];
			temp_vol = calc_hypercube_integral(refs, dim, hyp_ind_type, ideal, wdf, ref_point);
		}
		else
			temp_vol = calc_hypervolume_cubewise(front, refs, no_nondominated_points,
			                                     no_objectives - 1, ref_point);
		volume += temp_vol;

		refs[no_objectives - 1] = temp_dist;
		distance = temp_dist;
		n = reduce_nondominated_set(front, n, no_objectives - 1, distance);
	}

	return volume;
}


void scaleObjectiveValuesForMaximization(double *a, int size_a)
/* scales the objective values of all points in 'a' wrt
 * ideal and nadir point such that all objectives are maximized:
 *
 * post:
 * all objective values in 'a' are in [0,|ideal[k]-nadir[k]|]
 * for all objectives k and rescaled for maximization, i.e.,
 * (new) nadir point is always 0^{dim} and (new) ideal point is
 * ideal_old[k]-nadir_old[k] for former maximization objectives k and
 * nadir_old[k]-ideal_old[k] for former minimization objectives k
 */
{
	int  i, k;
	double  temp;

	for (k = 0; k < dim; k++)
	{
		switch (obj[k])
		{
		case 0: /* minimization in objective k */
			nadir[k] = nadir[k] - ideal[k];
			for (i = 0; i < size_a; i++)
			{
				temp = (nadir[k]) - (a[i * dim + k] - ideal[k]);
				error(temp < 0, "error in data or reference set file with 'nadir', 'ideal', or 'obj'\nPlease ensure that nadir and ideal point are set correctly according to maximization/minimization");
				a[i * dim + k] = temp;
			}

			/* re-calculate reference point of wdf '3' relative to given nadir point
			to get maximization in all objectives */
			if (wdf == 3)
			{
				temp = nadir[k] - (reference_point[k] - ideal[k]);
				error(temp < 0, "error in data or reference set file with 'reference_point' or 'obj'");
				reference_point[k] = temp;
			}

			break;

		default: /* maximization in objective k */
			for (i = 0; i < size_a; i++)
			{
				temp = a[i * dim + k] - nadir[k];
				error(temp < 0, "error in data or reference set file with 'nadir', 'ideal', or 'obj'");
				a[i * dim + k] = temp;
			}

			/* re-calculate reference point of wdf '3' relative to given nadir point
			to get maximization in all objectives */
			if (wdf == 3)
			{
				temp = reference_point[k] - nadir[k];
				error(temp < 0, "error in data or reference set file with 'reference_point' or 'obj'");
				reference_point[k] = temp;
			}
			break;
		}

		switch (obj[k])
		{
		case 0:
			/* switch and adjust nadir and ideal point */
			ideal[k] = nadir[k];
			nadir[k] = 0;
			break;
		default:
			/* adjust nadir and ideal point */
			ideal[k] = ideal[k] - nadir[k];
			nadir[k] = 0;
			break;
		}
	}
}

double  calc_ind_value(double  *a, int  size_a)
/* calculates the hypervolume of point set a according to minimzation or
 * maximization of objectives and the ideal and nadir points
 *
 * beforehand, the objective values are re-calculated relatively to
 * the given nadir and ideal point to get maximization in all objectives
 * and objective values between 0 and ideal[k]
 */
{
	/* re-calculate objective values relative to given nadir and ideal point
	   to get maximization in all objectives and objective values between 0 and ideal[k] */
	scaleObjectiveValuesForMaximization(a, size_a);

	/* calculate indicator values */
	return calc_hypervolume_cubewise(a, refPoints, size_a, dim , reference_point);
}

void  read_params(FILE  *fp)
{
	char str[MAX_STR_LENGTH];
	int  i;

	fscanf(fp, "%s", str);
	error(strcmp(str, "dim") != 0, "error in parameter file while reading 'dim'");
	fscanf(fp, "%d", &dim);
	error(dim <= 0, "error in parameter file");
	obj = chk_malloc(dim * sizeof(int));
	nadir = chk_malloc(dim * sizeof(double));
	ideal = chk_malloc(dim * sizeof(double));
	reference_point = chk_malloc( dim * sizeof(double) );

	error(obj == NULL || nadir == NULL || reference_point == NULL, "memory overflow");

	fscanf(fp, "%s", str);
	error(strcmp(str, "obj") != 0, "error in parameter file while reading 'obj'");
	for (i = 0; i < dim; i++)
	{
		fscanf(fp, "%s", str);
		error(str[0] != '-' && str[0] != '+', "error in parameter file while reading 'obj'");
		if (str[0] == '-')
			obj[i] = 0;
		else
			obj[i] = 1;
	}

	fscanf(fp, "%s", str);
	error(strcmp(str, "method") != 0, "error in parameter file while reading 'method''");
	fscanf(fp, "%d", &method);
	error(method != 0 && method != 1, "error in parameter file 'method' not in {0,1}");

	fscanf(fp, "%s", str);
	error(strcmp(str, "nadir") != 0, "error in parameter file while reading 'nadir'");
	for (i = 0; i < dim; i++)
		error(fscanf(fp, "%lf", &(nadir[i])) != 1, "error in parameter file  while reading 'nadir'");

	fscanf(fp, "%s", str);
	error(strcmp(str, "ideal") != 0, "error in parameter file while reading 'ideal'");
	for (i = 0; i < dim; i++)
		error(fscanf(fp, "%lf", &(ideal[i])) != 1, "error in parameter file  while reading 'ideal'");

	fscanf(fp, "%s", str);
	error(strcmp(str, "wdf") != 0, "error in parameter file while reading 'wdf'");
	fscanf(fp, "%d", &wdf);
	error(wdf < 0 || wdf > 3, "wdf <0 and >3 not implemented!");

	fscanf(fp, "%s", str);
	error(strcmp(str, "hyp_ind_type") != 0, "error in parameter file while reading hyp_ind_type");
	fscanf(fp, "%d", &hyp_ind_type);
	error(hyp_ind_type < 0, "hyp_ind_type has to be greater than 0");

	fscanf(fp, "%s", str);
	error(strcmp(str, "reference_point") != 0, "error in parameter file while reading 'reference_point'");
	for (i = 0; i < dim; i++)
		error(fscanf(fp, "%lf", &(reference_point[i])) != 1, "error in parameter file while reading 'reference_point'");
}

void  check_file(FILE  *fp, int  *no_runsp, int  *max_pointsp)
/* determines the maximum number of points and the number of runs
 * for the data resp. the reference set file
 */
{
	char  line[MAX_STR_LENGTH];
	int  i, j;
	int  new_run;
	int  no_points;
	double  number;

	no_points = 0;
	*max_pointsp = 0;
	*no_runsp = 0;
	new_run = 1;
	while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
	{
		if (sscanf(line, "%lf", &number) != 1)
			new_run = 1;
		else
		{
			if (new_run == 1)
			{
				(*no_runsp)++;
				if (*max_pointsp < no_points)
					*max_pointsp = no_points;
				no_points = 0;
			}
			new_run = 0;
			i = 0;
			for (j = 1; j < dim; j++)
			{
				while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
					i++;
				error(sscanf(&(line[i]), "%lf", &number) <= 0,
				      "error in data or reference set file");
				while (line[i] == ' ' && line[i] != '\0')
					i++;
			}
			no_points++;
		}
	}
	if (*max_pointsp < no_points)
		*max_pointsp = no_points;
}

int  determine_dim(FILE  *fp)
{
	char  line[MAX_STR_LENGTH];
	int  i, no_obj;
	int  line_found, number_found;
	double  number;

	no_obj = 0;
	line_found = 0;
	while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && !line_found)
		line_found = sscanf(line, "%lf", &number);
	if (line_found)
	{
		i = 0;
		do
		{
			no_obj++;
			while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
				i++;
			number_found = sscanf(&(line[i]), "%lf", &number);
			while (line[i] == ' ' && line[i] != '\0')
				i++;
		}
		while (number_found == 1);
	}

	return no_obj;
}

void  read_file(FILE  *fp, int  *no_pointsp, double  *points)
{
	char  line[MAX_STR_LENGTH];
	int  i, j, k;
	int  reading;
	double  number;

	k = 0;
	reading = 0;
	*no_pointsp = 0;
	while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
	{
		if (sscanf(line, "%lf", &number) != 1)
		{
			if (reading)
				break;
		}
		else
		{
			reading = 1;
			points[k++] = number;
			i = 0;
			for (j = 1; j < dim; j++)
			{
				while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
					i++;
				error(sscanf(&(line[i]), "%lf", &number) <= 0,
				      "error in data or reference set file");
				points[k++] = number;
				while (line[i] == ' ' && line[i] != '\0')
					i++;
			}
			(*no_pointsp)++;
		}
	}
}

void free_all()
{
	chk_free( obj );
	chk_free( refPoints );
	chk_free( nadir );
	chk_free( ideal );
	chk_free( reference_point );
}

int  main(int  argc, char  *argv[])
{
	int  i;
	int  no_runs;        /* number of runs */
	int  max_points;    /* maximum number of points per run */
	int  ref_set_size;  /* number of points in the reference set */
	int  curr_run_size; /* number of points associated with the current run */
	double  *ref_set;   /* reference set */
	double  *curr_run;  /* objective vectors fur current run */
	double  ref_set_value;
	double  ind_value;
	FILE  *fp, *out_fp;

	error(argc != 4 && argc != 5,
	      "Hypervolume indicator - wrong number of arguments:\n"
	      "hyp_ind parFile datFile refSet outFile");

	/* set parameters */
	if (argc == 5)
	{
		fp = fopen(argv[1], "r");
		error(fp == NULL, "parameter file not found");
		read_params(fp);
		fclose(fp);
	}
	else
	{
		fp = fopen(argv[1], "r");
		error(fp == NULL, "data file not found");
		dim = determine_dim(fp);
		error(dim < 1, "error in data file-2");
		fclose(fp);
		obj = chk_malloc(dim * sizeof(int));
		nadir = chk_malloc(dim * sizeof(double));
		ideal = chk_malloc(dim * sizeof(double));
		error(obj == NULL || nadir == NULL || ideal == NULL, "memory overflow");
		for (i = 0; i < dim; i++)
		{
			obj[i] = 0;
			nadir[i] = 2.1;
			ideal[i] = 0.0;
		}
		method = 1;
	}

	refPoints = chk_malloc(dim * sizeof(double) * 2);

	/* read reference set */
	if (method == 1)
	{
		if (argc == 5)
			fp = fopen(argv[3], "r");
		else
			fp = fopen(argv[2], "r");
		error(fp == NULL, "reference set file not found");
		check_file(fp, &no_runs, &max_points);
		error(no_runs != 1 || max_points < 1, "error in reference set file");
		ref_set = chk_malloc(dim * max_points * sizeof(double));
		error(ref_set == NULL, "memory overflow");
		rewind(fp);
		read_file(fp, &ref_set_size, ref_set);
		fclose(fp);
		no_runs = 0;
		max_points = 0;
		/* scale objective values of reference points according to
		   ideal and nadir point to get maximization in all objectives */
		ref_set_value = calc_ind_value(ref_set, ref_set_size);
	}
	else
	{
		ref_set = NULL;
		ref_set_size = 0;
	}
	/* check data file */
	if (argc == 5)
		fp = fopen(argv[2], "r");
	else
		fp = fopen(argv[1], "r");
	error(fp == NULL, "data file not found");
	check_file(fp, &no_runs, &max_points);
	error(no_runs < 1 || max_points < 1, "error in data file-1");
	curr_run = chk_malloc(dim * max_points * sizeof(double));
	rewind(fp);

	/* process data */
	if (argc == 5)
		out_fp = fopen(argv[4], "w");
	else
		out_fp = fopen(argv[3], "w");
	error(out_fp == NULL, "output file could not be generated");
	while (no_runs > 0)
	{
		read_file(fp, &curr_run_size, curr_run);

		ind_value = calc_ind_value(curr_run, curr_run_size);
		if (method == 1)
			fprintf(out_fp, "%.9e\n", ref_set_value - ind_value);
		else
			fprintf(out_fp, "%.9e\n", -ind_value);
		no_runs--;
	}
	fclose(out_fp);
	fclose(fp);

	chk_free( ref_set );
	chk_free( curr_run );
	free_all();
	return 0;
}
