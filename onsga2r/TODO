How to run these craps.
======================

1. compile:
	do_opposition 1 --> onsga2r
	do_opposition 0 --> nsgar2r

2. generate random seeds:
	./genrseed 10 rseed.in
		-- will create a file in input_data/rseed.in with 10 random seeds

4. burst pf data into generation wise files:
	./burstpf 1 100 all_pop.out snaps
		-- will burst all the collated pf data (all_pop.out) into generation wise pf data
		   (all_pop-gen-*.out)

5. do burstpf over n runs:
	nsga2r: ./burstpfn 1 10 1 100 \
			experiments/nsga2r/zdt1/all_pop- \
			experiments/nsga2r/zdt1/
		-- will generate raw pf snapshots in 
			experiments/nsga2r/zdt1/pfsnaps-run-*/all-pop-1-gen-*.out
	onsga2r: 
	
		(a) ./burstpfn 1 10 1 100 \
			experiments/onsga2r/zdt1/all_pop- \
			experiments/onsga2r/zdt1/
		-- will generate raw pf snapshots in 
			experiments/onsga2r/zdt1/pfsnaps-run-*/all-pop-1-gen-*.out
		
		(b) ./burstpfn 1 10 1 100 \
			experiments/onsga2r/zdt1/all_source- \
			experiments/onsga2r/zdt1/
		-- will generate raw pf snapshots in 
			experiments/onsga2r/zdt1/pfsnaps-run-*/all-source-1-gen-*.out

		(c) ./burstpfn 1 10 1 100 \
			experiments/onsga2r/zdt1/all_opposite- \
			experiments/onsga2r/zdt1/
		-- will generate raw pf snapshots in 
			experiments/onsga2r/zdt1/pfsnaps-run-*/all-opposite-1-gen-*.out
		
		(d) ./burstpfn 1 10 1 100 \
			experiments/onsga2r/zdt1/all_survived- \
			experiments/onsga2r/zdt1/
		-- will generate raw pf snapshots in 
			experiments/onsga2r/zdt1/pfsnaps-run-*/all-survived-1-gen-*.out

5. make plots from those snapshots:
	./genplots 1 100 \
		experiments/onsga2r/zdt1/pfplots-run-1 \
		experiments/nsga2r/zdt1/pfsnaps-run-1/all_pop-1-gen- \
		experiments/onsga2r/zdt1/pfsnaps-run-1/all_pop-1-gen- \
		experiments/onsga2r/zdt1/pfsnaps-run-1/all_source-1-gen- \
		experiments/onsga2r/zdt1/pfsnaps-run-1/all_opposite-1-gen- \
		experiments/onsga2r/zdt1/pfsnaps-run-1/all_survived-1-gen-
	-- all the superimposed plots will stored in experiments/onsga2r/zdt1/pfplots-run-1

7. generate a pdf summary:
	./genreport 1 100 experiments/onsga2r/zdt1/pfplots-run-1/ 5 8 0.4 pf-gen
		-- generates pdf in the current terminal location, the file name prefix, i.e. pf-gen
		   needs to be confirmed before running this script.

10. compute hypervolume for a single run:
	./calchv 1 100 experiments/nsga2r/zdt1/pfsnaps-run-1/all_pop-1-gen- \
		       experiments/nsga2r/zdt1/ whv/zdt1-param.txt
		-- generate hypervolume data for each generation for run 1 in 
		   experiments/nsga2r/zdt1/hv folder.

11. compute hypervolume for multiple runs:
	nsga2r:	./calchvn 1 10 1 100 experiments/nsga2r/zdt1/pfsnaps-run- \
			     experiments/nsga2r/zdt1/ whv/zdt1-param.txt
	onsga2r: ./calchvn 1 10 1 100 experiments/onsga2r/zdt1/pfsnaps-run- \
			     experiments/onsga2r/zdt1/ whv/zdt1-param.txt
	-- generate hypervolume data for each generation for all runs 
	   in experiments/zdt1/hv folder.

12. generate hv stats:
	./hvstat  1 10 experiments/nsga2r/zdt6/hv/hv-run- experiments/onsga2r/zdt6/hv/hv-run- 5
		-- plots will be stored in experiments/onsga2r/zdt6/hv folder.
	
===================================================================================================
** 3. run n multiple experiments:
	nsga2r: ./sh/run-n 1 10 nsga2r-zdt1 input_data/zdt1.in input_data/rseeds.in experiments
		-- will generate experiments/nsga2r/zdt1/all_pop-*.out

	onsga2r: ./sh/run-n 1 10 onsga2r-zdt1 input_data/zdt1.in input_data/rseeds.in experiments
		-- will generate experiments/onsga2r/zdt1/all_pop-*.out
		-- will generate experiments/onsga2r/zdt1/all_source-*.out
		-- will generate experiments/onsga2r/zdt1/all_opposite-*.out
		-- will generate experiments/onsga2r/zdt1/all_survival-*.out

** 4. do the above for in single snap:
	./sh/burstpfall zdt1 1 10 1 200
		-- do the above in single snap.

** 6. make plots from all the runs:
	./sh/genplotsn 1 10 1 200 zdt1
		-- do the same as above from run 1 to run 10.

** 8. generate pdf summary for all individual runs:
	./sh/genreportn 1 10 1 200 5 8 0.4 zdt1
		-- do the same as above from run 1 to run 10
	
** 9. generate statistical results for survival:
	./survivalstat 1 10 experiments/onsga2r/zdt4/all_survival_stat- 5
		-- generates a file for boxplot data, two pdf plots in experiments/onsga2r/zdt4/
		   boxplots will be skipped every 5 generation intervals.

** 13. do 11 and 12:
	./hvstatall zdt1 1 10 1 200
		-- do number 11 and 12 serially.

======================================= TODO ======================================================
1. fix makefile (changing header does not recompile the source)
1. implement rga
2. do euclidean dist in crowd_dist (done, slightly better in 3 obj)
3. fix the extreme point update with weak domination (just apply non-dominated sort on E)
======================================= TODO ======================================================
4. change rng call to make identical initial pop
5. replace rga with fmincon
6. implement modified dtlz problems wihtout weak points
7. merge 3 way plots -- nsga2+extreme, onsga2, nsga2+no-extreme + FE eval to fins extremes
8. rewrite scripts in python, numpy and matplotlib
9. change the nsga2r/onsga2r and scripts in such a way that they can be run in parallel
10. clean up code
11. compare with reference HV measure, to compute the reference HV use the ideal front from ETHZurich's site.























































































































































































































































































































































































http://xhamster.com/movies/2675224/a_frustration_mom_and_a_boy_2.html
