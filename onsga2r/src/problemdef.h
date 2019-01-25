# ifndef _PROBLEM_DEF_H_
# define _PROBLEM_DEF_H_

/* # define sch1 */
/* # define sch2 */
/* # define fon  */
/* # define kur  */
/* # define pol  */
/* # define vnt  */
/* # define bnh  */
/* # define osy  */
/* # define srn  */
/* # define tnk  */
/* # define ctp1 */
/* # define ctp2 */
/* # define ctp3 */
/* # define ctp4 */
/* # define ctp5 */
/* # define ctp6 */
/* # define ctp7 */
/* # define ctp8 */

/* zdt sets */
/* # define zdt1 */ /* good */
/* # define zdt2 */ /* good */
/* # define zdt3 */ /* good */
/* # define zdt4 */ /* good */
/* # define zdt5 */ /* good */
/* # define zdt6 */ /* good */

/* some mop's with nobj > 2 */
/* # define dtlz1 */ /* good */
/* # define dtlz2 */ /* same */
/* # define dtlz3 */ /* good */
/* # define dtlz4 */ /* same */
/* # define dtlz5 */ /* same */
/* # define dtlz6 */ /* good */
/* # define dtlz7 */ /* good, one patch */
/* # define dtlz8 */

/* unconstrained 2-obj */
void sch1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void sch2 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void fon (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void kur (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void pol (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void vnt (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* unconstrained 2-obj */
void zdt1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void zdt2 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void zdt3 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void zdt4 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void zdt5 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void zdt6 (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* constrained 2-obj */
void bnh (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void osy (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void srn (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void tnk (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp2 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp3 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp4 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp5 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp6 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp7 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void ctp8 (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* unconstrained >2-obj */
void dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz2 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz3 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz4 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz5 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz6 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz7 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void dtlz8 (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* constrained dtlz problems */
void c1dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void c1dtlz3 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void c2dtlz2 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void c3dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* engineering problems */
/* vehicle crash worthiness */
void crash (double *xreal, double *xbin, int **gene, double *obj, double *constr);
/* welded beam design */
void beam (double *xreal, double *xbin, int **gene, double *obj, double *constr);
/* gear train design */
void gear (double *xreal, double *xbin, int **gene, double *obj, double *constr);

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

/** All the WFG problems */
void wfg1(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg2(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg3(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg4(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg5(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg6(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg7(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg8(double *xreal, double *xbin, int **gene, double *obj, double *constr);
void wfg9(double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* wrapper */
void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

# endif
