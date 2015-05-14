/*========================================================================
	PISA  (www.tik.ee.ethz.ch/pisa/)
	========================================================================
	Computer Engineering (TIK)
	ETH Zurich
	========================================================================
	PREMO - Preference-based Multiobjective Optimizer

	Implementation in C for the selector side.

	Header file for premo_wdfs.c.

	file: premo_wdfs.h
	authors: Dimo Brockhoff, brockho@tik.ee.ethz.ch

	revision by: ---
	last change: August 10, 2007
	========================================================================
 */

/* Computes the integral 
	\int_a^b w(z) dz
	where the dim-dimensional points a and b are given
	in refs, w(z) is the weight distribution function,
	selected via variable "wdf".
	
	The parameter refpoint is only used with wdf '3' as the
	reference point.
	
	Note, that the scaling is done within this function,
	depending on type of hypervolume computation selected by the variable
	"hyp_ind_type".
	
	The ideal point is given as *ideal to rescale the
	points to [0,1] for hyp_ind_type == 1 (assuming that the objectives
	are always maximized and the nadir point is (0,0...0).
*/
double  calc_hypercube_integral(double  *refs, int dim, int hyp_ind_type,  
                                double *ideal, int wdf, double *refpoint);
void* chk_malloc(size_t size);
void chk_free( void* pointer );
