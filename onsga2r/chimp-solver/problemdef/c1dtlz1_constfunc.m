function [c, ceq] = c1dtlz1_constfunc(x)
%%   The constraints for C1-DTLZ1 problem
    global nobj ;
    f = c1dtlz1(x) ;    
    c(1) = 1.0 - (f(nobj)/0.6) - sum(f(2:nobj) ./ 0.5) ;
    ceq = [];
end