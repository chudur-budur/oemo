/*
 * MATLAB Compiler: 5.1 (R2014a)
 * Date: Tue Mar  1 12:23:20 2016
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
 * "src/sosolver/tester_antenna.m" "src/sosolver/test.m" "src/sosolver/tnk.m"
 * "src/sosolver/trapezoid.m" "src/sosolver/vnt.m"
 * "src/sosolver/zdt1_constfunc.m" "src/sosolver/zdt1.m"
 * "src/sosolver/zdt2_constfunc.m" "src/sosolver/zdt2.m"
 * "src/sosolver/zdt3_constfunc.m" "src/sosolver/zdt3.m"
 * "src/sosolver/zdt4_constfunc.m" "src/sosolver/zdt4.m" "src/sosolver/zdt5.m"
 * "src/sosolver/zdt6_constfunc.m" "src/sosolver/zdt6.m" 
 */

#include <stdio.h>
#define EXPORTING_libsosolver 1
#include "libsosolver.h"

static HMCRINSTANCE _mcr_inst = NULL;


#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libsosolver_C_API
#define LIB_libsosolver_C_API /* No special import/export declaration */
#endif

LIB_libsosolver_C_API 
bool MW_CALL_CONV libsosolverInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream((void *)(libsosolverInitializeWithHandlers));
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV libsosolverInitialize(void)
{
  return libsosolverInitializeWithHandlers(mclDefaultErrorHandler, 
                                           mclDefaultPrintHandler);
}

LIB_libsosolver_C_API 
void MW_CALL_CONV libsosolverTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_libsosolver_C_API 
void MW_CALL_CONV libsosolverPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAasf(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "aasf", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAntenna_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[])
{
  return mclFeval(_mcr_inst, "antenna_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxAntenna(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "antenna", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxArray_factor(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "array_factor", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBeam_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "beam_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBeam(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "beam", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxBnh(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "bnh", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[])
{
  return mclFeval(_mcr_inst, "c1dtlz1_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "c1dtlz1", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[])
{
  return mclFeval(_mcr_inst, "c1dtlz3_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC1dtlz3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "c1dtlz3", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC2dtlz2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[])
{
  return mclFeval(_mcr_inst, "c2dtlz2_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC2dtlz2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "c2dtlz2", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC3dtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[])
{
  return mclFeval(_mcr_inst, "c3dtlz1_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxC3dtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "c3dtlz1", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCrash_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "crash_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCrash(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "crash", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ctp4_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ctp4", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp8_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ctp8_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxCtp8(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ctp8", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz1_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz1", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz2_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz2", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz3_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz3", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz4_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz4", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz5_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz5_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz5(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz5", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz6_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz6_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz6(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz6", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz7_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz7_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxDtlz7(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dtlz7", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxFon(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "fon", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxGear_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "gear_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxGear(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "gear", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxKur(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "kur", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxLoad_input_data(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "load_input_data", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxMapvars(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "mapvars", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxOsy_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "osy_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxOsy(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "osy", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPlot_gain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "plot_gain", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPol(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "pol", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxPrintmatrix(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "printmatrix", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSch1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sch1", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSch2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sch2", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSopt(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sopt", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSosolver(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sosolver", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxSrn(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "srn", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTester_antenna(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "tester_antenna", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTest(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "test", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTnk(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "tnk", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxTrapezoid(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "trapezoid", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxVnt(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "vnt", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt1_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt1_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt1", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt2_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt2_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt2", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt3_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt3_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt3(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt3", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt4_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt4_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt4(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt4", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt5(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt5", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt6_constfunc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt6_constfunc", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlxZdt6(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "zdt6", nlhs, plhs, nrhs, prhs);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfAasf(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "aasf", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfAntenna_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* 
                                       x)
{
  return mclMlfFeval(_mcr_inst, "antenna_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfAntenna(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "antenna", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfArray_factor(int nargout, mxArray** y, mxArray* x, mxArray* phi, 
                                  mxArray* phi_desired, mxArray* distance, mxArray* dim)
{
  return mclMlfFeval(_mcr_inst, "array_factor", nargout, 1, 5, y, x, phi, phi_desired, distance, dim);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfBeam_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "beam_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfBeam(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "beam", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfBnh(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "bnh", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC1dtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* 
                                       x)
{
  return mclMlfFeval(_mcr_inst, "c1dtlz1_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC1dtlz1(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "c1dtlz1", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC1dtlz3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* 
                                       x)
{
  return mclMlfFeval(_mcr_inst, "c1dtlz3_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC1dtlz3(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "c1dtlz3", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC2dtlz2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* 
                                       x)
{
  return mclMlfFeval(_mcr_inst, "c2dtlz2_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC2dtlz2(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "c2dtlz2", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC3dtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* 
                                       x)
{
  return mclMlfFeval(_mcr_inst, "c3dtlz1_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfC3dtlz1(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "c3dtlz1", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCrash_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "crash_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCrash(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "crash", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCtp4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "ctp4_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCtp4(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "ctp4", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCtp8_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "ctp8_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfCtp8(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "ctp8", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz1_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz1(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz1", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz2_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz2(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz2", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz3_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz3(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz3", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz4_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz4(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz4", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz5_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz5_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz5(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz5", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz6_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz6_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz6(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz6", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz7_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz7_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfDtlz7(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "dtlz7", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfFon(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "fon", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfGear_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "gear_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfGear(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "gear", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfKur(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "kur", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfLoad_input_data(mxArray* datafile)
{
  return mclMlfFeval(_mcr_inst, "load_input_data", 0, 0, 1, datafile);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfMapvars(int nargout, mxArray** yvals, mxArray* xvals)
{
  return mclMlfFeval(_mcr_inst, "mapvars", nargout, 1, 1, yvals, xvals);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfOsy_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "osy_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfOsy(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "osy", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfPlot_gain(mxArray* nplot, mxArray* gbest, mxArray* phi_desired, 
                               mxArray* distance)
{
  return mclMlfFeval(_mcr_inst, "plot_gain", 0, 0, 4, nplot, gbest, phi_desired, distance);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfPol(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "pol", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfPrintmatrix(mxArray* X, mxArray* dec)
{
  return mclMlfFeval(_mcr_inst, "printmatrix", 0, 0, 2, X, dec);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfSch1(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "sch1", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfSch2(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "sch2", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfSopt(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "sopt", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfSosolver(int nargout, mxArray** result, mxArray* file_path, mxArray* 
                              findex, mxArray* seed)
{
  return mclMlfFeval(_mcr_inst, "sosolver", nargout, 1, 3, result, file_path, findex, seed);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfSrn(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "srn", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfTester_antenna()
{
  return mclMlfFeval(_mcr_inst, "tester_antenna", 0, 0, 0);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfTest()
{
  return mclMlfFeval(_mcr_inst, "test", 0, 0, 0);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfTnk(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "tnk", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfTrapezoid(int nargout, mxArray** q, mxArray* xval, mxArray* upper, 
                               mxArray* lower, mxArray* N1, mxArray* phi_desired, 
                               mxArray* distance, mxArray* dim)
{
  return mclMlfFeval(_mcr_inst, "trapezoid", nargout, 1, 7, q, xval, upper, lower, N1, phi_desired, distance, dim);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfVnt(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "vnt", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt1_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt1_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt1(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt1", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt2_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt2_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt2(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt2", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt3_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt3_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt3(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt3", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt4_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt4_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt4(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt4", nargout, 1, 1, f, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt5(int nargout, mxArray** parent_pop, mxArray* parent_pop_in1)
{
  return mclMlfFeval(_mcr_inst, "zdt5", nargout, 1, 1, parent_pop, parent_pop_in1);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt6_constfunc(int nargout, mxArray** c, mxArray** ceq, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt6_constfunc", nargout, 2, 1, c, ceq, x);
}

LIB_libsosolver_C_API 
bool MW_CALL_CONV mlfZdt6(int nargout, mxArray** f, mxArray* x)
{
  return mclMlfFeval(_mcr_inst, "zdt6", nargout, 1, 1, f, x);
}

