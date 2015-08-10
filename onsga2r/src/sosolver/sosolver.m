function result = sosolver(file_path, findex, seed)
%SOSOLVERF Solve a single objective function of a multi-objective problem using aasf
%   x:      solution to be found
%   f_star: best function value found so far
%   func:   the MOP function to be optimized
%   index:  index of the single objective function value

% these are from the load_input_data() function
global min_realvar ;
global max_realvar ;
global nreal ;
global nobj ;
global popsize ;
global ngen ;

% these are from the aasf()
global func ;
global index ;
global f_star ;

result = zeros(1, nreal + nobj + 2) ;

% if nreal > 10   then fmincon
% if nreal <= 10, then patternsearch
maxvarlm = 11 ;

% file_path = '../../input_data/zdt1.in' ;
[path, prob_name, ext] = fileparts(file_path);

% load the problem parameters
load_input_data(file_path);
% function to optimize
func = str2func(prob_name) ;
fprintf(1, 'sosolver: solving "%s" problem from file "%s"\n', ...
            prob_name, file_path);

% obj index to optimize
index = findex ;

% variable bounds
lb = min_realvar' ;
ub = max_realvar' ;

rng(seed, 'twister');
% random initial point
x0 = min_realvar' + (rand(1,nreal) .* (max_realvar - min_realvar)');

% fixed budget
if (nobj > 2)
    febound = round((((ngen * 0.25) * popsize) / nobj) / 2.0);
else
    febound = round((((ngen * 0.25) * popsize) / nobj) / 2.0);
end

% set options for fmincon
fmcopt = optimoptions('fmincon');
fmcopt.MaxFunEvals = febound;
% fmcopt.TolX = 1.0e-14 ;
% fmcopt.TolFun = 1.0e-14 ;
fmcopt.Display = 'off' ;
% options.Algorithm = 'trust-region-reflective' ;

% set options for patternsearch
psopt = psoptimset(@patternsearch);
psopt = psoptimset(psopt, 'MaxFunEvals', febound);
if (nobj > 2)
    psopt = psoptimset(psopt, 'InitialMeshSize', popsize);
    % psopt = psoptimset(psopt, 'MeshAccelerator', 'off', 'ScaleMesh', 'on');
    psopt = psoptimset(psopt, 'TolX', 1e-7, 'TolBind', 1e-6);
    % psopt = psoptimset(psopt, 'SearchMethod', @GPSPositiveBasis2N);
    % psopt = psoptimset(psopt, 'SearchMethod', @GSSPositiveBasis2N);
    psopt = psoptimset(psopt, 'SearchMethod', @MADSPositiveBasis2N);
    % psopt = psoptimset(psopt, 'SearchMethod', {@searchneldermead,10});
    % psopt = psoptimset(psopt, 'SearchMethod', {@searchga,10});
    psopt = psoptimset(psopt, 'CompletePoll', 'on');
    psopt = psoptimset(psopt, 'CompleteSearch', 'on');
    % psopt = psoptimset(psopt,'Cache','on','CacheTol',1e-10);
end
% psopt = psoptimset(psopt, 'Display','off');

feval = 0 ;
% start the initial optimization
if (nreal > maxvarlm)
    fprintf(1, 'sosolver: Initial optimization, applying fmincon(), with FE bound %d\n', febound);
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@sopt,x0,[],[],[],[],lb,ub,[],fmcopt) ;
    feval = feval + output.funcCount ;
    fprintf(1, 'sosolver: Initial optimization done (fmincon()).\n');
else
    fprintf(1, 'sosolver: Initial optimization, applying patternsearch(), with FE bound %d\n', febound);
    [x,fval,exitflag,output] ...
                = patternsearch(@sopt,x0,[],[],[],[],lb,ub,[],psopt) ;
    feval = feval + output.funccount ;
    fprintf(1, 'sosolver: Initial optimization done (patternsearch()).\n');
end
% Initial level result 
format compact ;
fprintf(1, 'x: '); printmatrix(x);
fprintf(1, 'f: '); printmatrix(func(x));
disp(output);

% initial result found, now use it as a starting point
x0 = x ;
f_star = func(x0) ;

% next level optimization with aasf
if (nreal > maxvarlm)
    fprintf(1, 'sosolver: Next level AASF, applying fmincon() with FE bound %d\n', febound);
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@aasf,x0,[],[],[],[],lb,ub,[],fmcopt) ;
    feval = feval + output.funcCount ;
    fprintf(1, 'sosolver: Next level AASF done (fmincon()).');
else
    fprintf(1, 'sosolver: Next level AASF, applying patternsearch() with FE bound %d\n', febound);
    [x,fval,exitflag,output] ...
                = patternsearch(@aasf,x0,[],[],[],[],lb,ub,[],psopt) ;
    feval = feval + output.funccount ;
    fprintf(1, 'sosolver: Next level AASF done (patternsearch()).');
end                
% next level aasf results
format compact ;
fprintf(1, '\nx: '); printmatrix(x);
fprintf(1, 'f: '); printmatrix(func(x));
disp(output)

% get stats
max_gen = round(feval / popsize);
xval = x ;
fval = func(x) ;

% x x x f f e g
% 1 2 3 4 5 6 7
result(1:nreal) = xval ;
result(nreal+1:nreal+nobj) = fval ;
result(nreal+nobj+1) = feval ;
result(end) = max_gen ;
result = result' ;
end