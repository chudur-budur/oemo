EMO with *CHIM<sub>+<sub>* outer-bounds (a.k.a oemo)
=====================================================

### Experiments with *CHIM<sub>+<sub>* bound injection in EMO.

#### How to find the *CHIM<sub>+<sub>* bounds:
This part is implemented in some stand-alone MATLAB (`R2014a`) codes, more details can be found [here](https://github.com/chudur-budur/oemo/tree/master/onsga2r/chimp-solver). 

Once you have found all the bounding solutions (using the MATLAB scritps in the `chimp-solver` folder), now you can build the main code --

##### 1. building the main executables:
```shell
	make
```
Once you have built the source, you will find the following executables --

  * `nsga2r`: the original NSGA-II from [here](http://www.coin-laboratory.com/#!codes/rr8aj). 
  * `onsga2r`: the experimental NSGA-II code that utilizes the *CHIM<sub>+<sub>* bounds.
  * `nsga2re`: NSGA-II, where *CHIM<sub>+<sub>* bounds are injected into the initial population, and that's all.
  * `onsga2rw`: the `onsga2r` code where the algorithm utilizes only *one* approximated solution on the PF which was found using objective function scalarization.
  * `onsga2rwdom`: the `onsga2r` code where it starts with a set of *weakly-dominated* bounds. 

##### 2. cleaning up:
```shell
	make clean
```

##### 3. building the wfg Hypervolume computation code:
```shell
	make computehv
``` 



#### How to run the experiments and to do the statistical analysis:

##### 1. Run a single experiment:
```shell
	./sh/run.sh onsga2r input_data/zdt1.in experiments/ 1 0.12345
	./sh/run.sh nsga2r input_data/zdt1.in experiments/ 1 0.12345
```

##### 2. Run multiple experiments at once:
```shell
	./sh/maprun.sh -si -n 11 -c "./sh/run.sh onsga2r input_data/zdt1.in experiments/"
	./sh/maprun.sh -si -n 11 -c "./sh/run.sh nsga2r input_data/zdt1.in experiments/"
```

##### 3. Burst snapshots from a single file:
```shell
	./sh/burstgen.py experiments/ zdt1 1
```
	
##### 4. Burst all 11 runs at once:
```shell
	./sh/maprun.sh -i -n 11 -c "./sh/burstgen.py experiments/ zdt1"
```

##### 5. Clean up all generated results for one particular problem and algorithm (e.g. zdt1 solved with nsga2r):
```shell
	./sh/flush.sh nsga2r zdt1
```

##### 6. Generate one snapshot report:

Assuming bursting has already been done from the previous step 3 (or 4) --
```shell
	./sh/reportsnap.sh experiments/ 1 100 1 8 0.4 zdt1 1
```
can also be done for multiple runs with `maprun.sh`. This code also assumes the [gnuplot](http://www.gnuplot.info/) is installed in the system, along with [gnuplot-palette](https://github.com/Gnuplotting/gnuplot-palettes) and [gnuplot-colorbrewer](https://github.com/aschn/gnuplot-colorbrewer) are installed in `~/gnuplot-utils/`.

##### 7. Generate hypervolume comparison stat for one problem:

Assuming `computehv` has already been compiled --
```shell
	./sh/plothv.py experiments/ zdt1
```

##### 8. Generate stats for the survival of opposite points:

Assuming bursting has already been done from the previous step 4 --
```shell
	./sh/survivalstat.py experiments/ zdt1
```
