function [c, ceq] = c1dtlz3_constfunc(x)
%ZDT1_CONSTFUNC Summary of this function goes here
%   Detailed explanation goes here
    global nobj ;
    f = c1dtlz3(x) ;    
    c(1) = sum((f(1:nobj) .* f(1:nobj)) - 16) * ...
                sum((f(1:nobj) .* f(1:nobj)) - 9);
    ceq = [];
end