function f = sopt(x)
%SO Make a multi-objective function to single-objective function
%   x:      solution to be found
%   func:   the MOP function to be optimized
%   index:  index of the single objective function value
%   wt:     weighted solver, if index is not being used.

global func ;
global index ;

fval = func(x);
f = fval(index) ;

end