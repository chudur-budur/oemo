function [c, ceq] = ctp4_constfunc(x)
% Constraints definitions for ct4 problem

theta = -0.2 * pi ;
a = 0.75;
b = 10.0;
c_ = 1.0;
d = 0.5;
e = 1.0;

f = ctp4(x) ;

% constraints
xp1 = ((f(2) - e) * cos(theta)) - (f(1) * sin(theta));
xp2 = ((f(2) - e) * sin(theta)) + (f(1) * cos(theta));
xp2 = b * pi * (xp2 ^ c_);
xp2 = abs(sin(xp2));
xp2 = a * (xp2^d);
c(1) = xp1/xp2 - 1.0;
ceq = [] ;
end