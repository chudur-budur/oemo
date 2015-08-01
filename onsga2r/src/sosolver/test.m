% script to test the sosolverf() function.
global popsize ;

path = '../../input_data/dtlz7.in' ;
idx = 1 ;
[xval, fval, feval, max_gen] = sosolver(path, idx);
fprintf('x: '); disp(xval);
fprintf('f: '); disp(fval);
fprintf('%d = %d x %d\n', feval, popsize, max_gen);
