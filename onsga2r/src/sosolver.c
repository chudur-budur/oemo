# include "sosolver.h"
# include "global.h"
# include "poplist.h"
# include "misc.h"
# include "libsosolver.h"

int nreal ;
int nobj ;
	
int sosolver(pop_list *lst)
{
	char path_str[80] ;
	individual ind ;
	int i, fe, feval = -1 ;
	
	mclmcrInitialize();

	mxArray *result = NULL ;
	mxArray *file_path = NULL;
	mxArray *findex = NULL ;

	if(!mclInitializeApplication(NULL,0))
	{
	    	fprintf(stdout, "Could not initialize the application.\n");
		return -1;
	}

	if (!libsosolverInitialize())
	{
		fprintf(stdout,"Could not initialize the library.\n");
		return -2;
	}
	else
	{
		load_path(path_str);
		fprintf(stdout, "path_str = %s\n", path_str);
		file_path = mxCreateString(path_str);
		for(i = 0 ; i < nobj ; i++)
		{
			findex = mxCreateDoubleScalar(i+1);
			mlfSosolver(1, &result, file_path, findex);
			/*display(result);*/
			allocate_memory_ind(&ind);
			parse_result(ind.xreal, &fe, result);
			evaluate_ind(&ind);
			dumpf_individual(&ind, stdout);
			push_back(lst, &ind);
			deallocate_memory_ind(&ind);
			feval += fe ;
			mxDestroyArray(result); result = NULL ;
			mxDestroyArray(findex); findex = NULL ;
		}
		fprintf(stdout, "feval = %d\n", feval);
		libsosolverTerminate();
		mxDestroyArray(file_path); file_path = NULL ;
	}

	mclTerminateApplication();
	return feval ;
}

void display(const mxArray* in)
{
	int i=0, j=0; /* loop index variables */
	int r=0, c=0; /* variables to store the row and column length of the matrix */
	double *data; /* variable to point to the double data stored within the mxArray */

	/* Get the size of the matrix */
	r = mxGetM(in);
	c = mxGetN(in);
	fprintf(stdout, "row = %d, col = %d\n", r, c);
	/* Get a pointer to the double data in mxArray */
	data = mxGetPr(in);

	/* Loop through the data and display the same in matrix format */
	for( i = 0; i < c; i++ )
	{
		for( j = 0; j < r; j++)
			printf("%.4f\t",data[j*c+i]);
		printf("\n");
	}
	printf("\n");
}

void parse_result(double *x, int *feval, const mxArray *in)
{
	int i, j, r, c ;
	r = mxGetM(in);
	c = mxGetN(in);
	double *temp = NULL, *data ;
	temp = mxGetPr(in);
	data = malloc(sizeof(double) * r);
	for( i = 0; i < c; i++ )
		for( j = 0; j < r; j++)
			data[j] = temp[j*c+i];
	for(i = 0 ; i < nreal ; i++)
		x[i] = data[i] ;
	*feval = ((int)data[r-2]);
	free(data);
	return ;
}

void load_path(char *dest)
{
#ifdef zdt1
	sprintf(dest, "input_data/zdt1.in");
#endif
#ifdef zdt2
	sprintf(dest, "input_data/zdt2.in");
#endif
#ifdef zdt3
	sprintf(dest, "input_data/zdt3.in");
#endif
#ifdef zdt4
	sprintf(dest, "input_data/zdt4.in");
#endif
#ifdef zdt6
	sprintf(dest, "input_data/zdt6.in");
#endif
#ifdef dtlz1
	sprintf(dest, "input_data/dtlz1.in");
#endif
#ifdef dtlz2
	sprintf(dest, "input_data/dtlz2.in");
#endif
#ifdef dtlz3
	sprintf(dest, "input_data/dtlz3.in");
#endif
#ifdef dtlz4
	sprintf(dest, "input_data/dtlz4.in");
#endif
#ifdef dtlz5
	sprintf(dest, "input_data/dtlz5.in");
#endif
#ifdef dtlz6
	sprintf(dest, "input_d`ata/dtlz6.in");
#endif
#ifdef dtlz7
	sprintf(dest, "input_data/dtlz7.in");
#endif

}
