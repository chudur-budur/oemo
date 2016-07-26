%% GEN_CHIMPS Generate all CHIM bounding points and save them in a file

clear ; % clear craps
addpath('problemdef') ;
% rng(123456, 'twister');

%% these are from the load_input_data() function
global min_realvar ;
global max_realvar ;
global nreal ;
global nobj ;
global popsize ;
global ngen ;

%% these are from the aasf()
global func ;
global index ;
global f_star ;

%% total number of runs, setting it 20
nruns = 20 ;

%% problem names for the hashmap
probs = {...
    'zdt1', 'zdt2', 'zdt3', 'zdt4', 'zdt6', ...
    'dtlz1', 'dtlz2', 'dtlz3', 'dtlz4', 'dtlz5', 'dtlz6', 'dtlz7', ...
    'osy', 'ctp8', 'ctp4', ...
    'c1dtlz1', 'c1dtlz3', 'c2dtlz2', 'c3dtlz1', ...
    'crash', 'antenna', 'beam', 'gear'};
% ratios to fix FE bounds
ratios = {...
    30.0, 30.0, 25.0, 8.0, 8.0, ...
    8.0, 40.0, 6.0, 30.0, 30.0, 10.0, 30.0, ...
    6.0, 8.0, 8.0, ...
    15.0, 6.0, 6.0, 15.0, ...
    15.0, 6.0, 500, 500};
% hashmap: problem name -> (FE bound, problem type)
ratio_map = containers.Map(probs, ratios);

%% problem classes for the choice of search algorithms
% if the problem does not have local optima then use fmincon()
set_one = {'zdt1'; 'zdt2'; 'zdt3'; 'zdt6'; 'dtlz4'; 'dtlz5'; ...
    'dtlz7'; 'c3dtlz1'; 'osy'; 'crash'; 'antenna'};
% if the problem has local optima, then use patternsearch()
% move the problem to set_two if the number of variable is many
set_two = {'zdt4'; 'dtlz1'; 'dtlz2'; 'dtlz3'; 'dtlz6'; 'ctp4'; ...
    'ctp8'; 'c1dtlz1'; 'c1dtlz3'; 'c2dtlz2'; 'c3dtlz1'; 'beam'; 'gear'};

%% file paths
% file_path is the problem parameters from input_data folder
file_path = '../input_data/dtlz4.in' ;
[path, prob_name, ext] = fileparts(file_path);
% make file path to save all the nadir solutions
out_dir = '../chimps' ;
if(~exist(out_dir, 'dir')), mkdir(out_dir); end
out_file = strcat(out_dir, '/', prob_name, '-chimps.out');
fprintf('** Saving CHIM bounds to: %s\n', out_file);
    
%% load the problem parameters
load_input_data(file_path);

%5 copy the variable bounds
lb = min_realvar' ;
ub = max_realvar' ;

%% function to optimize
func = str2func(prob_name) ;
% the constraint related to the func
constfunc = str2func(strcat(prob_name, '_constfunc'));
fprintf(1, '*** Solving "%s" problem from file "%s"\n', ...
            prob_name, file_path);
fprintf(1, '*** Using func: "%s" and constfun: "%s"\n', ...
            strcat(prob_name, '()'), strcat(prob_name, '_constfunc()'));
        
%% fixed budget
% febound = 1667 ; % for zdt6 to get a better view
fetotal = ngen * popsize ;
febound = round((fetotal / ratio_map(prob_name)) / nobj) ;
fprintf('*** FE bound fixed to: %d\n', febound);
  
%% algorithm options
% set options for fmincon
fmcopt = optimoptions('fmincon');
fmcopt.MaxFunEvals = febound;
fmcopt.Display = 'off' ;
% set options for patternsearch
psopt = psoptimset(@patternsearch);
psopt = psoptimset(psopt, 'MaxFunEvals', febound);
% this can be removed, may be ?
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
        
%% open the nadir file and solve the problem for nruns times
fid = fopen(out_file, 'w');
for runs = 1:nruns
    for i = 1:nobj
        % obj index to optimize
        index = i ;

        % random initial point
        x0 = min_realvar' + (rand(1,nreal) .* ...
            (max_realvar - min_realvar)');

        feval = 0 ;
        % start the initial optimization
        if (ismember(prob_name, set_one))
            fprintf(1, '* Initial run: fmincon(), FE bound %d\n', febound);
            [x,~,exitflag,output,lambda,grad,hessian] = ...
                fmincon(@sopt,x0,[],[],[],[],lb,ub,constfunc,fmcopt) ;
            feval = feval + output.funcCount ;
            fprintf(1, '* Initial run: done (fmincon()).\n');
        elseif (ismember(prob_name, set_two))
            fprintf(1, '* Initial run: patternsearch(), FE bound %d\n', febound);
            [x,~,exitflag,output] = ...
                patternsearch(@sopt,x0,[],[],[],[],lb,ub,constfunc,psopt) ;
            feval = feval + output.funccount ;
            fprintf(1, '* Initial run: done (patternsearch()).\n');
        end
        % Initial level result 
        format compact ;
        fprintf(1, '* Initial x: '); printmatrix(x);
        fprintf(1, '* Initial f: '); printmatrix(func(x));
        % disp(output);

        % initial result found, now use it as a starting point
        x0 = x ;
        f_star = func(x0) ;

        % next level optimization with aasf
        if (ismember(prob_name, set_one))
            fprintf(1, '** AASF run: fmincon(), FE bound %d\n', febound);
            [x,~,exitflag,output,lambda,grad,hessian] ...
                = fmincon(@aasf,x0,[],[],[],[],lb,ub,constfunc,fmcopt) ;
            feval = feval + output.funcCount ;
            fprintf(1, '** AASF run: done (fmincon()).');
        elseif (ismember(prob_name, set_two))
            fprintf(1, '** AASF run: patternsearch(), FE bound %d\n', febound);
            [x,~,exitflag,output] ...
                = patternsearch(@aasf,x0,[],[],[],[],lb,ub,constfunc,psopt) ;
            feval = feval + output.funccount ;
            fprintf(1, '** AASF run: done (patternsearch()).');
        end                
        % next level aasf results
        format compact ;
        fprintf(1, '\n*** Final x*: '); printmatrix(x);
        fprintf(1, '*** Final f*: '); printmatrix(func(x));
        fprintf(1, '*** Final feval: %d\n', feval); 
        % disp(output)

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
        fprintf('*** Final result:'); printmatrix(result');
        result = result' ;
        fprintf(fid, '%.3f ', result);
        fprintf(fid, '\n');
    end
end
fclose(fid);
