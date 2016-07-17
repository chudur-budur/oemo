function [c, ceq] = c1dtlz3_constfunc(x)
%%   The constraint definition for the C1-DTLZ3 problem
    global nobj ;
    f = c1dtlz3(x) ;    
    Ms = {3, 5, 8, 10, 15};
    rs = {9, 12.5, 12.5, 15, 15};
    rmap = containers.Map(Ms, rs);
    r = rmap(nobj) ;
    c(1) = sum((f(1:nobj) .* f(1:nobj)) - 16) * ...
                sum((f(1:nobj) .* f(1:nobj)) - (r .^ 2));
    ceq = [];
end