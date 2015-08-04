% script to test the sosolverf() function.
global popsize ;
global nreal ;
global nobj ;

path = '../../input_data/zdt1.in' ;
idx = 1 ;
result = sosolver(path, idx);
disp(result);
xval = result(1:nreal);
fval = result(nreal+1:nreal+nobj);
feval = result(nreal+nobj+1);
max_gen = result(end);
fprintf('x: '); printmatrix(xval);
fprintf('f: '); printmatrix(fval);
fprintf('%d = %d x %d\n', feval, popsize, max_gen);
