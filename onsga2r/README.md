oemo-mirroring
==============

Experiments with opposition based emo with mirroring.

#### How to compile the classical search component:
This part is written in MATLAB (R2014a), extensively using `fmincon()` and `patternsearch()`. All the related matlab scripts could be found in `src/sosolver` and the wrapper function is in `src/sosolver.c` and `src/sosolver.h`. To compile and run this part, you need to add `$matlabhome/runtime/glnxa64` and `$matlabhome/bin/glnxa64` to `$LD_LIBRARY_PATH`. So there is goes -- 

##### 1. To build the whole application, first you need to build the matlab's single obj. optimization solver
```
	make sosolv
```

##### 2. cleaning up the so-solver
```
	make clean-sosolv
```

Now you can build the main code --


##### 3. building the main code (nsga2 and opposition based nsga2):
```
	make
```

##### 4. cleaning up:
```
	make clean
```

##### 5. building the wfg Hypervolume computation code:
```
	make wfg
``` 


#### How to run the experiments and to statistical analysis:

##### 1. Run a single experiment:
```
	./sh/run onsga2r input_data/zdt1.in experiments/ 1 0.12345
	./sh/run nsga2re input_data/zdt1.in experiments/ 1 0.12345
```

##### 2. Run multiple experiments at once:
```
	./sh/maprun -si -n 31 -c "./sh/run onsga2r input_data/zdt1.in experiments/"	
	./sh/maprun -si -n 31 -c "./sh/run nsga2re input_data/zdt1.in experiments/"
```

##### 3. Burst snapshots from a single file:
```
	./sh/burstgen.py experiments/ zdt1 1
```
	
##### 4. Burst all 31 runs at once:
```
	./sh/maprun -i -n 31 -c "./sh/burstgen.py experiments/ zdt1"
```

##### 4. Clean up all generated results for one particular problem (e.g. zdt1):
```
	./sh/flush zdt1
```

##### 5. Generate one snapshot report:
Assuming bursting has already been done from the previous step 4 --
```
	./sh/reportsnap experiments/ 1 100 1 8 0.4 zdt1 1
```
can also be done for multiple runs with `maprun`.

##### 6. Generate hypervolume comparison stat for one problem:
Assuming `wfg` has already been compiled --
```
	./sh/plothv.py experiments/ zdt1
```

##### 7. Generate stats for the survival of opposite points:
Assuming bursting has already been done from the previous step 4 --
```
	./sh/survivalstat.py experiments/ zdt1
```
