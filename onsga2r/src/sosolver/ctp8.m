function f = ctp8(x)
%   This procedure implements CTP4 function.

g = 1.0 + x(2);
f1 = x(1);
f2 = g * (1.0  - sqrt(f1/g));

f = [f1, f2];

end