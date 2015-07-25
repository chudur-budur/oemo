oemo-mirroring
==============

Experiments with opposition based emo with mirroring.

#### How to compile:

##### 1. building the main code (nsga2 and opposition based nsga2):
```
	make
```

##### 2. building the wfg Hypervolume computation code:
```
	make wfg
``` 

##### 3. cleaning up:
```
	make clean
```


#### How to run the experiments:

##### 1. Run a single experiment:
```
	./sh/run nsga2r input_data/zdt1.in experiments/ 1 0.12345
	./sh/run onsga2r input_data/zdt1.in experiments/ 1 0.12345
```

##### 2. Run multiple experiments at once:
```
	./sh/mapl -si -n 31 -c "./sh/run onsga2r input_data/zdt1.in experiments/"	
	./sh/mapl -si -n 31 -c "./sh/run nsga2r input_data/zdt1.in experiments/"
```

##### 3. Burst snapshots from a single file:
```
	./sh/burstgen.py experiments/ zdt1 1
```
	
##### 4. Burst all 31 runs at once:
```
	./sh/mapl -is -n 31 -c "./sh/burstgen.py experiments/ zdt1"
```

##### 5. Generate one snapshot report:
```
	./sh/reportsnap experiments/ 1 100 1 8 0.4 zdt1 1
```

##### 6. Generate hypervolume comparison stat for one problem:
Assuming wfg has been already compiled --
```
	./sh/plothv.py experiments/ zdt1
```
