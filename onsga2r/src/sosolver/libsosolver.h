/*
 * MATLAB Compiler: 5.1 (R2014a)
 * Date: Thu Mar  3 03:00:37 2016
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libsosolver" "-W"
 * "lib:libsosolver" "-T" "link:lib" "-v" "src/sosolver/aasf.m"
 * "src/sosolver/antenna_constfunc.m" "src/sosolver/antenna.m"
 * "src/sosolver/array_factor.m" "src/sosolver/beam_constfunc.m"
 * "src/sosolver/beam.m" "src/sosolver/bnh.m"
 * "src/sosolver/c1dtlz1_constfunc.m" "src/sosolver/c1dtlz1.m"
 * "src/sosolver/c1dtlz3_constfunc.m" "src/sosolver/c1dtlz3.m"
 * "src/sosolver/c2dtlz2_constfunc.m" "src/sosolver/c2dtlz2.m"
 * "src/sosolver/c3dtlz1_constfunc.m" "src/sosolver/c3dtlz1.m"
 * "src/sosolver/crash_constfunc.m" "src/sosolver/crash.m"
 * "src/sosolver/ctp4_constfunc.m" "src/sosolver/ctp4.m"
 * "src/sosolver/ctp8_constfunc.m" "src/sosolver/ctp8.m"
 * "src/sosolver/dtlz1_constfunc.m" "src/sosolver/dtlz1.m"
 * "src/sosolver/dtlz2_constfunc.m" "src/sosolver/dtlz2.m"
 * "src/sosolver/dtlz3_constfunc.m" "src/sosolver/dtlz3.m"
 * "src/sosolver/dtlz4_constfunc.m" "src/sosolver/dtlz4.m"
 * "src/sosolver/dtlz5_constfunc.m" "src/sosolver/dtlz5.m"
 * "src/sosolver/dtlz6_constfunc.m" "src/sosolver/dtlz6.m"
 * "src/sosolver/dtlz7_constfunc.m" "src/sosolver/dtlz7.m" "src/sosolver/fon.m"
 * "src/sosolver/gear_constfunc.m" "src/sosolver/gear.m" "src/sosolver/kur.m"
 * "src/sosolver/load_input_data.m" "src/sosolver/mapvars.m"
 * "src/sosolver/osy_constfunc.m" "src/sosolver/osy.m"
 * "src/sosolver/plot_gain.m" "src/sosolver/pol.m" "src/sosolver/printmatrix.m"
 * "src/sosolver/sch1.m" "src/sosolver/sch2.m" "src/sosolver/sopt.m"
 * "src/sosolver/sosolver.m" "src/sosolver/srn.m"
 * "src/sosolver/tester_antenna.m" "src/sosolver/test_sosolver.m"
 * "src/sosolver/tnk.m" "src/sosolver/trapezoid.m" "src/sosolver/vnt.m"
 * "src/sosolver/zdt1_constfunc.m" "src/sosolver/zdt1.m"
 * "src/sosolver/zdt2_constfunc.m" "src/sosolver/zdt2.m"
 * "src/sosolver/zdt3_constfunc.m" "src/sosolver/zdt3.m"
 * "src/sosolver/zdt4_constfunc.m" "src/sosolver/zdt4.m" "src/sosolver/zdt5.m"
 * "src/sosolver/zdt6_constfunc.m" "src/sosolver/zdt6.m" 
 */

#ifndef __libsosolver_h
#define __libsosolver_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libsosolver
#define PUBLIC_libsosolver_C_API __global
#else
#define PUBLIC_libsosolver_C_API /* No import statement needed. */
#endif

#define LIB_libsosolver_C_API PUBLIC_libsosolver_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libsosolver
#define PUBLIC_libsosolver_C_API __declspec(dllexport)
#else
#define PUBLIC_libsosolver_C_API __declspec(dllimport)
#endif

#define LIB_libsosolver_C_API PUBLIC_libsosolver_C_API


#else

#define LIB_libsosolver_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libsosolver_C_API 
#define LIB_libsosolver_C_API /* No special import/export declaration */
#endif

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV libsosolverInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV libsosolverInitialize(void);

extern LIB_libsosolver_C_API 
void MW_CALL_CONV libsosolverTerminate(void);



extern LIB_libsosolver_C_API 
void MW_CALL_CONV libsosolverPrintStackTrace(void);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAasf(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAntenna_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAntenna(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxArray_factor(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBeam_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBeam(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBnh(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC2dtlz2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC2dtlz2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC3dtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC3dtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCrash_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCrash(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp8_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp8(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz5_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz5(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz6_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz6(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz7_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz7(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxFon(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxGear_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxGear(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxKur(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxLoad_input_data(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                     *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxMapvars(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxOsy_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxOsy(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPlot_gain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPol(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPrintmatrix(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSch1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSch2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSopt(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSosolver(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSrn(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTester_antenna(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTest_sosolver(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTnk(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTrapezoid(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxVnt(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt5(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt6_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt6(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfAasf(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfAntenna_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfAntenna(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfArray_factor(int nargout, mxArray** y, mxArray* x, mxArray* phi, mxArray* phi_desired, mxArray* distance, mxArray* dim);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfBeam_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfBeam(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfBnh(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC1dtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC1dtlz1(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC1dtlz3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC1dtlz3(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC2dtlz2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC2dtlz2(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC3dtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfC3dtlz1(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCrash_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCrash(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCtp4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCtp4(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCtp8_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfCtp8(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz1(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz2(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz3(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz4(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz5_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz5(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz6_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz6(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz7_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfDtlz7(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfFon(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfGear_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfGear(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfKur(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfLoad_input_data(mxArray* datafile);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfMapvars(int nargout, mxArray** yvals, mxArray* xvals);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfOsy_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfOsy(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfPlot_gain(mxArray* nplot, mxArray* gbest, mxArray* phi_desired, mxArray* distance);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfPol(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfPrintmatrix(mxArray* X, mxArray* dec);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfSch1(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfSch2(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfSopt(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfSosolver(int nargout, mxArray** result, mxArray* file_path, mxArray* findex, mxArray* seed);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfSrn(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfTester_antenna();

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfTest_sosolver();

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfTnk(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfTrapezoid(int nargout, mxArray** q, mxArray* xval, mxArray* upper, mxArray* lower, mxArray* N1, mxArray* phi_desired, mxArray* distance, mxArray* dim);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfVnt(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt1(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt2(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt3(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt4(int nargout, mxArray** f, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt5(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt6_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x);

extern LIB_libsosolver_C_API bool MW_CALL_CONV mlfZdt6(int nargout, mxArray** f, mxArray* x);

#ifdef __cplusplus
}
#endif
#endif
