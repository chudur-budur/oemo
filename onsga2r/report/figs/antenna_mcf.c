#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/* the antenna design problem */
typedef struct dnode dnode ;
struct dnode {
	double value ; dnode *next ; dnode *prev ;
};
typedef struct {
	int size; dnode *head ; dnode *tail ;
} double_list ;
double_list* new_double_list();
void append(double_list *lst, double value);
double pop_max(double_list *lst);
void free_double_list(double_list *lst);
void print_double_list(double_list *lst);
void printv(double *x, int len);
void mapvars(double *x, int xlen, double *y);
double array_factor(double *x, double phi, double phi_desired, 
			double distance, int dim);
double trapezoid(double *xval, double upper, double lower, int N1, 
			double phi_desired, double distance, int dim);
void linspace(double a, double b, int n, double *vals);
void antenna(double *xreal, double *xbin, int **gene, double *obj, double *constr);

int nreal = 12 ;
int nobj = 3 ;


int main(void)
{
	int i, n, N ;
	double *x_, *x, *f ;

	srand(0.123456);

	x_ = (double*)malloc(sizeof(double) * nreal);
	x = (double*)malloc(sizeof(double) * nreal);
	f = (double*)malloc(sizeof(double) * nobj);

	N = 5000 ;
	for(n = 0 ; n < N ; n++)
	{
		for(i = 0 ; i < nreal ; i++)
			x_[i] = (rand() % 1000)/1000.0 ;
		mapvars(x_, nreal, x);
		antenna(x, NULL, NULL, f, NULL);
		fprintf(stdout, "%.4f\t\t%10.4f\t%10.4f\n", f[0], f[1], f[2]);
	}

	free(f);
	free(x);
	free(x_);
	return 0 ;
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
