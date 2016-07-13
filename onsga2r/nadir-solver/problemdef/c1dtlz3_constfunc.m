function [c, ceq] = c1dtlz3_constfunc(x)
%C1DTLZ3_CONSTFUNC Summary of this function goes here
%   The constraint definition for the C1-DTLZ3 problem
    global nobj ;
    f = c1dtlz3(x) ;    
    c(1) = sum((f(1:nobj) .* f(1:nobj)) - 16) * ...
                sum((f(1:nobj) .* f(1:nobj)) - 9);
    ceq = [];
end