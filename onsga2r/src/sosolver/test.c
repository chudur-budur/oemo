# include <stdio.h>
# include <stdlib.h>
# include "libsosolver.h"

void display(const mxArray* in);

int main()
{
	mclmcrInitialize();
	
	mxArray *result = NULL ;
	mxArray *file_path = NULL ;
	mxArray *findex = NULL ;
	mxArray *seed = NULL ;
	
	if( !mclInitializeApplication(NULL,0) )
	{
        	fprintf(stderr, "Could not initialize the application.\n");
    		return -1;
	}

	
	if (!libsosolverInitialize()){
		fprintf(stderr,"Could not initialize the library.\n");
		return -2;
	}
	else
	{
		file_path = mxCreateString("../../input_data/zdt1.in");
		seed = mxCreateDoubleScalar(12345);
		findex = mxCreateDoubleScalar(2);
		mlfSosolver(1, &result, file_path, findex, seed);
		display(result);
		mxDestroyArray(result); result = 0 ;
		libsosolverTerminate();
		mxDestroyArray(file_path); file_path = 0 ;
		mxDestroyArray(findex); findex = 0 ;
	}

	mclTerminateApplication();
	return 0; 
}

void display(const mxArray* in)
{
    int i=0, j=0; /* loop index variables */
    int r=0, c=0; /* variables to store the row and column length of the matrix */
    double *data; /* variable to point to the double data stored within the mxArray */

    /* Get the size of the matrix */
    r = mxGetM(in);
    c = mxGetN(in);
    /* Get a pointer to the double data in mxArray */
    data = mxGetPr(in);
    
    /* Loop through the data and display the same in matrix format */
    for( i = 0; i < c; i++ ){
        for( j = 0; j < r; j++){
            printf("%.4f\t",data[j*c+i]);
        }
        printf("\n");
    }
    printf("\n");
}
