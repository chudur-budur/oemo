EMO with *CHIM<sub>+<sub>* outer-bounds (a.k.a oemo)
=====================================================

### Experiments with *CHIM<sub>+<sub>* bound injection in EMO.

#### How to find the *CHIM<sub>+<sub>* bounds:
This part is implemented in some stand-alone MATLAB (`R2014a`) codes, more details can be found [here](https://github.com/chudur-budur/oemo/tree/master/onsga2r/chimp-solver). 



This module assumes that you have [jMetal](https://github.com/jMetal/jMetal) library in your stash. Once you have found all the bounding solutions (using the MATLAB scritps in the `chimp-solver` folder), now you can build the main code --

##### 1. building the main executables:
```shell
	ant make
```
Once you have built the source, you will find the following executables in the `bin/` folder --

  * `MoeadExr.class`: the MOEA/D with extreme point injection
  * `Moeadr.class`: the actual MOEA/D code implemented in the [jMetal](https://github.com/jMetal/jMetal) framework.

Also before building the above code, you need to build the `onsga2r` module to get the `wfg` executable. Details on how to build the `onsga2r` module is described [here](https://github.com/chudur-budur/oemo/blob/master/onsga2r/README.md).

##### 2. cleaning up:
```shell
	make clean
```
