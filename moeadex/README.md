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
Once you have built the source, you will find the following executables --

