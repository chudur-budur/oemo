% Run matlabbed GA for a single objective problems

global min_realvar ;
global max_realvar ;
global nreal ;

% the problem parameters file
file_path = '../../input_data/antenna.in' ;
load_input_data(file_path);

LB = min_realvar' ;
UB = max_realvar' ;
options = gaoptimset('Display', 'iter', 'Generations', 200, ...
    'PopulationSize', 200, 'PopulationType', 'doubleVector');
% ga(fitnessfcn,nvars,A,b,[],[],LB,UB,nonlcon,IntCon,options)
x = ga(@antenna, nreal, [], [], [], [], LB, UB, [], [], options);

disp(x);