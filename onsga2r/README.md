oemo-mirroring
==============

Experiments with opposition based emo with mirroring.

#### How to compile the classical search component:
This part is written in MATLAB (`R2014a`), extensively using `fmincon()` and `patternsearch()`. All the related matlab scripts could be found in `src/sosolver` and the wrapper function is in `src/sosolver.c` and `src/sosolver.h`. To compile and run this part, you need to add `$matlabroot/runtime/glnxa64` and `$matlabroot/bin/glnxa64` to `$LD_LIBRARY_PATH`. So there it goes -- 

##### 1. To build the whole application, first you need to build the matlab's single obj. optimization solver
```shell
	make sosolv
```

##### 2. cleaning up the so-solver
```shell
	make clean-sosolv
```

Now you can build the main code --


##### 3. building the main code (nsga2 and opposition based nsga2):
```shell
	make
```

##### 4. cleaning up:
```shell
	make clean
```

##### 5. building the wfg Hypervolume computation code:
```shell
	make wfg
``` 


#### How to run the experiments and to statistical analysis:

##### 1. Run a single experiment:
```shell
	./sh/run onsga2r input_data/zdt1.in experiments/ 1 0.12345
	./sh/run nsga2re input_data/zdt1.in experiments/ 1 0.12345
```

##### 2. Run multiple experiments at once:
```shell
	./sh/maprun -si -n 11 -c "./sh/run onsga2r input_data/zdt1.in experiments/"
	./sh/maprun -si -n 11 -c "./sh/run nsga2re input_data/zdt1.in experiments/"
```

##### 3. Burst snapshots from a single file:
```shell
	./sh/burstgen.py experiments/ zdt1 1
```
	
##### 4. Burst all 11 runs at once:
```shell
	./sh/maprun -i -n 11 -c "./sh/burstgen.py experiments/ zdt1"
```

##### 5. Clean up all generated results for one particular problem (e.g. zdt1):
```shell
	./sh/flush zdt1
```

##### 6. Generate one snapshot report:

Assuming bursting has already been done from the previous step 5 --
```shell
	./sh/reportsnap experiments/ 1 100 1 8 0.4 zdt1 1
```
can also be done for multiple runs with `maprun`.

##### 7. Generate hypervolume comparison stat for one problem:

Assuming `wfg` has already been compiled --
```shell
	./sh/plothv.py experiments/ zdt1
```

##### 8. Generate stats for the survival of opposite points:

Assuming bursting has already been done from the previous step 5 --
```shell
	./sh/survivalstat.py experiments/ zdt1
```
