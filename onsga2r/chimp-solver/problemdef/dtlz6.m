function f = dtlz6(x)
%%   This procedure implements dtlz6 function.

global nobj ;

k = length(x) - nobj + 1;

x_ = x(((end - k) + 1):end);
% g = sum(x_ .^ 0.1);
% this might make the nsga2 to converge slower.
g = sum(abs(x_ - 0.5) .^ 0.1);
t = pi / (4.0 * (1.0 + g)) ;
theta = zeros(1, nobj - 1);
theta(1) = x(1) * (pi / 2.0) ;
theta(2:nobj - 1) = t .* (1.0 + ((2.0 * g) .* x(2:nobj - 1)));
f = ones(1,nobj) + g ;

for i = 1:nobj
    f(i) = f(i) * prod(cos((theta(1:nobj - i))));
    if (i ~= 1)
        f(i) = f(i) * sin(theta((nobj - i) + 1));
    end
end
end