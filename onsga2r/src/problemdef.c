/* Test problem definitions */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <float.h>

# include "global.h"
# include "problemdef.h"
# include "rand.h"
#include "vecutils.h"

char prob_name[16] ;

/*  Test problem SCH1
    # of real variables = 1
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void sch1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = pow(xreal[0],2.0);
	obj[1] = pow((xreal[0]-2.0),2.0);
	return;
}

/*  Test problem SCH2
    # of real variables = 1
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void sch2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	if (xreal[0]<=1.0)
	{
		obj[0] = -xreal[0];
		obj[1] = pow((xreal[0]-5.0),2.0);
		return;
	}
	if (xreal[0]<=3.0)
	{
		obj[0] = xreal[0]-2.0;
		obj[1] = pow((xreal[0]-5.0),2.0);
		return;
	}
	if (xreal[0]<=4.0)
	{
		obj[0] = 4.0-xreal[0];
		obj[1] = pow((xreal[0]-5.0),2.0);
		return;
	}
	obj[0] = xreal[0]-4.0;
	obj[1] = pow((xreal[0]-5.0),2.0);
	return;
}

/*  Test problem FON
    # of real variables = n
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void fon (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double s1, s2;
	int i;
	s1 = s2 = 0.0;
	for (i=0; i<nreal; i++)
	{
		s1 += pow((xreal[i]-(1.0/sqrt((double)nreal))),2.0);
		s2 += pow((xreal[i]+(1.0/sqrt((double)nreal))),2.0);
	}
	obj[0] = 1.0 - exp(-s1);
	obj[1] = 1.0 - exp(-s2);
	return;
}

/*  Test problem KUR
    # of real variables = 3
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void kur (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i;
	double res1, res2;
	res1 = -0.2*sqrt((xreal[0]*xreal[0]) + (xreal[1]*xreal[1]));
	res2 = -0.2*sqrt((xreal[1]*xreal[1]) + (xreal[2]*xreal[2]));
	obj[0] = -10.0*( exp(res1) + exp(res2));
	obj[1] = 0.0;
	for (i=0; i<3; i++)
	{
		obj[1] += pow(fabs(xreal[i]),0.8) + 5.0*sin(pow(xreal[i],3.0));
	}
	return;
}

/*  Test problem POL
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void pol (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double a1, a2, b1, b2;
	a1 = 0.5*sin(1.0) - 2.0*cos(1.0) + sin(2.0) - 1.5*cos(2.0);
	a2 = 1.5*sin(1.0) - cos(1.0) + 2.0*sin(2.0) - 0.5*cos(2.0);
	b1 = 0.5*sin(xreal[0]) - 2.0*cos(xreal[0]) + sin(xreal[1]) - 1.5*cos(xreal[1]);
	b2 = 1.5*sin(xreal[0]) - cos(xreal[0]) + 2.0*sin(xreal[1]) - 0.5*cos(xreal[1]);
	obj[0] = 1.0 + pow((a1-b1),2.0) + pow((a2-b2),2.0);
	obj[1] = pow((xreal[0]+3.0),2.0) + pow((xreal[1]+1.0),2.0);
	return;
}

/*  Test problem VNT
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 3
    # of constraints = 0
    */
void vnt (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = 0.5*(xreal[0]*xreal[0] + xreal[1]*xreal[1]) + sin(xreal[0]*xreal[0] + xreal[1]*xreal[1]);
	obj[1] = (pow((3.0*xreal[0] - 2.0*xreal[1] + 4.0),2.0))/8.0 + (pow((xreal[0]-xreal[1]+1.0),2.0))/27.0 + 15.0;
	obj[2] = 1.0/(xreal[0]*xreal[0] + xreal[1]*xreal[1] + 1.0) - 1.1*exp(-(xreal[0]*xreal[0] + xreal[1]*xreal[1]));
	return;
}

/*  Test problem ZDT1
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double f1, f2, g, h;
	int i;
	f1 = xreal[0] ;
	g = 0.0;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for (i=1; i<nreal; i++)  g += xreal[i] ;*/
	/* for(i = 1 ; i < nreal ; i++) g += (xreal[i] - 0.5) * (xreal[i] - 0.5); */
	/* for(i = 1 ; i < nreal ; i++) g += sqrt(fabs((xreal[i] - 0.5))) ; */
	for(i = 1 ; i < nreal ; i++) g += fabs((xreal[i] - 0.5)) ;
	g = 9.0 * g / ((double)nreal - 1.0) ;
	g += 1.0 ;
	h = 1.0 - sqrt(f1/g) ;
	f2 = g * h ;
	obj[0] = f1 ;
	obj[1] = f2 ;
	return ;
}

/*  Test problem ZDT2
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double f1, f2, g, h;
	int i;
	f1 = xreal[0] ;
	g = 0.0;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for (i=1; i<nreal; i++) g += xreal[i]; */
	for (i = 1 ; i < nreal ; i++) g += fabs((xreal[i] - 0.5)); 
	g = 9.0 * g / ((double)nreal - 1.0);
	g += 1.0 ;
	h = 1.0 - pow((f1/g), 2.0) ;
	f2 = g * h ;
	obj[0] = f1 ;
	obj[1] = f2 ;
	return ;
}

/*  Test problem ZDT3
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double f1, f2, g, h;
	int i;
	f1 = xreal[0] ;
	g = 0.0;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for (i=1; i<nreal; i++) g += xreal[i];*/
	for (i = 1 ; i < nreal ; i++) g += fabs((xreal[i] - 0.5)); 
	g = 9.0 * g / ((double)nreal - 1.0);
	g += 1.0 ;
	h = 1.0 - sqrt(f1/g) - (f1/g) * sin(10.0 * PI * f1) ;
	f2 = g * h ;
	obj[0] = f1 ;
	obj[1] = f2 ;
	return ;
}

/*  Test problem ZDT4
    # of real variables = 10
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt4 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double f1, f2, g, h;
	int i;
	f1 = xreal[0] ;
	g = 0.0;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for (i=1; i<nreal; i++) 
	 	g += (xreal[i] * xreal[i]) - 10.0 * cos(4.0*PI*xreal[i]); */
	for(i = 1; i < nreal ; i++ ) 
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)) 
			- 10.0 * cos(4.0*PI*(xreal[i] - 0.5)); 
	g += 1.0 + (10.0 * ((double)nreal - 1.0));
	h = 1.0 - sqrt(f1/g);
	f2 = g * h ;
	obj[0] = f1 ;
	obj[1] = f2 ;
	return;
}

/*  Test problem ZDT5
    # of real variables = 0
    # of bin variables = 11
    # of bits for binvar1 = 30
    # of bits for binvar2-11 = 5
    # of objectives = 2
    # of constraints = 0
    */
void zdt5 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j;
	int u[11];
	int v[11];
	double f1, f2, g, h;
	for (i=0; i<11; i++)
	{
		u[i] = 0;
	}
	for (j=0; j<30; j++)
	{
		if (gene[0][j] == 1)
		{
			u[0]++;
		}
	}
	for (i=1; i<11; i++)
	{
		for (j=0; j<4; j++)
		{
			if (gene[i][j] == 1)
			{
				u[i]++;
			}
		}
	}
	f1 = 1.0 + u[0];
	for (i=1; i<11; i++)
	{
		if (u[i] < 5)
		{
			v[i] = 2 + u[i];
		}
		else
		{
			v[i] = 1;
		}
	}
	g = 0;
	for (i=1; i<11; i++)
	{
		g += v[i];
	}
	h = 1.0/f1;
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
	return;
}

/*  Test problem ZDT6
    # of real variables = 10
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt6 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double f1, f2, g, h;
	int i;
	f1 = 1.0 - (exp(-4.0 * xreal[0])) * pow((sin(6.0*PI*xreal[0])), 6.0);
	g = 0.0;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for (i=1; i<nreal; i++) g += xreal[i]; */
	for (i = 1 ; i < nreal ; i++) g += fabs((xreal[i] - 0.5));
	g = g / 9.0 ;
	g = pow(g, 0.25) ;
	g = 1.0 + 9.0 * g ;
	h = 1.0 - pow((f1/g), 2.0) ;
	f2 = g * h ;
	obj[0] = f1 ;
	obj[1] = f2 ;
	return ;
}

/*  Test problem BNH
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void bnh (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = 4.0*(xreal[0]*xreal[0] + xreal[1]*xreal[1]);
	obj[1] = pow((xreal[0]-5.0),2.0) + pow((xreal[1]-5.0),2.0);
	constr[0] = 1.0 - (pow((xreal[0]-5.0),2.0) + xreal[1]*xreal[1])/25.0;
	constr[1] = (pow((xreal[0]-8.0),2.0) + pow((xreal[1]+3.0),2.0))/7.7 - 1.0;
	return;
}

/*  Test problem OSY
    # of real variables = 6
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 6
    */
void osy (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = -(25.0*pow((xreal[0]-2.0),2.0) + pow((xreal[1]-2.0),2.0) 
			+ pow((xreal[2]-1.0),2.0) + pow((xreal[3]-4.0),2.0) 
			+ pow((xreal[4]-1.0),2.0));
	obj[1] = xreal[0]*xreal[0] +  xreal[1]*xreal[1] + xreal[2]*xreal[2] 
		+ xreal[3]*xreal[3] + xreal[4]*xreal[4] + xreal[5]*xreal[5];
	/**
	 *	c1(x) = x1 + x2 - 2 >= 0
	 * -->	(x1+x2) >= 2
	 * -->	(x1+x2)/2 >= 1
	 * -->	(x1+x2)/2 - 1 >= 0
	 */
	constr[0] = (xreal[0]+xreal[1])/2.0 - 1.0;
	/**
	 * 	c2(x) = 6 - x1 - x2 >= 0
	 * -->	-(x1+x2) >= -6
	 * -->	(x1+x2) <= 6
	 * -->	(x1+x2)/6 <= 1
	 * -->	1 >= (x1+x2)/6
	 * -->	1 - (x1+x2)/6 >= 0
	 */
	constr[1] = 1.0 - (xreal[0]+xreal[1])/6.0;
	constr[2] = 1.0 - xreal[1]/2.0 + xreal[0]/2.0;
	constr[3] = 1.0 - xreal[0]/2.0 + 3.0*xreal[1]/2.0;
	constr[4] = 1.0 - (pow((xreal[2]-3.0),2.0))/4.0 - xreal[3]/4.0;
	constr[5] = (pow((xreal[4]-3.0),2.0))/4.0 + xreal[5]/4.0 - 1.0;
	return;
}

/*  Test problem SRN
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void srn (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = 2.0 + pow((xreal[0]-2.0),2.0) + pow((xreal[1]-1.0),2.0);
	obj[1] = 9.0*xreal[0] - pow((xreal[1]-1.0),2.0);
	constr[0] = 1.0 - (pow(xreal[0],2.0) + pow(xreal[1],2.0))/225.0;
	constr[1] = 3.0*xreal[1]/10.0 - xreal[0]/10.0 - 1.0;
	return;
}

/*  Test problem TNK
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void tnk (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = xreal[0];
	obj[1] = xreal[1];
	if (xreal[1] == 0.0)
	{
		constr[0] = -1.0;
	}
	else
	{
		constr[0] = xreal[0]*xreal[0] + xreal[1]*xreal[1] - 0.1*cos(16.0*atan(xreal[0]/xreal[1])) - 1.0;
	}
	constr[1] = 1.0 - 2.0*pow((xreal[0]-0.5),2.0) + 2.0*pow((xreal[1]-0.5),2.0);
	return;
}

/*  Test problem CTP1
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void ctp1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*exp(-obj[0]/g);
	constr[0] = obj[1]/(0.858*exp(-0.541*obj[0]))-1.0;
	constr[1] = obj[1]/(0.728*exp(-0.295*obj[0]))-1.0;
	return;
}

/*  Test problem CTP2
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = -0.2*PI;
	a = 0.2;
	b = 10.0;
	c = 1.0;
	d = 6.0;
	e = 1.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP3
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = -0.2*PI;
	a = 0.1;
	b = 10.0;
	c = 1.0;
	d = 0.5;
	e = 1.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP4
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp4 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = -0.2*PI;
	a = 0.75;
	b = 10.0;
	c = 1.0;
	d = 0.5;
	e = 1.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP5
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp5 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = -0.2*PI;
	a = 0.1;
	b = 10.0;
	c = 2.0;
	d = 0.5;
	e = 1.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP6
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp6 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = 0.1*PI;
	a = 40.0;
	b = 0.5;
	c = 1.0;
	d = 2.0;
	e = -2.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP7
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp7 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	theta = -0.05*PI;
	a = 40.0;
	b = 5.0;
	c = 1.0;
	d = 6.0;
	e = 0.0;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	return;
}

/*  Test problem CTP8
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void ctp8 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double g;
	double theta, a, b, c, d, e;
	double exp1, exp2;
	g = 1.0 + xreal[1];
	obj[0] = xreal[0];
	obj[1] = g*(1.0  - sqrt(obj[0]/g));
	theta = 0.1*PI;
	a = 40.0;
	b = 0.5;
	c = 1.0;
	d = 2.0;
	e = -2.0;
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[0] = exp1/exp2 - 1.0;
	theta = -0.05*PI;
	a = 40.0;
	b = 2.0;
	c = 1.0;
	d = 6.0;
	e = 0.0;
	exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
	exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
	exp2 = b*PI*pow(exp2,c);
	exp2 = fabs(sin(exp2));
	exp2 = a*pow(exp2,d);
	constr[1] = exp1/exp2 - 1.0;
	return;
}

/**  
 *  Test problem DTLZ1 (suggested k = 5)
 *  # of objectives = M = 3
 *  # of real variables = n = M + k - 1 = 3 + 5 - 1 = 7
 *  # of bin variables = 0
 *  # of constraints = 0
 *  harder: 96 variables
 **/
void dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g ;

	k = nreal - nobj + 1; /* k = 12 - 3 + 1 = 10 */

	/** 
	 * this is ok, no need to change xreal, 
	 * since it is already done in the actual problem.
	 */
	g = 0.0 ;
	for(i = nreal - k; i < nreal ; i++) /* i = 12 - 10 = 2 ; i < 12 ; i++ */
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5))
		     - cos(20.0 * PI *  (xreal[i] - 0.5)) ;
	g = 100.0 * (k + g);

	for(i = 0 ; i < nobj ; i++) obj[i] = (1.0 + g) * 0.5 ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0; j < nobj - (i+1); j++) obj[i] *= xreal[j];
		if(i != 0) obj[i] *= 1.0 - xreal[nobj - (i + 1)];
	}
	return ;
}

/**
 * Test problem DTLZ2 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: 96 variables
 **/
void dtlz2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g ;

	k = nreal - nobj + 1;

	g = 0.0 ;
	/* sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i) */
	/* for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)); */
	for(i = nreal - k ; i < nreal ; i++)
		g += fabs(xreal[i] - 0.5);
	for(i = 0 ; i < nobj ; i++) obj[i] = 1.0 + g ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(xreal[j] * 0.5 * PI) ;
		if(i != 0)
			obj[i] *= sin(xreal[nobj - (i+1)] * 0.5 * PI);
	}
	return ;
}

/**
 * Test problem DTLZ3 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: 96 variables
 **/
void dtlz3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k;
	double g ;

	k = nreal - nobj + 1;

	/**
	 * in the acutal problem definision, x_i - 0.5 was
	 * already done, so no need to make any adjustments.
	 */
	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5))
		     - cos(20.0 * PI *  (xreal[i] - 0.5)) ;
	g = 100.0 * (k + g);

	for(i = 0 ; i < nobj ; i++)
		obj[i] = (1.0 + g) ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(xreal[j] * 0.5 * PI);
		if(i != 0)
			obj[i] *= sin(xreal[nobj - (i+1)] * 0.5 * PI);
	}
	return ;
}

/**
 * Test problem DTLZ4 (suggested k = 10, alpha = 100)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: same problem
 **/
void dtlz4 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g ;
	/* suggested alpha */
	double alpha = 100.0 ;

	k = nreal - nobj + 1;

	/**
	 * the original problem already does x_i - 0.5,
	 * so no adjustment is required.
	 */
	g = 0.0 ;
	/* for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)) ; */
	/* but this adjustment may make nsga2 to converge slow */
	for(i = nreal - k ; i < nreal ; i++)
		g += fabs(xreal[i] - 0.5);
	/* g = g * 100.0 */
	for(i = 0 ; i < nobj ; i++)
		obj[i] = (1.0 + g) ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos((PI / 2.0) * pow(xreal[j], alpha));
		if(i != 0)
			obj[i] *= sin((PI / 2.0) * pow(xreal[nobj - (i+1)], alpha));
	}
	return ;
}

/**
 * Test problem DTLZ5 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: same problem
 **/
void dtlz5 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g, t;
	double *theta;

	theta = (double*)malloc(sizeof(double) * (nobj-1));

	k = nreal - nobj + 1;

	/* similarly, there is no need to make the x_i - 0.5 adjustments. */
	g = 0.0 ;
	/* for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)) ; */
	/* but this might make the problem slower for nsga2 to converge */
	for(i = nreal - k ; i < nreal ; i++)
		g += fabs(xreal[i] - 0.5) ;
	t = PI / (4.0 * (1.0 + g)) ;

	theta[0] = xreal[0] * (PI / 2.0);
	for(i = 1 ; i < nobj - 1 ; i++)
		theta[i] = t * (1.0 + 2.0 * g * xreal[i]);

	for(i = 0 ; i < nobj ; i++)
		obj[i] = (1.0 + g) ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(theta[j]);
		if(i != 0)
			obj[i] *= sin(theta[nobj - (i+1)]);
	}
	free(theta);
	return ;
}

/**
 * Test problem DTLZ6 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: same problem
 **/
void dtlz6 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g, t;
	double *theta;

	theta = (double*)malloc(sizeof(double) * (nobj-1));
	k = nreal - nobj + 1;

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		/* g += pow(xreal[i], 0.1); */
		g += pow(fabs(xreal[i] - 0.5), 0.1);

	t = PI / (4.0 * (1.0 + g)) ;
	theta[0] = xreal[0] * (PI / 2.0);
	for(i = 1 ; i < nobj - 1 ; i++)
		theta[i] = t * (1.0 + 2.0 * g * xreal[i]);

	for(i = 0 ; i < nobj ; i++)
		obj[i] = (1.0 + g) ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(theta[j]);
		if(i != 0)
			obj[i] *= sin(theta[nobj - (i+1)]);
	}
	free(theta);
	return ;
}

/**
 * Test problem DTLZ7 (suggested k = 20)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 20 - 1 = 22 
 * # of bin variables = 0
 * # of constraints = 0
 * harder: same problem.
 **/
void dtlz7 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, k ;
	double g, h;

	k = nreal - nobj + 1;

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		/* g += xreal[i] ; */
		g += fabs(xreal[i] - 0.5);
	g = 1.0 + ((9.0 * g) / k) ;

	for(i = 0 ; i < nobj - 1 ; i++)
		obj[i] = xreal[i] ;

	h = 0.0 ;
	for(i = 0 ; i < nobj - 1 ; i++)
		h += (obj[i]/(1.0 + g)) * (1.0 + sin(3.0 * PI * obj[i])) ;
	h = ((double)nobj) - h ;
	obj[nobj-1] = (1.0 + g) * h;

	return ;
}

/**  
 *  Test problem C1DTLZ1 (suggested k = 5)
 *  # of objectives = M = 3
 *  # of real variables = n = M + k - 1 = 3 + 5 - 1 = 7
 *  # of bin variables = 0
 *  # of constraints = 0
 *  harder: 96 variables
 **/
void c1dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g, fsum ;

	k = nreal - nobj + 1;

	g = 0.0 ;
	/* this is ok, no need to change xreal */
	for(i = nreal - k; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5))
		     - cos(20.0 * PI *  (xreal[i] - 0.5)) ;
	g = 100.0 * (k + g);

	for(i = 0 ; i < nobj ; i++) obj[i] = (1.0 + g) * 0.5 ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0; j < nobj - (i+1); j++) obj[i] *= xreal[j];
		if(i != 0) obj[i] *= 1.0 - xreal[nobj - (i + 1)];
	}
	
	fsum = 0.0 ;
	for(i = 0 ; i < nobj - 1 ; i++)
		fsum += obj[i]/0.5 ;
	constr[0] = 1.0 - (obj[nobj-1]/0.6) - fsum ;
	
	return ;
}

/**
 * Test problem C1DTLZ3 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: 96 variables
 **/
void c1dtlz3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k;
	double g, fsum1, fsum2;
	double r[15] = { 
		0.0, 0.0, 9.0,  0.0, 12.5, 
		0.0, 0.0, 12.5, 0.0, 15.0, 
		0.0, 0.0, 0.0,  0.0, 15.0
	};

	k = nreal - nobj + 1;

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5))
		     - cos(20.0 * PI *  (xreal[i] - 0.5)) ;
	g = 100.0 * (k + g);

	for(i = 0 ; i < nobj ; i++)
		obj[i] = (1.0 + g) ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(xreal[j] * 0.5 * PI);
		if(i != 0)
			obj[i] *= sin(xreal[nobj - (i+1)] * 0.5 * PI);
	}

	fsum1 = 0.0, fsum2 = 0.0 ;
	for(i = 0 ; i < nobj ; i++)
	{
		fsum1 += (obj[i] * obj[i]) - 16 ; 
		fsum2 += (obj[i] * obj[i]) - (r[nobj - 1] * r[nobj - 1]) ; /* M = 3, r = 9 */
	}
	constr[0] = fsum1 * fsum2 ;
	return ;
}

/**
 * Test problem C2DTLZ2 (suggested k = 10)
 * # of objectives = M = 3
 * # of real variables = n = M + k - 1 = 3 + 10 - 1 = 12
 * # of bin variables = 0
 * # of constraints = 0
 * harder: 96 variables
 **/
void c2dtlz2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g, fsum, fmax1, fmax2;

	k = nreal - nobj + 1;

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5));
	/* g = 100.0 * g */
	for(i = 0 ; i < nobj ; i++) obj[i] = 1.0 + g ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0 ; j < nobj - (i+1); j++)
			obj[i] *= cos(xreal[j] * 0.5 * PI) ;
		if(i != 0)
			obj[i] *= sin(xreal[nobj - (i+1)] * 0.5 * PI);
	}

	fmax1 = 0.0 ;
	for(i = 0 ; i < nobj ; i++)
	{
		fsum = 0.0; 
		for(j = 0 ; j < nobj ; j++)
			if (i != j) fsum += (obj[j] * obj[j]) - (0.4 * 0.4) ;
		fsum += (obj[i] - 1.0) * (obj[i] - 1.0) ;
		if(fsum >= fmax1) fmax1 = fsum ;
	}
	fmax2 = 0.0 ;
	for(i = 0 ; i < nobj ; i++)
		fmax2 += ((obj[i] - 1/sqrt(nobj)) * (obj[i] - 1/sqrt(nobj))) - (0.4 * 0.4) ;
	constr[0] = max(fmax1, fmax2);
	return ;
}

/**  
 *  Test problem C3DTLZ1 (suggested k = 5)
 *  # of objectives = M = 3
 *  # of real variables = n = M + k - 1 = 3 + 5 - 1 = 7
 *  # of bin variables = 0
 *  # of constraints = 0
 *  harder: 96 variables
 **/
void c3dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i, j, k ;
	double g, fsum ;

	k = nreal - nobj + 1;

	g = 0.0 ;
	/* this is ok, no need to change xreal */
	for(i = nreal - k; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5))
		     - cos(20.0 * PI *  (xreal[i] - 0.5)) ;
	g = 100.0 * (k + g);

	for(i = 0 ; i < nobj ; i++) obj[i] = (1.0 + g) * 0.5 ;

	for(i = 0 ; i < nobj ; i++)
	{
		for(j = 0; j < nobj - (i+1); j++) obj[i] *= xreal[j];
		if(i != 0) obj[i] *= 1.0 - xreal[nobj - (i + 1)];
	}
	
	for(i = 0 ; i < nobj ; i++)
	{
		fsum = 0.0 ;
		for(j = 0 ; j < nobj ; j++)
			if(i != j) fsum += obj[j] ; 
		constr[i] = fsum + (obj[i]/0.5) - 1.0 ;
	}
	return ;
}

void crash (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	obj[0] = 1640.2823 + (2.3573285 * xreal[0]) 
		+ (2.3220035 * xreal[1]) + (4.5688768 * xreal[2])
		+ (7.7213633 * xreal[3]) + (4.4559504 * xreal[4]) ;

	obj[1] = 6.5856 + (1.15 * xreal[0]) - (1.0427 * xreal[1]) 
		+ (0.9738 * xreal[2]) + (0.8364 * xreal[3])
		- (0.3695 * xreal[0] * xreal[3]) + (0.0861 * xreal[0] * xreal[4]) 
		+ (0.3628 * xreal[1] * xreal[3]) - (0.1106 * xreal[0] * xreal[0]) 
		- (0.3437 * xreal[2] * xreal[2]) + (0.1764 * xreal[3] * xreal[3]) ;
	
	obj[2] = -0.0551 + (0.0181 * xreal[0]) 
		+ (0.1024 * xreal[1]) + (0.0421 * xreal[2]) 
		- (0.0073 * xreal[0] * xreal[1]) + (0.024 * xreal[1] * xreal[2]) 
		- (0.0118 * xreal[1] * xreal[3]) - (0.0204 * xreal[2] * xreal[3]) 
		- (0.008 * xreal[2] * xreal[4]) - (0.0241 * xreal[1] * xreal[1])
		+ (0.0109 * xreal[3] * xreal[3]);
}

void beam (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	double h, b, l, t ;
	double pcx, sigmax, tau_, tau__, taux ;
	h =  xreal[0], b = xreal[1], l = xreal[2], t = xreal[3] ;
	pcx = 64746.022 * (1 - 0.0282346 * t) * t * b * b * b ;
	sigmax = 504000 / (t * t * b);
	tau_ = 6000 / (sqrt(2) * h * l) ;
	tau__ = (6000 * (14 + 0.5 * l) * sqrt(0.25 * (l * l + pow(h + t, 2.0)))) /
			(2 * (0.707 * h * l * (((l * l) / 12) + (0.25 * pow(h + t, 2.0))))) ;
	taux = sqrt((tau_ * tau_) + (tau__ * tau__) 
			+ ((l * tau_ * tau__) / sqrt(0.25 * (l * l + pow(h + t, 2.0)))));
	obj[0] = (1.10471 * h * h * l) + (0.04811 * t * b * (14.0 + l));
	obj[1] = 2.1952 / (t * t * t * b) ;
	constr[0] = 1.0 - (taux / 13600);
	constr[1] = 1.0 - (sigmax / 30000);
	constr[2] = 1.0 - (h/b) ;
	constr[3] = (pcx/6000) - 1.0 ; 
}

void gear (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i ;
	double x1, x2, x3, x4, maxx ;
	x1 = xreal[0];
	x2 = xreal[1];
	x3 = xreal[2];
	x4 = xreal[3];
	maxx = x1 ;
	for(i = 1 ; i < nreal ; i++)
		if(xreal[i] >= maxx)
			maxx = xreal[i];
	obj[0] = fabs(6.931 - ((x3/x1)*(x4/x2)));
	obj[1] = maxx ;
	/**
	 * c1(x) = f1(x)/6.931 <= 0.5
	 * -->	f1(x)/(6.931 * 0.5) <= 1
	 * --> 1 >= f1(x)/(6.931 * 0.5)
	 * --> 1 - (f1(x)/(6.931 * 0.5)) >= 0
	 */
	constr[0] = (obj[0]/(6.931 * 0.5)) - 1.0;
}

double_list* new_double_list()
{
	double_list* lst = (double_list*)malloc(sizeof(double_list));
	if(lst == NULL)
	{
		fprintf(stderr, "new_double_list(): Coudn't allocate a \'double_list\'\n");
		exit(1);		
	}
	lst->head = NULL ; lst->tail = NULL ;
	lst->size = 0 ;
	return lst ;
}

void append(double_list *lst, double value)
{
	dnode *n = (dnode*)malloc(sizeof(dnode));
	n->value = value ;
	n->next = NULL ; n->prev = NULL ;
	if(lst->head == NULL)
	{
		lst->head = n ;
		lst->tail = n ;
	}
	else
	{
		lst->tail->next = n ;
		n->prev = lst->tail ;
		lst->tail = lst->tail->next ;
	}
	lst->size++;
	return ;
}

double pop_max(double_list *lst)
{
	dnode *maxnode, *p;
	double maxval = -DBL_MAX; 
	if(lst->head != NULL)
	{
		if (lst->head == lst->tail)
		{
			maxnode = lst->head ;
			maxval = maxnode->value ;
			lst->head = NULL ;
			lst->tail = NULL ;
			free(maxnode);
			lst->size-- ;
		}
		else
		{
			maxnode = lst->head ;
			maxval = maxnode->value ;
			p = lst->head->next ;
			while(p != NULL)
			{
				if(p->value >= maxval)
				{
					maxval = p->value ;
					maxnode = p ;
				}
				p = p->next ;
			}
			if(maxnode == lst->head) 
			{
				lst->head = maxnode->next ; 
				maxnode->prev = NULL ;
				maxnode->next = NULL ;
			}
			else if(maxnode == lst->tail)
			{
				lst->tail = maxnode->prev ;
				maxnode->prev->next = NULL ;
				maxnode->prev = NULL ;
				maxnode->next = NULL ;
			}
			else
			{
				maxnode->prev->next = maxnode->next ;
				maxnode->next->prev = maxnode->prev ;
			}
			lst->size-- ;
			free(maxnode);
		}
	}
	return maxval ;
}

void free_double_list(double_list *lst)
{
	dnode *tmp ;
	dnode *p = lst->head ;
	if(lst->head != NULL)
	{
		while (1)
		{
			if(lst->head == lst->tail)
			{
				tmp = lst->head ;
				lst->head = NULL ;
				lst->tail = NULL ;
				free(tmp);
				break ;
			}
			lst->head = p->next ;
			tmp = p ;
			p->next->prev = NULL ;
			p = p->next ;	
			free(tmp);
		}
	}
	free(lst);	
}

void print_double_list(double_list *lst)
{
	dnode *p = lst->head ;
	printf("%d: ", lst->size);
	while(p != NULL)
	{
		printf("%.3f ", p->value) ;
		p = p->next ;
	}
}

void printv(double *x, int len)
{
	int i ;
	for(i = 0 ; i < len ; i++)
		fprintf(stdout, "%.3f ", x[i]);
	return ;
}

void mapvars(double *x, int xlen, double *y)
{
	int i, N, x1_min, x1_max ;
	double x2_min, x2_max ;
	N = xlen ;
	x1_min = 0.2 ; x1_max = 1.0 ;
	x2_min = -180.0; x2_max = 180.0 ;
	for(i = 0 ; i < N/2 ; i++)
		y[i] = x1_min + (x[i] * (x1_max - x1_min));
	for(i = N/2 ; i < N ; i++)
		y[i] = x2_min + (x[i] * (x2_max - x2_min));
	return ;
}

double array_factor(double *x, double phi, double phi_desired, 
				double distance, int dim)
{
	int i ; 
	double delphi, shi ;
	double pi = 3.141592654 ;
	double y1 = 0.0, y2 = 0.0 ;
	for(i = 0 ; i < dim ; i++)
	{
		delphi = 2.0 * pi * (i/(double)dim) ;
		shi = cos(phi - delphi) - cos(phi_desired * (pi/180.0) - delphi);
		shi = shi * dim * distance ;
		if (i < dim/2) 
		{
			y1 = y1 + x[i] * cos(shi + x[(dim/2) + i] * (pi/180.0));
			y2 = y2 + x[i] * sin(shi + x[(dim/2) + i] * (pi/180.0));
		}
		else
		{
			y1 = y1 + x[i - (dim/2)] * cos(shi - x[i] * (pi/180.0));
			y2 = y2 + x[i - (dim/2)] * sin(shi - x[i] * (pi/180.0));
		}
	}

	return sqrt((y1 * y1) + (y2 * y2));
}

double trapezoid(double *xval, double upper, double lower, int N1, 
			double phi_desired, double distance, int dim)
{
	int i ;
	double *y ;
	double h, x, q, s;
	double pi = 3.1416 ;
	y = (double*)malloc(sizeof(double) * (N1+1));
	
	h = (upper - lower) / N1 ; 
	x = lower ;
	y[0] = fabs(pow(array_factor(xval, x, phi_desired, distance, dim), 2.0) 
			* sin(x - pi/2.0));
	for(i = 1 ; i < N1 + 1 ; i++) 
	{
		x += h ;
		y[i] = fabs(pow(array_factor(xval, x, phi_desired, distance, dim), 2.0) 
				* sin(x - pi/2.0));
	}

	s = 0.0 ;
	for(i = 0 ; i < N1 + 1 ; i++)
	{
		if(i == 0 || i == N1)
			s += y[i] ;
		else
			s += 2.0 * y[i] ;
	}
	q = (h / 2.0) * s ;
	free(y);
	return q ;
}

void linspace(double a, double b, int n, double *vals)
{
	int i; double del ;
	del = (b - a)/((double)(n - 1));
	vals[0] = a ;
	for(i = 1 ; i < n ; i++)
		vals[i] = vals[i-1] + del ;
	return ;
}

void antenna(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	int i ;
	double *x, *phi, *yax ;
        /* double directivity ;	*/
	double pi, phi_desired, distance, phizero, maxi, y, sllreturn;
	double upper_bound, lower_bound, bwfn, y1, y3;
	int dim, num_null, phi_ref, num1, count ;
	double_list *sidelobes ;

	pi = 3.141592654 ;
	
	double nullv[2] = {50.0, 120.0};
	phi_desired = 180.0 ; 
	distance = 0.5 ;

	dim = nreal ;
	x = (double*)malloc(sizeof(double) * dim);
	/* mapvars(xreal, dim, x); */ /* not doing it anymore */
	for(i = 0 ; i < nreal ; i++)
		x[i] = xreal[i] ;

	num_null = sizeof(nullv)/sizeof(nullv[0]) ;
	num1 = 300 ;
	phi = (double*)malloc(sizeof(double) * num1);
	linspace(0, 360, num1, phi);

	phizero = 0.0 ;
	yax = (double*)malloc(sizeof(double) * num1);
	yax[0] = array_factor(x, (pi/180.0) * phi[0], phi_desired, distance, dim);
	maxi = yax[0] ;
	phi_ref = 0 ;
	/* this loop computes the max gain */
	for(i = 1; i < num1 ; i++)
	{
		yax[i] = array_factor(x, (pi/180.0) * phi[i], phi_desired, distance, dim);
		if( maxi < yax[i]) 
		{
			maxi = yax[i] ;
			phizero = phi[i] ;
			phi_ref = i ;
		}	
	}
	
	sidelobes = new_double_list();
	count = -1 ;
	if (yax[0] > yax[num1-1] && yax[0] > yax[1])
	{
		count++ ;
		append(sidelobes, yax[0]);
	}
	if (yax[num1-1] > yax[0] && yax[num1-1] > yax[num1-2])
	{
		count++ ;
		append(sidelobes, yax[num1-1]);
	}
	for(i = 1 ; i < num1-1 ; i++)
	{
		if (yax[i] > yax[i+1] && yax[i] > yax[i-1])
		{
			count++ ;
			append(sidelobes, yax[i]);
		}
	}
	pop_max(sidelobes);
	y = pop_max(sidelobes)/maxi ;
	sllreturn = 20.0 * log10(y);
	free_double_list(sidelobes);

	upper_bound = 180 ; lower_bound = 180 ;
	for(i = 0 ; i < num1/2 ; i++)
	{
		if((phi_ref+i) > num1-1)
		{
			upper_bound = 180 ;
			break ;
		}
		if((yax[phi_ref + i] < yax[phi_ref + i - 1]) 
			&& (yax[phi_ref + i] < yax[phi_ref + i + 1]))
		{
			upper_bound = phi[phi_ref + i] - phi[phi_ref] ;
			break ;
		}
	}
	for(i = 0 ; i < num1/2 ; i++)
	{
		if ((phi_ref - i) < 2)
		{
			lower_bound = 180 ;
			break ;
		}
		if ((yax[phi_ref - i] < yax[phi_ref - i - 1]) 
			&& (yax[phi_ref - i] < yax[phi_ref - i + 1]))
		{
			lower_bound = phi[phi_ref] - phi[phi_ref - i];
			break ;
		}
	}
	bwfn = upper_bound + lower_bound ;

	y1 = 0.0 ;
	for(i = 0 ; i < num_null ; i++)
		y1 += array_factor(x, nullv[i], phi_desired, distance, dim) / (double)maxi ;

	y3 = fabs(phizero - phi_desired);
	if( y3 < 5 ) y3 = 0 ;

	y = 0 ;
	if (bwfn > 80) y += fabs(bwfn - 80);

	free(yax);
	free(phi);
	free(x);

	obj[0] = sllreturn ;
	obj[1] = y + y3 ;
	obj[2] = y1 ;

	return ;
}

/* wrapper */
void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
	if(strcmp(prob_name, "sch1") == 0)
		sch1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "sch2") == 0)
		sch2(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "fon") == 0)
		fon(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "kur") == 0)
		kur(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "pol") == 0)
		pol(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "vnt") == 0)
		vnt(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt1") == 0)
		zdt1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt2") == 0)
		zdt2(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt3") == 0)
		zdt3(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt4") == 0)
		zdt4(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt5") == 0)
		zdt5(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "zdt6") == 0)
		zdt6(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "bnh") == 0)
		bnh(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "osy") == 0)
		osy(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "srn") == 0)
		srn(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "tnk") == 0)
		tnk(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp1") == 0)
		ctp1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp2") == 0)
		ctp2(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp3") == 0)
		ctp3(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp4") == 0)
		ctp4(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp5") == 0)
		ctp5(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp6") == 0)
		ctp6(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp7") == 0)
		ctp7(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "ctp8") == 0)
		ctp8(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz1") == 0)
		dtlz1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz2") == 0)
		dtlz2(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz3") == 0)
		dtlz3(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz4") == 0)
		dtlz4(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz5") == 0)
		dtlz5(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz6") == 0)
		dtlz6(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "dtlz7") == 0)
		dtlz7(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "c1dtlz1") == 0)
		c1dtlz1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "c1dtlz3") == 0)
		c1dtlz3(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "c2dtlz2") == 0)
		c2dtlz2(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "c3dtlz1") == 0)
		c3dtlz1(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "crash") == 0)
		crash(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "beam") == 0)
		beam(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "gear") == 0)
		gear(xreal, xbin, gene, obj, constr);
	else if(strcmp(prob_name, "antenna") == 0)
		antenna(xreal, xbin, gene, obj, constr);
	else
	{
		fprintf(stdout, " Error: wrong problem string or problem not defined.\n");
		exit(1);
	}
}
