EMO with *CHIM<sub>+<sub>* outer-bounds (a.k.a oemo)
=====================================================

### Experiments with *CHIM<sub>+<sub>* bound injection in EMO.

#### How to find the *CHIM<sub>+<sub>* bounds:
This part is implemented in some stand-alone MATLAB (`R2014a`) codes, more details can be found [here](https://github.com/chudur-budur/oemo/tree/master/onsga2r/nadir-solver). 



Once you have found all the bounding solutions (using the MATLAB scritps in the `nadir-solver` folder), now you can build the main code --

##### 1. building the main executables:
```shell
	make
```
Once you build, you will find the following executables --

  * `nsga2r`: blah blah
  * `onsga2r`: blah blah

##### 2. cleaning up:
```shell
	make clean
```

##### 3. building the wfg Hypervolume computation code:
```shell
	make wfg
``` 



#### How to run the experiments and to do the statistical analysis:

##### 1. Run a single experiment:
```shell
	./sh/run onsga2r input_data/zdt1.in experiments/ 1 0.12345
	./sh/run nsga2r input_data/zdt1.in experiments/ 1 0.12345
```

##### 2. Run multiple experiments at once:
```shell
	./sh/maprun -si -n 11 -c "./sh/run onsga2r input_data/zdt1.in experiments/"
	./sh/maprun -si -n 11 -c "./sh/run nsga2r input_data/zdt1.in experiments/"
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
