% script to test the sosolverf() function.
global popsize ;
global nreal ;
global nobj ;

filepath = '../../input_data/antenna.in' ;
load_input_data(filepath);
[pathstr, pname, ext] = fileparts(filepath);
matfile = strcat('pivots_', pname, '.mat');
pivots = zeros(nobj, nreal + nobj);
for i = 1:nobj
    idx = i ;
    result = sosolver(filepath, idx, 12345);
    % disp(result);
    xval = result(1:nreal);
    fval = result(nreal+1:nreal+nobj);
    feval = result(nreal+nobj+1);
    max_gen = result(end);
    % fprintf('x: '); printmatrix(xval);
    fprintf('f: \n'); disp(fval); % printmatrix(fval);
    fprintf('%d = %d x %d\n', feval, popsize, max_gen);
    pivots(i,:) = [xval', fval'];
end
% disp(pivots);
save(matfile, 'pivots');