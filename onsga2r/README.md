oemo-mirroring
==============

Experiments with opposition based emo with mirroring.

#### How to compile:

##### 1. First you need to build the matlab's single obj. optimization solver
```
	make sosolv
```

##### 2. cleaning up the so-solver
```
	make clean-sosolv
```

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


#### How to run the experiments:

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

##### 5. Generate one snapshot report:
Assuming bursting has already been done from the previous step 4 --
```
	./sh/reportsnap experiments/ 1 100 1 8 0.4 zdt1 1
```
can also be done for multiple runs with `mapl`.

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
