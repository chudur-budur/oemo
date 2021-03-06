function f = zdt3(x)
%%   This procedure implements zdt3 function.
%   The canonical zdt3 function is defined as below --
%   f_1 = x_1
%   f_2 = g * h
%   g(x_2, x_3, ..., x_n) = 1.0 + (9/(n - 1)) sum_{i = 2}^n x_i
%   h(f_1,g) = 1.0 - sqrt(f_1/g) - (f_1/g)*sin(10 * pi * f_1)
%   0 <= x_i <= 1.0 (i = 1, 2, 3, ..., n)

f1 = x(1);
% sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i)
% g = sum(x(2:length(x)));
% mod to make this problem harder to converge --
g = sum(abs(x(2:length(x)) - 0.5));
g = 9.0 * g / (length(x)-1) ;
g = 1.0 + g ;
h = 1.0 - sqrt(f1/g) - ((f1/g) * sin(10.0 * pi * f1));
f2 = g * h ;
f = [f1, f2] ;

end