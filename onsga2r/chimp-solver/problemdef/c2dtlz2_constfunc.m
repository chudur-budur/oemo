function [c, ceq] = c2dtlz2_constfunc(x)
%%   The constraints definition for c2dtlz2 problem.
    global nobj ;
    f = c2dtlz2(x);
    fmax1 = 0.0 ;
    for i = 1:nobj
        fsum = 0.0 ; 
        for j = 1:nobj
            if (i ~= j)
                fsum = fsum + (f(j) * f(j) - (0.4 * 0.4));
            end
        end
        fsum = fsum + (f(i) - 1.0) * (f(i) - 1.0);
        if (fsum >= fmax1)
            fmax1 = fsum ;
        end
    end
    fmax2 = 0.0 ;
    for i = 1:nobj
        fmax2 = fmax2 + ((f(i) - 1/sqrt(nobj)) * (f(i) - 1/sqrt(nobj))) ...
            - (0.4 * 0.4) ;
    end
	c(1) = max(fmax1, fmax2);
    ceq = [] ;
end

