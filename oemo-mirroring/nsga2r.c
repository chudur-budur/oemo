/* NSGA-II routine (implementation of the 'main' function) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# include "global.h"
# include "rand.h"

int nreal;
int nbin;
int nobj;
int ncon;
int popsize;
float opposite_proportion = 0.25 ;
int opposite_popsize;
int opposite_count ;
double pcross_real;
double pcross_bin;
double pmut_real;
double pmut_bin;
double eta_c;
double eta_m;
int ngen;
int nbinmut;
int nrealmut;
int nbincross;
int nrealcross;
int *nbits;
double *min_realvar;
double *max_realvar;
double *min_binvar;
double *max_binvar;
int bitlength;
int choice;
int obj1;
int obj2;
int obj3;
int angle1;
int angle2;


#define do_opposition 1 /*0 no opposition, 1 with opposition*/
#define pUqUo 0
#define qUo 1
#define interval 0
#define archive 0
#define attractor 1

#define invoke_gnuplot 0 /* 0 no gnuplot, 1 invoke gnuplot */
#define debug 0 /* debug switch */

/*int main_ (int,char**);*/

int main (int argc, char **argv)
/*int main_ (int argc, char **argv)*/
{
	int i;
	double corrupted_genes = 0.0;
	FILE *fpt_init_pop;
	FILE *fpt_final_pop;
	FILE *fpt_best_pop;
	FILE *fpt_all_pop;
	FILE *fpt_all_source;
	FILE *fpt_all_opposite;
	FILE *fpt_all_survived;
	FILE *fpt_all_survival_stat;
	FILE *fpt_params;
	FILE *gp;
	
	population *parent_pop;
	population *child_pop;
	population *mixed_pop;
	population *opposite_source_pop;
	population *opposite_pop;
	
	if (argc<2)
	{
		if(!do_opposition)
			printf("\n Usage ./nsga2r random_seed \n");
		else
			printf("\n Usage ./onsga2r random_seed \n");
		exit(1);		
	}

	seed = (double)atof(argv[1]);
	if (seed<=0.0 || seed>=1.0)
	{
		printf("\n Entered seed value is wrong, seed value must be in (0,1) \n");
		exit(1);
	}
	
	fpt_init_pop = fopen("initial_pop.out","w");
	fpt_final_pop = fopen("final_pop.out","w");
	fpt_best_pop = fopen("best_pop.out","w");
	fpt_all_pop = fopen("all_pop.out","w");
	fpt_params = fopen("params.out","w");
	if(do_opposition) {
		fpt_all_source = fopen("all_source.out","w");
		fpt_all_opposite = fopen("all_opposite.out","w");
		fpt_all_survived = fopen("all_survived.out","w");
		fpt_all_survival_stat = fopen("all_survival_stat.out","w");
	}

	fprintf(fpt_init_pop,"# This file contains the data of initial population\n");
	fprintf(fpt_final_pop,"# This file contains the data of final population\n");
	fprintf(fpt_best_pop,"# This file contains the data of final feasible population (if found)\n");
	fprintf(fpt_all_pop,"# This file contains the data of all generations\n");
	if(do_opposition) {
		fprintf(fpt_all_source,"# This file contains the source population\n");
		fprintf(fpt_all_opposite,"# This file contains the opposite population\n");
		fprintf(fpt_all_survived,"# This file contains the sruvived population\n");
	}
	fprintf(fpt_params,"# This file contains information about inputs as read by the program\n");

	printf("\n Enter the problem relevant and algorithm relevant parameters ... ");
	printf("\n Enter the population size (a multiple of 4) : ");
	scanf("%d",&popsize);
	if(do_opposition) opposite_popsize = (int)(popsize * opposite_proportion);
	if (popsize<4 || (popsize%4)!= 0)
	{
		printf("\n population size read is : %d",popsize);
		printf("\n Wrong population size entered, hence exiting \n");
		exit (1);
	}
	printf("\n Enter the number of generations : ");
	scanf("%d",&ngen);
	if (ngen<1)
	{
		printf("\n number of generations read is : %d",ngen);
		printf("\n Wrong nuber of generations entered, hence exiting \n");
		exit (1);
	}
	printf("\n Enter the number of objectives : ");
	scanf("%d",&nobj);
	if (nobj<1)
	{
		printf("\n number of objectives entered is : %d",nobj);
		printf("\n Wrong number of objectives entered, hence exiting \n");
		exit (1);
	}
	printf("\n Enter the number of constraints : ");
	scanf("%d",&ncon);
	if (ncon<0)
	{
		printf("\n number of constraints entered is : %d",ncon);
		printf("\n Wrong number of constraints enetered, hence exiting \n");
		exit (1);
	}
	printf("\n Enter the number of real variables : ");
	scanf("%d",&nreal);
	if (nreal<0)
	{
		printf("\n number of real variables entered is : %d",nreal);
		printf("\n Wrong number of variables entered, hence exiting \n");
		exit (1);
	}
	if (nreal != 0)
	{
		min_realvar = (double *)malloc(nreal*sizeof(double));
		max_realvar = (double *)malloc(nreal*sizeof(double));
		for (i=0; i<nreal; i++)
		{
			printf ("\n Enter the lower limit of real variable %d : ",i+1);
			scanf ("%lf",&min_realvar[i]);
			printf ("\n Enter the upper limit of real variable %d : ",i+1);
			scanf ("%lf",&max_realvar[i]);
			if (max_realvar[i] <= min_realvar[i])
			{
				printf("\n Wrong limits entered for the min and max bounds of real variable, hence exiting \n");
				exit(1);
			}
		}
		printf ("\n Enter the probability of crossover of real variable (0.6-1.0) : ");
		scanf ("%lf",&pcross_real);
		if (pcross_real<0.0 || pcross_real>1.0)
		{
			printf("\n Probability of crossover entered is : %e",pcross_real);
			printf("\n Entered value of probability of crossover of real variables is out of bounds, hence exiting \n");
			exit (1);
		}
		printf ("\n Enter the probablity of mutation of real variables (1/nreal) : ");
		scanf ("%lf",&pmut_real);
		if (pmut_real<0.0 || pmut_real>1.0)
		{
			printf("\n Probability of mutation entered is : %e",pmut_real);
			printf("\n Entered value of probability of mutation of real variables is out of bounds, hence exiting \n");
			exit (1);
		}
		printf ("\n Enter the value of distribution index for crossover (5-20): ");
		scanf ("%lf",&eta_c);
		if (eta_c<=0)
		{
			printf("\n The value entered is : %e",eta_c);
			printf("\n Wrong value of distribution index for crossover entered, hence exiting \n");
			exit (1);
		}
		printf ("\n Enter the value of distribution index for mutation (5-50): ");
		scanf ("%lf",&eta_m);
		if (eta_m<=0)
		{
			printf("\n The value entered is : %e",eta_m);
			printf("\n Wrong value of distribution index for mutation entered, hence exiting \n");
			exit (1);
		}
	}
	printf("\n Enter the number of binary variables : ");
	scanf("%d",&nbin);
	if (nbin<0)
	{
		printf ("\n number of binary variables entered is : %d",nbin);
		printf ("\n Wrong number of binary variables entered, hence exiting \n");
		exit(1);
	}
	if (nbin != 0)
	{
		nbits = (int *)malloc(nbin*sizeof(int));
		min_binvar = (double *)malloc(nbin*sizeof(double));
		max_binvar = (double *)malloc(nbin*sizeof(double));
		for (i=0; i<nbin; i++)
		{
			printf ("\n Enter the number of bits for binary variable %d : ",i+1);
			scanf ("%d",&nbits[i]);
			if (nbits[i] < 1)
			{
				printf("\n Wrong number of bits for binary variable entered, hence exiting");
				exit(1);
			}
			printf ("\n Enter the lower limit of binary variable %d : ",i+1);
			scanf ("%lf",&min_binvar[i]);
			printf ("\n Enter the upper limit of binary variable %d : ",i+1);
			scanf ("%lf",&max_binvar[i]);
			if (max_binvar[i] <= min_binvar[i])
			{
				printf("\n Wrong limits entered for the min and max bounds of binary variable entered, hence exiting \n");
				exit(1);
			}
		}
		printf ("\n Enter the probability of crossover of binary variable (0.6-1.0): ");
		scanf ("%lf",&pcross_bin);
		if (pcross_bin<0.0 || pcross_bin>1.0)
		{
			printf("\n Probability of crossover entered is : %e",pcross_bin);
			printf("\n Entered value of probability of crossover of binary variables is out of bounds, hence exiting \n");
			exit (1);
		}
		printf ("\n Enter the probability of mutation of binary variables (1/nbits): ");
		scanf ("%lf",&pmut_bin);
		if (pmut_bin<0.0 || pmut_bin>1.0)
		{
			printf("\n Probability of mutation entered is : %e",pmut_bin);
			printf("\n Entered value of probability  of mutation of binary variables is out of bounds, hence exiting \n");
			exit (1);
		}
	}
	if (nreal==0 && nbin==0)
	{
		printf("\n Number of real as well as binary variables, both are zero, hence exiting \n");
		exit(1);
	}
	choice=0;
	printf("\n Do you want to use gnuplot to display the results realtime (0 for NO) (1 for yes) : ");
	scanf("%d",&choice);
	if(invoke_gnuplot)
		choice = 1 ;
	else
		choice = 0 ;
	if (choice!=0 && choice!=1)
	{
		printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",choice);
		exit(1);
	}
	if (choice==1)
	{
		gp = popen(GNUPLOT_COMMAND,"w");
		if (gp==NULL)
		{
			printf("\n Could not open a pipe to gnuplot, check the definition of GNUPLOT_COMMAND in file global.h\n");
			printf("\n Edit the string to suit your system configuration and rerun the program\n");
			exit(1);
		}
		if (nobj==2)
		{
			printf("\n Enter the objective for X axis display : ");
			scanf("%d",&obj1);
			if (obj1<1 || obj1>nobj)
			{
				printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
				exit(1);
			}
			printf("\n Enter the objective for Y axis display : ");
			scanf("%d",&obj2);
			if (obj2<1 || obj2>nobj)
			{
				printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
				exit(1);
			}
			obj3 = -1;
		}
		else
		{
			printf("\n #obj > 2, 2D display or a 3D display ?, enter 2 for 2D and 3 for 3D :");
			scanf("%d",&choice);
			if (choice!=2 && choice!=3)
			{
				printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",choice);
				exit(1);
			}
			if (choice==2)
			{
				printf("\n Enter the objective for X axis display : ");
				scanf("%d",&obj1);
				if (obj1<1 || obj1>nobj)
				{
					printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
					exit(1);
				}
				printf("\n Enter the objective for Y axis display : ");
				scanf("%d",&obj2);
				if (obj2<1 || obj2>nobj)
				{
					printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
					exit(1);
				}
				obj3 = -1;
			}
			else
			{
				printf("\n Enter the objective for X axis display : ");
				scanf("%d",&obj1);
				if (obj1<1 || obj1>nobj)
				{
					printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
					exit(1);
				}
				printf("\n Enter the objective for Y axis display : ");
				scanf("%d",&obj2);
				if (obj2<1 || obj2>nobj)
				{
					printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
					exit(1);
				}
				printf("\n Enter the objective for Z axis display : ");
				scanf("%d",&obj3);
				if (obj3<1 || obj3>nobj)
				{
					printf("\n Wrong value of Z objective entered, value entered was %d\n",obj3);
					exit(1);
				}
				printf("\n You have chosen 3D display, hence location of eye required \n");
				printf("\n Enter the first angle (an integer in the range 0-180) (if not known, enter 60) :");
				scanf("%d",&angle1);
				if (angle1<0 || angle1>180)
				{
					printf("\n Wrong value for first angle entered, hence exiting \n");
					exit(1);
				}
				printf("\n Enter the second angle (an integer in the range 0-360) (if not known, enter 30) :");
				scanf("%d",&angle2);
				if (angle2<0 || angle2>360)
				{
					printf("\n Wrong value for second angle entered, hence exiting \n");
					exit(1);
				}
			}
		}
	}
	printf("\n Input data successfully entered, now performing initialization \n");
	fprintf(fpt_params,"\n Population size = %d",popsize);
	fprintf(fpt_params,"\n Number of generations = %d",ngen);
	fprintf(fpt_params,"\n Number of objective functions = %d",nobj);
	fprintf(fpt_params,"\n Number of constraints = %d",ncon);
	fprintf(fpt_params,"\n Number of real variables = %d",nreal);
	if (nreal!=0)
	{
		for (i=0; i<nreal; i++)
		{
			fprintf(fpt_params,"\n Lower limit of real variable %d = %e",i+1,min_realvar[i]);
			fprintf(fpt_params,"\n Upper limit of real variable %d = %e",i+1,max_realvar[i]);
		}
		fprintf(fpt_params,"\n Probability of crossover of real variable = %e",pcross_real);
		fprintf(fpt_params,"\n Probability of mutation of real variable = %e",pmut_real);
		fprintf(fpt_params,"\n Distribution index for crossover = %e",eta_c);
		fprintf(fpt_params,"\n Distribution index for mutation = %e",eta_m);
	}
	fprintf(fpt_params,"\n Number of binary variables = %d",nbin);
	if (nbin!=0)
	{
		for (i=0; i<nbin; i++)
		{
			fprintf(fpt_params,"\n Number of bits for binary variable %d = %d",i+1,nbits[i]);
			fprintf(fpt_params,"\n Lower limit of binary variable %d = %e",i+1,min_binvar[i]);
			fprintf(fpt_params,"\n Upper limit of binary variable %d = %e",i+1,max_binvar[i]);
		}
		fprintf(fpt_params,"\n Probability of crossover of binary variable = %e",pcross_bin);
		fprintf(fpt_params,"\n Probability of mutation of binary variable = %e",pmut_bin);
	}
	fprintf(fpt_params,"\n Seed for random number generator = %e",seed);
	bitlength = 0;
	if (nbin!=0)
	{
		for (i=0; i<nbin; i++)
		{
			bitlength += nbits[i];
		}
	}
	fprintf(fpt_init_pop,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	fprintf(fpt_final_pop,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	fprintf(fpt_best_pop,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	fprintf(fpt_all_pop,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	if(do_opposition) {
		fprintf(fpt_all_source,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
		fprintf(fpt_all_opposite,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
		fprintf(fpt_all_survived,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	}
	nbinmut = 0;
	nrealmut = 0;
	nbincross = 0;
	nrealcross = 0;

	parent_pop = (population *)malloc(sizeof(population));
	child_pop = (population *)malloc(sizeof(population));
	mixed_pop = (population *)malloc(sizeof(population));
	if(do_opposition) {
		opposite_pop = (population *)malloc(sizeof(population));
		opposite_source_pop = (population *)malloc(sizeof(population));
	}
	
	allocate_memory_pop (parent_pop, popsize);
	allocate_memory_pop (child_pop, popsize);

	if(!do_opposition)
		allocate_memory_pop (mixed_pop, 2 * popsize); 
	else
	{
		if(pUqUo)
			allocate_memory_pop (mixed_pop, (2 * popsize + opposite_popsize)); 
		if(qUo)
			allocate_memory_pop (mixed_pop, 2 * popsize); 
	}

	if(do_opposition) { 
		allocate_memory_pop (opposite_pop, opposite_popsize);
		allocate_memory_pop (opposite_source_pop, opposite_popsize);
	}
	
	randomize();
	initialize_pop (parent_pop);
	if(do_opposition) {
		initialize_pop_with_size (opposite_pop, opposite_popsize);
		initialize_pop_with_size (opposite_source_pop, opposite_popsize);
	}
	
	printf("\n Initialization done, now performing first generation");
	decode_pop(parent_pop);
	evaluate_pop (parent_pop);
	assign_rank_and_crowding_distance (parent_pop);
	
	if(do_opposition)
	{
		printf("\n *** Will apply opposition based variation.");
		if(interval)
		{
			if(archive)
				corrupted_genes = generate_opposite_population_interval_from_archive(
						parent_pop, popsize, opposite_source_pop, 
						opposite_pop, opposite_popsize, 4, 1); 
			else
				corrupted_genes = generate_opposite_population_interval(
						parent_pop, popsize, opposite_source_pop, 
						opposite_pop, opposite_popsize, 4);
		}
		else if(attractor)
			corrupted_genes = generate_opposite_population_using_attractor(
						parent_pop, popsize, opposite_source_pop, 
						opposite_pop, opposite_popsize,1); 
		else
			corrupted_genes = generate_opposite_population(parent_pop, popsize, 
					opposite_source_pop, opposite_pop, opposite_popsize); 
		fprintf(stdout, "\n gen = 1\tcorrupted_genes = %.2f\n", corrupted_genes);
		/* this evaluation below is not necessary for the original algorithm */
		evaluate_pop_with_size(opposite_pop, opposite_popsize);
	}
	
	report_pop (parent_pop, fpt_init_pop);
	fprintf(fpt_all_pop,"# gen = 1\n");
	report_pop(parent_pop, fpt_all_pop);
	if(do_opposition)
	{
		fprintf(fpt_all_source,"# gen = 1\n");
		dump_population(opposite_source_pop, opposite_popsize, fpt_all_source);
		fprintf(fpt_all_opposite,"# gen = 1\n");
		dump_population(opposite_pop, opposite_popsize, fpt_all_opposite);
	}
	
	printf("\n gen = 1");

	if(debug)
	{
		fprintf(stdout, "\n gen = 1, parent_pop:\n");
		dump_population(parent_pop, popsize, stdout);
		if(do_opposition) {
			fprintf(stdout, "\n gen = 1, opposite_source_pop:\n");
			dump_population(opposite_source_pop, opposite_popsize, stdout);
			fprintf(stdout, " gen = 1, opposite_pop:\n");
			dump_population(opposite_pop, opposite_popsize, stdout);
		}
	}
	
	fflush(stdout);
	if (choice!=0)    onthefly_display (parent_pop,gp,1);
	
	fflush(fpt_init_pop);
	fflush(fpt_final_pop);
	fflush(fpt_best_pop);
	fflush(fpt_all_pop);
	fflush(fpt_params);
	if(do_opposition)
	{
		fflush(fpt_all_source);
		fflush(fpt_all_opposite);
	}
	
	sleep(1);
	printf("\n");
		
	for (i=2; i<=ngen; i++)
	/* for (i=2; i<=2; i++) */
	{
		selection (parent_pop, child_pop);
		
		mutation_pop (child_pop);
		decode_pop(child_pop);
			
		/* this is required for some versions of the algorithm to work */
		clear_opposite_flag(child_pop, popsize); 
		
		/* inject opposite after variation */
		if(do_opposition)
		{
			if(qUo)
			{
				/* the i > 2 condition is for pareto-based extreme points */ 
				/*if (i > 2)*/
				{
					/* inject_opposite(opposite_pop, opposite_popsize, child_pop);*/
					inject_opposite_shuffle(opposite_pop, opposite_popsize, 
							child_pop, popsize);
				}
			}
		}
		
		/* inject_spread(child_pop, popsize); */
		evaluate_pop(child_pop);
		
		if(!do_opposition)
			merge(parent_pop, child_pop, mixed_pop);
		else
		{
			if(pUqUo)
				merge_with_size(parent_pop, popsize, 
					child_pop, popsize, 
					opposite_pop, opposite_popsize, 
					mixed_pop, (2 * popsize + opposite_popsize));
			if(qUo)
				merge(parent_pop, child_pop, mixed_pop);
		}

		if(debug)
		{
			fprintf(stdout, " gen = %d, mixed_pop:\n", i);
			dump_population(mixed_pop, 2 * popsize, stdout); 
			/* dump_population(mixed_pop, (2 * popsize + opposite_popsize), stdout); */
		}

		if(!do_opposition) 
			fill_nondominated_sort (mixed_pop, parent_pop);
		else
		{
			if(pUqUo)
				fill_nondominated_sort_with_size (mixed_pop, 
								(2 * popsize + opposite_popsize), 
								parent_pop, popsize);
			if(qUo)
				fill_nondominated_sort (mixed_pop, parent_pop);
		}

		if(debug)
		{
			fprintf(stdout, " gen = %d, parent_pop (after sort):\n", i);
			dump_population(parent_pop, popsize, stdout);
		}
		
		if(do_opposition)
		{
			opposite_count = count_opposite(parent_pop, popsize);
			
			pop_list *survived_pop = new_list(); 
			gather_survived_individuals(parent_pop, popsize, survived_pop);

			fprintf(fpt_all_survival_stat, "\n gen = %d\tratio = %f\n", 
					i-1, (opposite_count/((float)opposite_popsize)) * 100.0);
			clear_opposite_flag(parent_pop, popsize); 
			
			if(interval)
			{
				if(archive)
					corrupted_genes = generate_opposite_population_interval_from_archive(
							parent_pop, popsize, opposite_source_pop, 
							opposite_pop, opposite_popsize, 4, i); 
				else
					corrupted_genes = generate_opposite_population_interval(
							parent_pop, popsize, opposite_source_pop, 
							opposite_pop, opposite_popsize, 4);
			}
			else if(attractor)
				corrupted_genes = generate_opposite_population_using_attractor(
							parent_pop, popsize, opposite_source_pop, 
							opposite_pop, opposite_popsize, i); 
			else	
				corrupted_genes = generate_opposite_population(parent_pop, popsize, 
						opposite_source_pop, opposite_pop, opposite_popsize); 
			fprintf(stdout, "\n gen = %d\tcorrupted_genes = %.2f\n", i, corrupted_genes);
			/**
			 * now dump the opposite stuffs for analysis, the evaluation
			 * and the extra sorting is not required for the actual algorithm
			 */
			evaluate_pop_with_size(opposite_pop, opposite_popsize);			
			
			fprintf(fpt_all_source,"# gen = %d\n",i);
			dump_population(opposite_source_pop, opposite_popsize, fpt_all_source);
			fflush(fpt_all_source);	
			fprintf(fpt_all_opposite,"# gen = %d\n",i);
			dump_population(opposite_pop, opposite_popsize, fpt_all_opposite);
			fflush(fpt_all_opposite);
			if(debug)
			{
				fprintf(stdout," gen = %d, opposite_source_pop:\n",i);
				dump_population(opposite_source_pop, opposite_popsize, stdout);
				fprintf(stdout," gen = %d, opposite_pop:\n",i);
				dump_population(opposite_pop, opposite_popsize, stdout);
				fflush(stdout);
			}

			fprintf(fpt_all_survived,"# gen = %d\n",i-1);
			dump_population_list(survived_pop, fpt_all_survived);
			if(debug)
			{
				fprintf(stdout, " gen = %d, survived_pop (after sort):\n", i-1);
				dump_population_list(survived_pop, stdout);
				fflush(stdout);
			}
			free_list(survived_pop);
			fflush(fpt_all_survived);
		}
		
		/* Comment following four lines if information for all
		generations is not desired, it will speed up the execution */
		fprintf(fpt_all_pop,"# gen = %d\n",i);
		report_pop(parent_pop,fpt_all_pop);
		fflush(fpt_all_pop);

		if (choice!=0)    onthefly_display (parent_pop,gp,i);
		fprintf(stdout, "\n gen = %d",i);
		fflush(stdout);
	}
	
	printf("\n Generations finished, now reporting solutions");
	report_pop(parent_pop,fpt_final_pop);
	report_feasible(parent_pop,fpt_best_pop);
	
	if (nreal!=0)
	{
		fprintf(fpt_params,"\n Number of crossover of real variable = %d",nrealcross);
		fprintf(fpt_params,"\n Number of mutation of real variable = %d",nrealmut);
	}
	if (nbin!=0)
	{
		fprintf(fpt_params,"\n Number of crossover of binary variable = %d",nbincross);
		fprintf(fpt_params,"\n Number of mutation of binary variable = %d",nbinmut);
	}
	
	fflush(stdout);
	fflush(fpt_init_pop);
	fflush(fpt_final_pop);
	fflush(fpt_best_pop);
	fflush(fpt_all_pop);
	fflush(fpt_params);
	if(do_opposition)
	{
		fflush(fpt_all_source);
		fflush(fpt_all_opposite);
		fflush(fpt_all_survived);
		fflush(fpt_all_survival_stat);
	}

	fclose(fpt_init_pop);
	fclose(fpt_final_pop);
	fclose(fpt_best_pop);
	fclose(fpt_all_pop);
	fclose(fpt_params);
	if(do_opposition)
	{
		fclose(fpt_all_source);
		fclose(fpt_all_opposite);
		fclose(fpt_all_survived);
		fclose(fpt_all_survival_stat);
	}
	if (choice!=0)
	{
		pclose(gp);
	}
	if (nreal!=0)
	{
		free (min_realvar);
		free (max_realvar);
	}
	if (nbin!=0)
	{
		free (min_binvar);
		free (max_binvar);
		free (nbits);
	}
	
	deallocate_memory_pop (parent_pop, popsize);
	deallocate_memory_pop (child_pop, popsize);

	if(!do_opposition)
		deallocate_memory_pop (mixed_pop, 2 * popsize); 
	else
	{
		if(pUqUo)
			deallocate_memory_pop (mixed_pop, (2 * popsize + opposite_popsize)); 
		if(qUo)
			deallocate_memory_pop (mixed_pop, 2 * popsize); 
	}
	
	if(do_opposition) {
		deallocate_memory_pop (opposite_pop, opposite_popsize);
		deallocate_memory_pop (opposite_source_pop, opposite_popsize);
	}
	
	free (parent_pop);
	free (child_pop);
	free (mixed_pop);
	if(do_opposition) {
		free (opposite_pop);
		free (opposite_source_pop);
	}
	
	printf("\n Routine successfully exited \n");
	return (0);
}
