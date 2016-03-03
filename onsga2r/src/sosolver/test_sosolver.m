% script to test the sosolverf() function.
global popsize ;
global nreal ;
global nobj ;

path = '../../input_data/antenna.in' ;
idx = 3 ;
result = sosolver(path, idx, 12345);
% disp(result);
xval = result(1:nreal);
fval = result(nreal+1:nreal+nobj);
feval = result(nreal+nobj+1);
max_gen = result(end);
% fprintf('x: '); printmatrix(xval);
fprintf('f: \n'); disp(fval); % printmatrix(fval);
fprintf('%d = %d x %d\n', feval, popsize, max_gen);