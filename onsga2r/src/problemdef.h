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

/* constrained dtlz problems */
void c1dtlz1 (double *xreal, double *xbin, int **gene, double *obj, double *constr);
void c1dtlz3 (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* engineering problems */
// vehicle crash worthiness
void crash (double *xreal, double *xbin, int **gene, double *obj, double *constr);
// welded beam design
void beam (double *xreal, double *xbin, int **gene, double *obj, double *constr);
// gear train design
void gear (double *xreal, double *xbin, int **gene, double *obj, double *constr);

/* wrapper */
void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

# endif
