# include <string.h>
# include "sosolver.h"
# include "global.h"
# include "problemdef.h"
# include "poplist.h"
# include "misc.h"
# include "libsosolver.h"

int nreal ;
int nobj ;
char prob_name[16] ;
	
int sosolver(pop_list *lst, double seed)
{
	char path_str[80] ;
	individual ind ;
	int i, fe, feval = 0 ;
	
	mclmcrInitialize();

	mxArray *result = NULL ;
	mxArray *file_path = NULL;
	mxArray *findex = NULL ;
	mxArray *seed_val = NULL ;

	if(!mclInitializeApplication(NULL,0))
	{
	    	fprintf(stdout, "sosolver(): Could not initialize the application.\n");
		return -1;
	}

	if (!libsosolverInitialize())
	{
		fprintf(stdout,"sosolver(): Could not initialize the library.\n");
		return -2;
	}
	else
	{
		load_path(path_str);
		fprintf(stdout, "sosolver(): path_str = %s\n", path_str);
		file_path = mxCreateString(path_str);
		seed_val = mxCreateDoubleScalar((int)(seed * 1000.0));
		for(i = 0 ; i < nobj ; i++)
		{
			findex = mxCreateDoubleScalar(i+1);
			mlfSosolver(1, &result, file_path, findex, seed_val);
			/*display(result);*/
			allocate_memory_ind(&ind); initialize_ind_dummy(&ind);
			parse_result(ind.xreal, &fe, result);
			evaluate_ind(&ind);
			fprintf(stdout, "sosolver(): ");
			dumpf_individual(stdout, &ind);
			push_back(lst, &ind);
			feval += fe ;
			mxDestroyArray(result); result = NULL ;
			mxDestroyArray(findex); findex = NULL ;
		}
		fprintf(stdout, "sosolver(): feval = %d\n", feval);
		libsosolverTerminate();
		mxDestroyArray(file_path); file_path = NULL ;
		mxDestroyArray(seed_val); seed_val = NULL ;
	}

	mclTerminateApplication();
	return feval ;
}

int sosolver_weighted(pop_list *lst, double seed)
{
	char path_str[80] ;
	individual ind ;
	int fe, feval = 0 ;
	
	mclmcrInitialize();

	mxArray *result = NULL ;
	mxArray *file_path = NULL;
	mxArray *findex = NULL ;
	mxArray *seed_val = NULL ;

	if(!mclInitializeApplication(NULL,0))
	{
	    	fprintf(stdout, "sosolver_weighted(): Could not initialize the application.\n");
		return -1;
	}

	if (!libsosolverInitialize())
	{
		fprintf(stdout,"sosolver_weighted(): Could not initialize the library.\n");
		return -2;
	}
	else
	{
		load_path(path_str);
		fprintf(stdout, "sosolver_weighted(): path_str = %s\n", path_str);
		file_path = mxCreateString(path_str);
		seed_val = mxCreateDoubleScalar((int)(seed * 1000.0));
		findex = mxCreateDoubleScalar(-1);
		mlfSosolver(1, &result, file_path, findex, seed_val);
		/* display(result); */
		allocate_memory_ind(&ind); initialize_ind_dummy(&ind);
		parse_result(ind.xreal, &fe, result);
		evaluate_ind(&ind);
		fprintf(stdout, "sosolver_weighted(): ");
		dumpf_individual(stdout, &ind);
		push_back(lst, &ind);
		feval += fe ;
		mxDestroyArray(result); result = NULL ;
		mxDestroyArray(findex); findex = NULL ;
		fprintf(stdout, "sosolver_weighted(): feval = %d\n", feval);
		libsosolverTerminate();
		mxDestroyArray(file_path); file_path = NULL ;
		mxDestroyArray(seed_val); seed_val = NULL ;
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
	fprintf(stdout, "display(): row = %d, col = %d\n", r, c);
	/* Get a pointer to the double data in mxArray */
	data = mxGetPr(in);

	/* Loop through the data and display the same in matrix format */
	fprintf(stdout, "display(): ");
	for( i = 0; i < c; i++ )
	{
		for( j = 0; j < r ; j++)
			printf("%8.4f ",data[j*c+i]);
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
	/*fprintf(stdout, "parse_result(): ");
	for( i = 0; i < c; i++ )
	{
		for( j = 0; j < r; j++)
			printf("%8.4f ",data[j*c+i]);
		printf("\n");
	}*/
	for(i = 0 ; i < nreal ; i++)
		x[i] = data[i] ;
	*feval = ((int)data[r-2]);
	free(data);
	return ;
}

void load_path(char *dest)
{
	if(strcmp(prob_name, "zdt1") == 0)
		sprintf(dest, "input_data/zdt1.in");
	else if(strcmp(prob_name, "zdt2") == 0)
		sprintf(dest, "input_data/zdt2.in");
	else if(strcmp(prob_name, "zdt3") == 0)
		sprintf(dest, "input_data/zdt3.in");
	else if(strcmp(prob_name, "zdt4") == 0)
		sprintf(dest, "input_data/zdt4.in");
	else if(strcmp(prob_name, "zdt6") == 0)
		sprintf(dest, "input_data/zdt6.in");
	else if(strcmp(prob_name, "dtlz1") == 0)
		sprintf(dest, "input_data/dtlz1.in");
	else if(strcmp(prob_name, "dtlz2") == 0)
		sprintf(dest, "input_data/dtlz2.in");
	else if(strcmp(prob_name, "dtlz3") == 0)
		sprintf(dest, "input_data/dtlz3.in");
	else if(strcmp(prob_name, "dtlz4") == 0)
		sprintf(dest, "input_data/dtlz4.in");
	else if(strcmp(prob_name, "dtlz5") == 0)
		sprintf(dest, "input_data/dtlz5.in");
	else if(strcmp(prob_name, "dtlz6") == 0)
		sprintf(dest, "input_data/dtlz6.in");
	else if(strcmp(prob_name, "dtlz7") == 0)
		sprintf(dest, "input_data/dtlz7.in");
	else if(strcmp(prob_name, "osy") == 0)
		sprintf(dest, "input_data/osy.in");
	else if(strcmp(prob_name, "ctp4") == 0)
		sprintf(dest, "input_data/ctp4.in");
	else
	{
		fprintf(stdout, " Error: wrong problem string or problem not defined. \n");
		exit(1);
	}
}
