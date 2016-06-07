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

% file_path = '../../input_data/zdt1.in' ;
[path, prob_name, ext] = fileparts(file_path);

% load the problem parameters
load_input_data(file_path);
% function to optimize
func = str2func(prob_name) ;
constfunc = str2func(strcat(prob_name, '_constfunc'));
fprintf(1, 'sosolver.m -- solving "%s" problem from file "%s"\n', ...
            prob_name, file_path);
fprintf(1, 'sosolver.m -- using func: "%s" and constfun: "%s"\n', ...
            strcat(prob_name, '()'), strcat(prob_name, '_constfunc()'));

% obj index to optimize
index = findex ;

% variable bounds
lb = min_realvar' ;
ub = max_realvar' ;

rng(seed, 'twister');
% random initial point
x0 = min_realvar' + (rand(1,nreal) .* (max_realvar - min_realvar)');

% fixed budget
% febound = 1667 ; % for zdt6 to get a better view
febound = round((((ngen * 0.25) * popsize) / nobj) / 2.0);
% febound = round((((200 * 0.25) * popsize) / nobj) / 2.0);
% this works for osy, ctp4
% febound = round((((30 * 0.25) * popsize) / nobj) / 2.0);
fprintf('********** solsolver.m -- FE bound fixed to: %d\n', febound);

% if the problem does not have local optima then use fmincon()
easy_problems = {'zdt1'; 'zdt2'; 'zdt3'; 'zdt6'; ...
                    'dtlz4'; 'dtlz5'; 'dtlz7'; ...
                    'c3dtlz1'; ...
                    'osy'; ...
                    'crash'; 'antenna'};
% if the problem has local optima, then use patternsearch()
hard_problems = {'zdt4'; 'dtlz1'; 'dtlz2'; 'dtlz3'; 'dtlz6'; ...
                    'ctp4'; 'ctp8'; ...
                    'c1dtlz1'; 'c1dtlz3'; 'c2dtlz2'; ...
                    'beam'; 'gear'};

% set options for fmincon
fmcopt = optimoptions('fmincon');
fmcopt.MaxFunEvals = febound;
fmcopt.Display = 'off' ;

% set options for patternsearch
psopt = psoptimset(@patternsearch);
psopt = psoptimset(psopt, 'MaxFunEvals', febound);
if (nobj > 2)
    psopt = psoptimset(psopt, 'InitialMeshSize', (1.0 / popsize));
    % psopt = psoptimset(psopt, 'InitialMeshSize', 1.0);
    psopt = psoptimset(psopt, 'TolX', 1e-7, 'TolBind', 1e-6);
    psopt = psoptimset(psopt, 'SearchMethod', @MADSPositiveBasis2N);
    % psopt = psoptimset(psopt, 'SearchMethod', @GPSPositiveBasis2N);
    % psopt = psoptimset(psopt, 'SearchMethod', @GSSPositiveBasis2N);
    % psopt = psoptimset(psopt, 'SearchMethod', {@searchneldermead,10});
    % psopt = psoptimset(psopt, 'SearchMethod', {@searchga,100});
    psopt = psoptimset(psopt, 'CompletePoll', 'on');
    psopt = psoptimset(psopt, 'CompleteSearch', 'on');   
end

feval = 0 ;
% start the initial optimization
if (ismember(prob_name, easy_problems))
    fprintf(1, 'sosolver.m -- Initial optimization, applying fmincon(), with FE bound %d\n', febound);
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@sopt,x0,[],[],[],[],lb,ub,constfunc,fmcopt) ;
    feval = feval + output.funcCount ;
    fprintf(1, 'sosolver.m -- Initial optimization done (fmincon()).\n');
elseif (ismember(prob_name, hard_problems))
    fprintf(1, 'sosolver.m -- Initial optimization, applying patternsearch(), with FE bound %d\n', febound);
    [x,fval,exitflag,output] ...
                = patternsearch(@sopt,x0,[],[],[],[],lb,ub,constfunc,psopt) ;
    feval = feval + output.funccount ;
    fprintf(1, 'sosolver.m -- Initial optimization done (patternsearch()).\n');
end
% Initial level result 
format compact ;
fprintf(1, 'sosolver.m -- x: '); printmatrix(x);
fprintf(1, 'sosolver.m -- f: '); printmatrix(func(x));
disp(output);

% initial result found, now use it as a starting point
x0 = x ;
f_star = func(x0) ;

% next level optimization with aasf
if (ismember(prob_name, easy_problems))
    fprintf(1, 'sosolver.m -- Next level AASF, applying fmincon() with FE bound %d\n', febound);
    [x,fval,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@aasf,x0,[],[],[],[],lb,ub,constfunc,fmcopt) ;
    feval = feval + output.funcCount ;
    fprintf(1, 'sosolver.m -- Next level AASF done (fmincon()).');
elseif (ismember(prob_name, hard_problems))
    fprintf(1, 'sosolver.m -- Next level AASF, applying patternsearch() with FE bound %d\n', febound);
    [x,fval,exitflag,output] ...
                = patternsearch(@aasf,x0,[],[],[],[],lb,ub,constfunc,psopt) ;
    feval = feval + output.funccount ;
    fprintf(1, 'sosolver.m -- Next level AASF done (patternsearch()).');
end                
% next level aasf results
format compact ;
fprintf(1, '\nsosolver.m -- x: '); printmatrix(x);
fprintf(1, 'sosolver.m -- f: '); printmatrix(func(x));
fprintf(1, 'sosolver.m -- feval: %d\n', feval); 
disp(output)

% get stats
max_gen = round(feval / popsize);
xval = x ;
fval = func(x) ;

% x x x f f e g
% 1 2 3 4 5 6 7
result = zeros(1, nreal + nobj + 2) ;
result(1,1:nreal) = xval ;
result(1,nreal+1:nreal+nobj) = fval ;
result(1,nreal+nobj+1) = feval ;
result(1,end) = max_gen ;
fprintf('sosolver.m -- result: \n');
disp(result');
result = result' ;
end

