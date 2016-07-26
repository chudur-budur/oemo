function f = aasf(x)
%AASF Solve a single objective function of a multi-objective problem using aasf
%   x:      solution to be found
%   f_star: best function value found so far
%   func:   the MOP function to be optimized
%   index:  index of the single objective function value

global func ;
global f_star ;
global nobj ;
global index ;


if index > 0
    w = ones(1,nobj) * (0.1 / (nobj - 1.0));
    w(index) = 0.9 ;
    fval = (func(x) - f_star) ./ w ;
    f = max(fval) + (0.0001 * sum(fval)) ;
else
    w = ones(1, nobj) * 0.5 ;
    fval = (func(x) - f_star) ./ w ;
    f = max(fval) + (0.0001 * sum(fval)) ;    
end

end