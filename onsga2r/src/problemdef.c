/* Test problem definitions */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# include "global.h"
# include "problemdef.h"
# include "rand.h"

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
	for (i=1; i<nreal; i++)
		g += (xreal[i] - 0.5) * (xreal[i] - 0.5); 
		/* g += pow(fabs((xreal[i] - 0.5)), 0.001) ;*/
		/* g += xreal[i] ;*/
	g = 9.0*g/((double)nreal - 1.0);
	g += 1.0;
	h = 1.0 - sqrt(f1/g);
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
	return;
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
	for (i=1; i<nreal; i++) g += xreal[i]; /* (xreal[i] - 0.5)^2 */
	g = 1.0 + (9.0*g/((double)nreal - 1.0));
	h = 1.0 - pow((f1/g),2.0);
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
	return;
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
	for (i=1; i<nreal; i++) g += xreal[i]; /* (xreal[i] - 0.5)^2 */
	g = 1.0 + (9.0*g/((double)nreal - 1.0));
	h = 1.0 - sqrt(f1/g) - (f1/g)*sin(10.0*PI*f1);
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
	return;
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
	/* for(i = 1; i < nreal ; i++ ) 
		g += (xreal[i] - 0.5)*(xreal[i] - 0.5) - 10.0*cos(4.0*PI*(xreal[i] - 0.5)); */
	for (i=1; i<nreal; i++) g += xreal[i]*xreal[i] - 10.0*cos(4.0*PI*xreal[i]); 
	g += 1.0 + 10.0 * ((double)nreal - 1.0);
	h = 1.0 - sqrt(f1/g);
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
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
	f1 = 1.0 - ( exp(-4.0*xreal[0]) ) * pow( (sin(6.0*PI*xreal[0])),6.0 );
	g = 0.0;
	for (i=1; i<nreal; i++) g += xreal[i];
	/* for (i=1; i<nreal; i++) g += (xreal[i] - 0.5) * (xreal[i] - 0.5) ;*/
	g = g/9.0;
	g = pow(g,0.25);
	g = 1.0 + 9.0*g;
	h = 1.0 - pow((f1/g),2.0);
	f2 = g*h;
	obj[0] = f1;
	obj[1] = f2;
	return;
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
	obj[0] = -(25.0*pow((xreal[0]-2.0),2.0) + pow((xreal[1]-2.0),2.0) + pow((xreal[2]-1.0),2.0) + pow((xreal[3]-4.0),2.0) + pow((xreal[4]-1.0),2.0));
	obj[1] = xreal[0]*xreal[0] +  xreal[1]*xreal[1] + xreal[2]*xreal[2] + xreal[3]*xreal[3] + xreal[4]*xreal[4] + xreal[5]*xreal[5];
	constr[0] = (xreal[0]+xreal[1])/2.0 - 1.0;
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

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)) ;
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

	g = 0.0 ;
	for(i = nreal - k ; i < nreal ; i++)
		g += ((xreal[i] - 0.5) * (xreal[i] - 0.5)) ;
	/* g = 100.0 * g */
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
		g += pow(xreal[i], 0.1);
		/* g += pow(fabs(xreal[i] - 0.5), 0.1); */

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
		g += xreal[i] ;
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
	else
	{
		fprintf(stdout, " Error: wrong problem string or problem not defined.\n");
		exit(1);
	}
}
