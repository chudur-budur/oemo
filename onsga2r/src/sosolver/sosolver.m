function [xval, fval, feval, max_gen] = sosolver(file_path, findex)
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

% these are from the aasf()
global func ;
global index ;
global f_star ;

% if nreal > 10   then fmincon
% if nreal <= 10, then patternsearch
maxvarlm = 11 ;

% file_path = '../../input_data/zdt1.in' ;
[path, prob_name, ext] = fileparts(file_path);

% load the problem parameters
load_input_data(file_path);
% function to optimize
func = str2func(prob_name) ;
fprintf('sosolver: solving "%s" problem from file "%s"\n', ...
            prob_name, file_path);

% obj index to optimize
index = findex ;

% variable bounds
lb = min_realvar' ;
ub = max_realvar' ;
% rng(12345, 'twister');
% random initial point
x0 = min_realvar' + (rand(1,nreal) .* (max_realvar - min_realvar)');

% set options for fmincon
fmcopt = optimoptions('fmincon');
% fmcopt.TolX = 1.0e-14 ;
% fmcopt.TolFun = 1.0e-14 ;
fmcopt.Display = 'off' ;
% options.Algorithm = 'trust-region-reflective' ;

% set options for patternsearch
psopt = psoptimset(@patternsearch);
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
    fprintf('sosolver: Initial optimization, applying fmincon()\n');   
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@sopt,x0,[],[],[],[],lb,ub,[],fmcopt) ;
    feval = feval + output.funcCount ;
    disp('sosolver: Initial optimization done (fmincon()).');
else
    fprintf('sosolver: Initial optimization, applying patternsearch()\n');
    [x,fval,exitflag,output] ...
                = patternsearch(@sopt,x0,[],[],[],[],lb,ub,[],psopt) ;
    feval = feval + output.funccount ;
    disp('sosolver: Initial optimization done (patternsearch()).');
end
% Initial level result       
disp(x);
disp(func(x));
disp(output);

% initial result found, now use it as a starting point
x0 = x ;
f_star = func(x0) ;

% next level optimization with aasf
if (nreal > maxvarlm)
    fprintf('sosolver: Next level AASF, applying fmincon()\n');
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@aasf,x0,[],[],[],[],lb,ub,[],fmcopt) ;
    feval = feval + output.funcCount ;
    disp('sosolver: Next level AASF done (fmincon()).');
else
    fprintf('sosolver: Next level AASF, applying patternsearch()\n');
    [x,fval,exitflag,output] ...
                = patternsearch(@aasf,x0,[],[],[],[],lb,ub,[],psopt) ;
    feval = feval + output.funccount ;
    disp('sosolver: Next level AASF done (patternsearch()).');
end                
% next level aasf results
disp(x);
disp(func(x));
disp(output)

% get stats
max_gen = round(feval / popsize);
xval = x ;
fval = func(x) ;

end