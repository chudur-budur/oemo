function [c, ceq] = c3dtlz1_constfunc(x)
%%   The constraint definition for the C3-DTLZ1 problem.
    global nobj ;
    f = c3dtlz1(x) ;
    c = zeros(nobj) ;
    for i = 1:nobj
        fsum = 0.0 ;
        for j = 1:nobj
            if (i ~= j), fsum = fsum + f(j); end
        end
        c(i) = fsum + (f(i)/0.5) - 1.0 ;
    end
    ceq = [];
end