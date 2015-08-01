function f = dtlz5(x)
%   This procedure implements dtlz5 function.

global nobj ;

k = length(x) - nobj + 1;

x_ = x(((end-k)+1):end);
g = sum((x_ - 0.5) .* (x_ - 0.5));
t = pi / (4.0 * (1.0 + g)) ;
theta = zeros(1, nobj);
theta(1) = x(1) * (pi / 2.0) ;
theta(2:nobj) = t .* (1.0 + ((2.0 * g) .* x(2:nobj)));
f = ones(1,nobj) + g ;

for i = 1:nobj
    f(i) = f(i) * prod(cos((theta(1:nobj - i))));
    if (i ~= 1)
        f(i) = f(i) * sin(theta((nobj - i) + 1));
    end
end
end