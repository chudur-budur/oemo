howto
======

This folder contains the MATLAB (`R2014a`) codes to find the approximated *CHIM<sub>+<sub>* bounds.
All the *CHIM<sub>+<sub>* bounding solutions are saved in the `../chimps` folder.

1. `gen_chimps.m`: The main executable script, read this file to understand how this works. For example if you want to find the extreme solution for `zdt1` problem, go to line 50 and change the problem parameter file-path to an appropriate name --

	```matalb
	file_path = '../input_data/zdt6.in' ;
	```
and then run the script.

2. `test_antenna.m`: The script to run and test the multi-objective circular antenna array problem solver.
