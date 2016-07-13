function f = zdt6(x)
%%   This procedure implements zdt6 function.
%   The canonical zdt6 function is defined as below --
%   f_1 = 1.0 - exp(-4.0 * x_1) * sin(6 * pi * x_1)
%   f_2 = g * (1.0 - (f_1/g)^2)
%   g(x_2, x_3, ..., x_n) = 1.0 + 9.0 * ((sum_{i = 2}^n x_i)/9.0)^0.25
%   0 <= x_i <= 1.0 (i = 1, 2, 3, ..., n)

x1 = x(1);
f1 = 1.0 - (exp(-4.0 * x1) * (sin(6.0 * pi * x1) ^ 6.0));
% sum((x_i - 0.5)^2) is easier than sum(|x_i - 0.5|) is easier than sum(x_i)
% g = sum(x(2:length(x)));
% mod to make this problem harder to converge --
g = sum(abs(x(2:length(x)) - 0.5)) ;
g = g / 9.0 ;
g = g ^ 0.25 ;
g = 1.0 + (9.0 * g) ;
h = 1.0 - ((f1/g) ^ 2.0);
f2 = g * h ;
f = [f1, f2] ;

end