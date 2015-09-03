/* NSGA-II routine (implementation of the 'main' function) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <string.h>

# include "global.h"
# include "rand.h"
# include "opposition.h"
# include "misc.h"

char prob_name[16] ;
int nreal;
int nbin;
int nobj;
int ncon;
int popsize;
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

/* opposition bases stuffs */
float op_ratio = 0.25 ;
int op_popsize;
pop_list *e_star ;

int main (int argc, char **argv)
{
	int i, feval = 0 ;
	char uid_filename[80];
	FILE *fpt_init_pop;
	FILE *fpt_final_pop;
	FILE *fpt_best_pop;
	FILE *fpt_all_pop;
	FILE *fpt_all_oparent;
	FILE *fpt_all_ochild;
	FILE *fpt_all_survived;
	FILE *fpt_all_extreme;
	FILE *fpt_all_survival_stat;
	FILE *fpt_all_overshoot_stat;
	FILE *fpt_params;
	FILE *gp;

	population *parent_pop;
	population *child_pop;
	population *mixed_pop;
	pop_list *op_parent ;
	pop_list *op_child ;

	if (argc<3)
	{
		printf("\n Usage ./onsga2r [problem_name] [random_seed] [outfile-uid] [gnuplot option]\n");
		exit(1);
	}
	
	sprintf(prob_name, "%s", argv[1]);
	fprintf(stdout, "\n Solving problem %s \n", prob_name);

	seed = (double)atof(argv[2]);
	if (seed<=0.0 || seed>=1.0)
	{
		printf("\n Entered seed value is wrong, seed value must be in (0,1) \n");
		exit(1);
	}

	if(argc < 4)
	{
		fpt_init_pop = fopen("initial_pop.out","w");
		fpt_final_pop = fopen("final_pop.out","w");
		fpt_best_pop = fopen("best_pop.out","w");
		fpt_all_pop = fopen("all_pop.out","w");
		fpt_params = fopen("params.out","w");
	}
	else
	{
		sprintf(uid_filename, "initial_pop-%s.out", argv[3]);
		fpt_init_pop = fopen(uid_filename, "w");
		sprintf(uid_filename, "final_pop-%s.out", argv[3]);
		fpt_final_pop = fopen(uid_filename, "w");
		sprintf(uid_filename, "best_pop-%s.out", argv[3]);
		fpt_best_pop = fopen(uid_filename, "w");
		sprintf(uid_filename, "all_pop-%s.out", argv[3]);
		fpt_all_pop = fopen(uid_filename, "w");
		sprintf(uid_filename, "params-%s.out", argv[3]);
		fpt_params = fopen(uid_filename, "w");
	}
	/* oppostion stuff */
	if(argc < 4)
	{
		fpt_all_oparent = fopen("all_op_parent.out","w");
		fpt_all_ochild = fopen("all_op_child.out","w");
		fpt_all_survived = fopen("all_survived.out","w");
		fpt_all_extreme = fopen("all_extreme.out","w");
		fpt_all_survival_stat = fopen("all_survival_stat.out","w");
		fpt_all_overshoot_stat = fopen("all_overshoot_stat.out","w");
	}
	else
	{
		sprintf(uid_filename, "all_op_parent-%s.out", argv[3]);
		fpt_all_oparent = fopen(uid_filename,"w");
		sprintf(uid_filename, "all_op_child-%s.out", argv[3]);
		fpt_all_ochild = fopen(uid_filename,"w");
		sprintf(uid_filename, "all_survived-%s.out", argv[3]);
		fpt_all_survived = fopen(uid_filename,"w");
		sprintf(uid_filename, "all_extreme-%s.out", argv[3]);
		fpt_all_extreme = fopen(uid_filename,"w");
		sprintf(uid_filename, "all_survival_stat-%s.out", argv[3]);
		fpt_all_survival_stat = fopen(uid_filename,"w");
		sprintf(uid_filename, "all_overshoot_stat-%s.out", argv[3]);
		fpt_all_overshoot_stat = fopen(uid_filename,"w");
	}

	fprintf(fpt_init_pop,"# This file contains the data of initial population\n");
	fprintf(fpt_final_pop,"# This file contains the data of final population\n");
	fprintf(fpt_best_pop,"# This file contains the data of final feasible population (if found)\n");
	fprintf(fpt_all_pop,"# This file contains the data of all generations\n");
	fprintf(fpt_params,"# This file contains information about inputs as read by the program\n");
	/* oppostion stuff */
	fprintf(fpt_all_oparent,"# This file contains the opp. parent population\n");
	fprintf(fpt_all_ochild,"# This file contains the opp. child population\n");
	fprintf(fpt_all_survived,"# This file contains the survived population\n");

	printf("\n Enter the problem relevant and algorithm relevant parameters ... ");
	printf("\n Enter the population size (a multiple of 4) : ");
	scanf("%d",&popsize);
	op_popsize = (int)(popsize * op_ratio);
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
	printf("\n Do you want to use gnuplot to display the results realtime (0 for NO) (1 for yes) : ");
	scanf("%d",&choice);
	if(argc == 5) choice = atoi(argv[4]);
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
	/* opposition stuff */
	fprintf(fpt_all_oparent,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	fprintf(fpt_all_ochild,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	fprintf(fpt_all_survived,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
	nbinmut = 0;
	nrealmut = 0;
	nbincross = 0;
	nrealcross = 0;
	parent_pop = (population *)malloc(sizeof(population));
	child_pop = (population *)malloc(sizeof(population));
	mixed_pop = (population *)malloc(sizeof(population));
	allocate_memory_pop (parent_pop, popsize);
	allocate_memory_pop (child_pop, popsize);
	allocate_memory_pop (mixed_pop, 2 * popsize);

	/* for the overshoot stats */
	double overshoot_stat[4] = {0.0, 0.0, 0.0, 0.0};

	randomize();
	initialize_pop (parent_pop);
	/* just to shut the valgrind complains :-( */
	initialize_pop_dummy (child_pop);
		
	printf("\n Initialization done, now performing first generation");
	decode_pop(parent_pop);
	evaluate_pop (parent_pop);
	/* now find the extreme points */	
	feval = init_extreme_pts_hardcoded_weak();
	fprintf(stdout, "****** extreme point computation, total function eval: %d\n", feval);
	/* update the actual feval */
	feval += popsize ;
	
	/* this ranking and crowding dist is not necessary for the actual algorithm */
	assign_rank_and_crowding_distance (parent_pop);
	/* save the initial population before extreme point injection for stat purposes */
	dump_population(fpt_init_pop, parent_pop, popsize);
	fprintf(fpt_all_pop, "# gen = 1\tfe = %d\n", feval);
	dump_population(fpt_all_pop, parent_pop, popsize);
	
	inject_extreme_points(parent_pop);
	assign_rank_and_crowding_distance (parent_pop);

	/* opposition stuff */
	op_parent = new_list();
	op_child = new_list();
	printf("\n *** Will apply opposition based variation.");
	generate_opposite_population(parent_pop, op_parent, op_child, 1, overshoot_stat);
	/* some overshoot stats */
	fprintf(stdout, "\n gen = %4d\tfe = %8d", 1, feval);
	fprintf(stdout, "\tind = %4.2f%%\tgenes/ind = %4.3f",overshoot_stat[0], overshoot_stat[1]);
	fprintf(stdout, "\tmax_gene = %4.2f%%\tno_gene = %4.2f%%\n",overshoot_stat[2], overshoot_stat[3]);
	fprintf(fpt_all_overshoot_stat, "%4d\t%8d\t%4.2f\t%4.3f\t%4.2f\t%4.2f\n",
		1, feval, overshoot_stat[0], overshoot_stat[1], overshoot_stat[2], overshoot_stat[3]);
	/* other stats */
	fprintf(fpt_all_oparent, "# gen = 1\tfe = %d\n", feval);
	dump_pop_list(fpt_all_oparent, op_parent);
	evaluate_pop_list(op_child);
	fprintf(fpt_all_ochild, "# gen = 1\tfe = %d\n", feval);
	dump_pop_list(fpt_all_ochild, op_child);
	fprintf(fpt_all_extreme,"# gen = 1\tfe = %d\n", feval);
	dump_pop_list(fpt_all_extreme, e_star);

	fflush(stdout);
	if (choice!=0)    onthefly_display (parent_pop,gp,1);

	fflush(fpt_init_pop);
	fflush(fpt_final_pop);
	fflush(fpt_best_pop);
	fflush(fpt_all_pop);
	fflush(fpt_params);
	/* opposition stuff */
	fflush(fpt_all_oparent);
	fflush(fpt_all_ochild);
	fflush(fpt_all_survived);
	fflush(fpt_all_extreme);
	fflush(fpt_all_survival_stat);
	fflush(fpt_all_overshoot_stat);

	sleep(1);

	for (i=2; i<=ngen; i++)
	{
		selection (parent_pop, child_pop);

		mutation_pop (child_pop);
		decode_pop(child_pop);

		/**
		 * this "clearing" for child population is required 
		 * for this particular nsga2 source code only, 
		 * not a part of actual algorithm
		 **/
		if(i > 2) clear_opposite_flag(child_pop);
		/* inject opposite after variation */
		inject_opposite_shuffle(op_child, child_pop);
		/* also we need to inject newly found extreme points */
		inject_extreme_points(child_pop);

		evaluate_pop(child_pop);
		feval += popsize ;
		merge(parent_pop, child_pop, mixed_pop);
		fill_nondominated_sort (mixed_pop, parent_pop);

		/* now generate opposite points */
		make_empty(op_child);
		make_empty_ptr(op_parent);
		/* some overshoot stats */
		generate_opposite_population(parent_pop, op_parent, op_child, i, overshoot_stat);
		fprintf(stdout, " gen = %4d\tfe = %8d", i, feval);
		fprintf(stdout, "\tind = %4.2f%%\tgenes/ind = %4.3f",overshoot_stat[0], overshoot_stat[1]);
		fprintf(stdout, "\tmax_gene = %4.2f%%\tno_gene = %4.2f%%\n",overshoot_stat[2], overshoot_stat[3]);
		fprintf(fpt_all_overshoot_stat, "%4d\t%8d\t%4.2f\t%4.3f\t%4.2f\t%4.2f\n", 
			i, feval, overshoot_stat[0], overshoot_stat[1], overshoot_stat[2], overshoot_stat[3]);
		/**
		 * All these stuffs below are only for analysis, not for the algorithm
		 */ 
		fprintf(fpt_all_oparent,"# gen = %d\tfe = %d\n", i, feval);
		dump_pop_list(fpt_all_oparent, op_parent);
		fflush(fpt_all_oparent);
		evaluate_pop_list(op_child);
		fprintf(fpt_all_ochild,"# gen = %d\tfe = %d\n", i, feval);
		dump_pop_list(fpt_all_ochild, op_child);
		fflush(fpt_all_ochild);
		/**
		 * now do some analysis of the opposite solutions
		 * not required for the actual algorithm to work
		 */
		pop_list *survived_pop = new_list();
		gather_survived_individuals(parent_pop, survived_pop);
		fprintf(fpt_all_survival_stat, "\n gen = %d\tfe = %d\tratio = %f\n", (i - 1),
		        (feval - popsize), (survived_pop->size/((float)op_popsize)) * 100.0);
		fprintf(fpt_all_survived,"# gen = %d\tfe = %d\n", (i - 1), (feval - popsize));
		dump_pop_list(fpt_all_survived, survived_pop);
		fflush(fpt_all_survived);
		fflush(fpt_all_survival_stat);
		free_list_ptr(survived_pop);
		/* clear the parent's opposite flags */
		clear_opposite_flag(parent_pop);
		
		fprintf(fpt_all_extreme,"# gen = %d\tfe = %d\n", i, feval);
		dump_pop_list(fpt_all_extreme, e_star);
		fflush(fpt_all_extreme);

		/* 
		 * Comment following four lines if information for all 
		 * generations is not desired, it will speed up the execution 
		 */
		fprintf(fpt_all_pop,"# gen = %d\tfe = %d\n", i, feval);
		dump_population(fpt_all_pop, parent_pop, popsize);
		fflush(fpt_all_pop);

		if (choice!=0)    onthefly_display (parent_pop,gp,i);
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
	/* opposition stuff */
	fflush(fpt_all_oparent);
	fflush(fpt_all_ochild);
	fflush(fpt_all_survived);
	fflush(fpt_all_survival_stat);
	fflush(fpt_all_overshoot_stat);

	fclose(fpt_init_pop);
	fclose(fpt_final_pop);
	fclose(fpt_best_pop);
	fclose(fpt_all_pop);
	fclose(fpt_params);
	/* opposition stuff */
	fclose(fpt_all_oparent);
	fclose(fpt_all_ochild);
	fclose(fpt_all_survived);
	fclose(fpt_all_extreme);
	fclose(fpt_all_survival_stat);
	fclose(fpt_all_overshoot_stat);
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
	deallocate_memory_pop (mixed_pop, 2 * popsize);

	free (parent_pop);
	free (child_pop);
	free (mixed_pop);

	/* opposition based stuff */
	free_list(e_star);
	free_list_ptr(op_parent);
	free_list(op_child);

	printf("\n Routine successfully exited \n");
	return (0);
}
