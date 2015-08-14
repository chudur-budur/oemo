function f = zdt4(x)
%   This procedure implements zdt4 function.
%   The canonical zdt4 function is defined as below --
%   f_1 = x_1
%   f_2 = g * h
%   g(x_2, x_3, ..., x_n) = 91.0 + sum_{i = 2}^n x_i^2 - 10 * cos(4 * pi * x_i)
%   h(f_1,g) = 1.0 - sqrt(f_1/g)
%   0 <= x_i <= 1.0 (i = 1, 2, 3, ..., n)

f1 = x(1);
gvals = x(2:length(x));
g = (gvals .* gvals) - (10 .* cos(4.0 .* pi .* gvals)); 
g = 1.0 + (10.0 * (length(x) - 1.0)) + sum(g);
h = 1.0 - sqrt(f1/g);
f2 = g * h ;
f = [f1, f2] ;
end