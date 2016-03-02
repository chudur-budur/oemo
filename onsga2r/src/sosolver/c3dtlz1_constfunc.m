function [c, ceq] = c3dtlz1_constfunc(x)
%C3DTLZ1_CONSTFUNC Summary of this function goes here
%   The constraint definition for the C3-DTLZ1 problem.
    global nobj ;
    f = c3dtlz1(x) ;
    c = zeros(nobj) ;
    for i = 1:nobj
        j = 1:nobj ;
        c(i) = sum(f(i ~= j)) + f(i)/0.5 - 1.0 ;
    end
    ceq = [];
end