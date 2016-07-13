function [c, ceq] = gear_constfunc(x)
%   The constraint functions for the gear design problem

% x_ = round(x) ; 
x_ = x ; 
f1 = abs(6.931 - ((x_(3)/x_(1)) * (x_(4)/x_(2))));
c(1) = (f1/(6.931 * 0.5)) - 1.0 ;
ceq = [] ;
end