function f = dtlz2(x)
%   This procedure implements dtlz2 function.

global nobj ;

k = length(x) - nobj + 1;

x_ = x(((end-k)+1):end);
g = sum((x_ - 0.5) .* (x_ - 0.5));
f = ones(1,nobj) + g ;

for i = 1:nobj
    f(i) = f(i) * prod(cos(x(1:nobj - i) .* (0.5 * pi)));
    if (i ~= 1)
        f(i) = f(i) * sin(x((nobj - i) + 1) * (0.5 * pi));
    end
end
end