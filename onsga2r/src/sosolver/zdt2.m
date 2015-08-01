function f = zdt2(x)
%   This procedure implements zdt2 function.
%   The canonical zdt2 function is defined as below --
%   f_1 = x_1
%   f_2 = g * (1.0 - (f_1/g)^2)
%   g(x_2, x_3, ..., x_n) = 1.0 + (9/(n - 1)) sum_{i = 2}^n x_i
%   0 <= x_i <= 1.0 (i = 1, 2, 3, ..., n)

f1 = x(1);
g = sum(x(2:length(x)));
g = (g * 9.0) / (length(x)-1) ;
g = 1.0 + g ;
h = 1.0 - ((f1 / g) ^ 2.0);
f2 = g * h ;
f = [f1, f2];
end