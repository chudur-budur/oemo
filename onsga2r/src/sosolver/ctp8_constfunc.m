function [c, ceq] = ctp8_constfunc(x)
% CTP8 constraints definitions.

theta = 0.1 * pi;
a = 40.0;
b = 0.5;
c_ = 1.0;
d = 2.0;
e = -2.0;

f = ctp8(x) ;

% constraints
xp1 = ((f(2) - e) * cos(theta)) - (f(1) * sin(theta));
xp2 = ((f(2) - e) * sin(theta)) + (f(1) * cos(theta));
xp2 = b * pi * (xp2 ^ c_);
xp2 = abs(sin(xp2));
xp2 = a * (xp2^d);
c(1) = xp1/xp2 - 1.0;

theta = -0.05 * pi;
a = 40.0;
b = 2.0;
c_ = 1.0;
d = 6.0;
e = 0.0;

% constraints
xp1 = ((f(2) - e) * cos(theta)) - (f(1) * sin(theta));
xp2 = ((f(2) - e) * sin(theta)) + (f(1) * cos(theta));
xp2 = b * pi * (xp2 ^ c_);
xp2 = abs(sin(xp2));
xp2 = a * (xp2^d);
c(2) = xp1/xp2 - 1.0;

ceq = [] ;
end