/*========================================================================
  PISA  (www.tik.ee.ethz.ch/pisa/)
  ========================================================================
  Computer Engineering (TIK)
  ETH Zurich
  ========================================================================
  PREMO - Preference-based Multiobjective Optimizer

  Implements the different weight distribution functions as described in
  the EMO2007 paper zbt2007a.

  file: premo_wdfs.c
  authors: Dimo Brockhoff, brockho@tik.ee.ethz.ch

  revision by: ---
  last change: August 10, 2007
  ========================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "premo_wdfs.h"

double get_dist(double *x, double *y, int dim)
/* computes the euclidian distance between x and y in dim-dimensional
 * space. */
{
	double ret;
	int i;

	ret = 0;
	for (i=0; i<dim; i++)
	{
		ret+= (x[i] - y[i])*(x[i] - y[i]);
	}
	ret = sqrt(ret);

	return ret;
}

double get_cutting_points(double *hypercubepoints, double *linestart,
                          double *lineend, int dim)
/* auxiliary function used in calc_hypercube_integral2(...) */
{
	int  i;
	int j;
	double s;

	for (i = 0; i < dim; i ++)
	{
		/* no intersection with hypercube */
		if ((linestart[i] < hypercubepoints[i] && lineend[i] < hypercubepoints[i])
		        || (linestart[i] > hypercubepoints[dim+i] && lineend[i] > hypercubepoints[dim+i]) )
		{
			for(j=0; j<dim; j++)
			{
				linestart[j] = 0.0;
				lineend[j] = 0.0;
			}
			return 0;
		}

		/* possible intersection with hypercube in dimension i */
		/*  a) with first hyperplane */
		if (linestart[i] < hypercubepoints[i] && lineend[i] >= hypercubepoints[i])
		{
			s = (hypercubepoints[i]-linestart[i])/(lineend[i]-linestart[i]);
			for (j=0; j < dim; j++)
			{
				linestart[j] = linestart[j] + s*(lineend[j]-linestart[j]);
			}
		}
		/*  b) with second hyperplane */
		if (lineend[i] > hypercubepoints[dim+i]
		        && linestart[i] <= hypercubepoints[dim+i])
		{
			s = (lineend[i]-hypercubepoints[dim+i])/(lineend[i]-linestart[i]);
			for (j=0; j < dim; j++)
			{
				lineend[j] = lineend[j] - s*(lineend[j]-linestart[j]);
			}
		}
	}
	/* return 1 if intersection between line and hypercube is not empty */
	return 1;
}

double hypervolume(double  *refs, int dim)
/* Usual hypervolume */
{
	int  i;
	double  volume;

	/* calculate hypervolume */
	volume = 1.0;
	for (i = 0; i < dim; i ++)
	{
		volume *= refs[dim + i] - refs[i];
	}

	return volume;
}

double calc_hypercube_integral1(double  *refs, int dim)
/* This is weight distribution function 1 from
 * EMO2007 paper zbt2007a, final version
 *
 * IMPORTANT: This wdf only works if dim == 2.
 */
{
	double  volume;
	double  x1;
	double  x2;
	double  y1;
	double  y2;

	/* only works as a 2D indicator */
	assert( dim == 2 );

	/* get corners of 2D hypercube the integral of which */
	/* is sought */
	x1 = refs[0];
	y1 = refs[1];
	x2 = refs[2];
	y2 = refs[3];

	/* compute integral to go to extreme points */
	volume = (exp(x2*20)-exp(x1*20))*(y2-y1)/exp(20);
	volume += (exp(y2*20)-exp(y1*20))*(x2-x1)/exp(20);

	return volume;
}

double calc_hypercube_integral2(double  *refs, int dim)
/* This is weight distribution function 2 from
 * EMO2007 paper zbt2007a, final version
 *
 * --> with maximization: go to y-axis,
 *     plus one point with maximal x-value
 *
 * IMPORTANT: This wdf only works if dim == 2.
 */
{
	double volume;
	/* starting point (x[0],x[1],...,x[dim-1]) and end point
		(y[0],y[1],...,y[dim-1]) of the straight line on which
		a constant dirac function with constant "dirac" is defined */
	double *x;
	double *y;

	x = chk_malloc(sizeof(double) * dim);
	y = chk_malloc(sizeof(double) * dim);

	/* only works as a 2D indicator */
	assert( dim == 2 );

	volume = 0.0;

	/* integral for exponential wdf */
	volume += (exp(refs[3]*20)-exp(refs[1]*20))*(refs[2]-refs[0])/exp(20);

	/* set reference line (0,0)-->(1,0) */
	x[0] = 0;
	x[1] = 0;
	y[0] = 1;
	y[1] = 0;

	/* add line integral on dirac like weight distribution function */
	get_cutting_points(refs, x, y, dim);
	volume += 400*get_dist(x,y,dim);

	free(x);
	free(y);

	return volume;
}

double calc_integral_wdf3(double c, double d)
/* Calculates the integral
 * int_{(-1,-1)}^{(c,d)} wdf3(x,y) dxdy
 *
 * with wdf3(x,y)= (2-(x^2 + y^2))/(0.01+(x-y)^2)
 *
 * pre: x>-1, y>-1, x<1, y<1
 * post: return correct integral
 *       1/300 (-400(1+c)(1+d)+(4030+6030c-2000c^3)*atan(10(1+c)) +
 *              10(-603c+200c^3+603d-200d^3)*atan(10(c-d)^2) -
 *             (-151+150c^2)*log(101+100c(2+c)) +
 *             301*log(1+100(c-d)^2)-150c^2*log(1+100(c-d)^2) -
 *             151*log(101+100d(2+d)) +
 *             10((403+603d-200d^3)*atan(10(1+d)) +
 *             15d^3(-log(1+100(c-d)^2) + log(101+100d(2+d)))))
 */
{
	double integral;

	assert(c >= -1);
	assert(d >= -1);

	integral = -400*(1+c)*(1+d)+(4030+6030*c-2000*c*c*c)*atan(10*(1+c));
	integral += 10*(-603*c+200*c*c*c+603*d-200*d*d*d)*atan(10*(c-d));
	integral += (-151+150*c*c)*log(101+100*c*(2+c));
	integral += 301*log(1+100*(c-d)*(c-d))-150*c*c*log(1+100*(c-d)*(c-d));
	integral -= 151*log(101+100*d*(2+d));
	integral += 10*((403+603*d-200*d*d*d)*atan(10*(1+d)) + 15*d*d*(-log(1+100*(c-d)*(c-d)) + log(101+100*d*(2+d))));
	integral = integral/300;

	return integral;
}

double calc_hypercube_integral3(double *refs, int dim, double *refpoint)
/* This is weight distribution function 3 from
 * EMO2007 paper zbt2007a, final version, and
 * submitted version respectively
 *
 * --> ridge to reference point (a,b), given in array refpoint
 *
 *
 * This 2D wdf yields an indicator with convex
 * equipotential lines the knees of which are sharp
 * and lying on a diagonal line
 *
 * wdf = low constant + ridge in [-1,1]x[-1,1]
 *       on diagonal with maximum at (refpoint[0], refpoint[1])
 *
 * IMPORTANT: This wdf only works if dim == 2.
 */
{

	double  volume;
	double  x1;
	double  x2;
	double  y1;
	double  y2;
	double x1_t;
	double y1_t;
	double x2_t;
	double y2_t;
	double vol1;
	double vol2;
	double vol3;
	double vol4;
	double  c = 1000;  /* scaling factor */

	/* only works as a 2D indicator */
	assert( dim == 2 );
	assert( refpoint[0] > 0 );
	assert( refpoint[1] > 0 );

	/* get corners of 2D hypercube the integral of which
	   is sought */
	x1 = refs[0];
	y1 = refs[1];
	x2 = refs[2];
	y2 = refs[3];

	assert( x1 < (x2+0.000001) );
	assert( y1 < (y2+0.000001) );

	/* compute indicator with ridge on (0.5,0.4) */

	/* transform hypercube from [0,1]x[0,1] to [-2,2]x[-2,2] */
	x1_t = 2*(x1-refpoint[0]);
	y1_t = 2*(y1-refpoint[1]);
	x2_t = 2*(x2-refpoint[0]);
	y2_t = 2*(y2-refpoint[1]);

	/* clip hypercube to [-1,1]x[-1,1] */
	if (x1_t < -1)
		x1_t = -1;
	else if (x1_t > 1)
		x1_t = 1;

	if (y1_t < -1)
		y1_t = -1;
	else if (x1_t > 1)
		y1_t = 1;

	if (x2_t < -1)
		x2_t = -1;
	else if (x1_t > 1)
		x2_t = 1;

	if (y2_t < -1)
		y2_t = -1;
	else if (x1_t > 1)
		y2_t = 1;

	/* compute integral on clipped hypercube */

	vol1 = calc_integral_wdf3(x2_t, y2_t);
	vol2 = calc_integral_wdf3(x1_t, y1_t);
	vol3 = calc_integral_wdf3(x1_t, y2_t);
	vol4 = calc_integral_wdf3(x2_t, y1_t);

	volume = 100*(vol1 - vol3 -vol4 + 2*vol2);

	/* compute integral when not at the coordinate axes */
	volume += (x1-x2)*(y1-y2)*(x1+x2+y1+y2)/(2*c);

	return volume;

}

double compute_integral(double *refs, int wdf, int dim, double *ref_point)
{
	double volume=0;

	switch (wdf)
	{
		/* This is wdf 1 from EMO2007 paper zbt2007a */
		/*           stress on corner points            */
	case 1:
		volume = calc_hypercube_integral1(refs, dim);
		break;
	case 2:
		/* This is wdf 2 from EMO2007 paper zbt2007a */
		/*       stress on x-axis plus additional       */
		/*           weighted line on y-axis            */
		volume = calc_hypercube_integral2(refs, dim);
		break;
	case 3:
		/* This is wdf 3 from EMO2007 paper zbt2007a */
		/*          reference point on diagonal         */
		volume = calc_hypercube_integral3(refs, dim, ref_point);
		break;
	default:
		/*original hypervolume*/
		volume = hypervolume(refs, dim);
		break;
	}
	return volume;
}

double  calc_hypercube_integral(double  *refs, int dim, int hyp_ind_type, double *ideal,
                                int wdf, double *ref_point )
/* calculates the hypervolume of the points in 'refs' according to
 * specified weight distribution function in 'wdf'
 */
{

	double  volume;
	/* factor, the wdf near front is larger than maximal hypervolume on entire
		search space when hyp_ind_type == 1 */
	double factor;
	double *scaledrefs;
	int i,j;
	int scalingnecessary;

	scaledrefs = chk_malloc(sizeof(double) * dim * 2);
	/* initialize factor: */
	factor = 1.0;
	for (i=0; i<dim; i++)
	{
		factor *= ideal[i];
	}

	/* get deep copy of hypercube's reference points, the integral
		of which is sought */
	for (i=0; i<2*dim; i++)
	{
		scaledrefs[i] = refs[i];
	}

	volume = 0.0;

	if (hyp_ind_type == 0)
	{
		/* usual hypervolume on entire search space */
		volume = hypervolume(scaledrefs, dim);
	}

	/* if hyp_ind_type == 1:
			- compute usual hypervolume of hypercube
			- add integral of additional weight distribution function
				near Pareto-optimal front, here in [0,1] x ... x [0,1]
	*/
	if (hyp_ind_type == 1)
	{
		/* add hypervolume on entire search space */
		volume = hypervolume(scaledrefs, dim);

		/* scale points for additional wdf near Pareto-optimal front
		   ------------------------------------------------------------ */

		/* scaling is necessary if second point lies in hypercube
			[(ideal[0]-1),ideal[0]] x [(ideal[1]-1),ideal[1]] x ... x [(ideal[dim-1]-1)-ideal[dim-1]] */
		scalingnecessary = 0;
		for (i=0; i<dim; i++)
		{
			if (scaledrefs[dim+i] >= (ideal[i]-1.0))
			{
				scalingnecessary = 1;
				break;
			}
		}

		if (scalingnecessary)
		{
			/* if scaling is necessary, translate reference points
				to [0,1] x [0,1] x ... x [0,1] and cut - if necessary -
				on bounding box of this hypercube */
			for (i=0; i<dim; i++)
			{
				scaledrefs[i] = scaledrefs[i] - (ideal[i]-1.0);
			}
			for (i=dim; i<2*dim; i++)
			{
				scaledrefs[i] = scaledrefs[i] - (ideal[i-dim]-1.0);
			}
			for (i=0; i<dim; i++)
			{
				if (scaledrefs[i] < 0)
				{
					scaledrefs[i] = 0;
				}
			}
		}
		else
		{
			for (i=0; i<2*dim; i++)
			{
				scaledrefs[i] = 0;
			}
		}


		/* compute integral of additional weight distribution function
			near Pareto-optimal front */
		volume += factor * compute_integral(scaledrefs, wdf, dim, ref_point);

	}

	/* if hyp_ind_type == 2:
			- compute usual indicator for hypercube
			   Please ensure that the points are already scaled to
				[0,1] x [0,1] before
			- add line integrals of constant weight distribution functions
				on the axes
	*/
	if (hyp_ind_type == 2)
	{
		/* compute integral of additional weight distribution function
			near Pareto-optimal front */
		volume = compute_integral(scaledrefs, wdf, dim, ref_point);

		/* add weight distibution function on axis */
		for (i = 0; i < dim; i ++)
		{
			if (scaledrefs[i] == 0.0)
			{
				double  tempVol = 1.0;
				for (j = 0; j < dim; j++)
					if (j != i)
						tempVol *= scaledrefs[dim + j] - scaledrefs[j];
				volume += tempVol;
			}
		}
	}

	free(scaledrefs);

	return volume;
}

void* chk_malloc(size_t size)
/* Wrapper function for malloc(). Checks for failed allocations. */
{
	void *return_value = malloc(size);
	if (return_value == NULL)
	{
		fprintf(stderr, "Selector: Out of memory.");
	}
	return (return_value);
}

void chk_free( void* pointer )
{
	if( pointer != NULL )
	{
		free( pointer );
	}
}
