function f = dtlz4(x)
%%   This procedure implements dtlz4 function.

global nobj ;
alpha = 100.0 ;

k = length(x) - nobj + 1;

x_ = x(((end - k) + 1):end);
% similar, no need to adjust, follows from the original definition.
% g = sum((x_ - 0.5) .* (x_ - 0.5));
% but this adjustment will make nsga2 to converge slow
g = sum(abs((x_ - 0.5)));
f = ones(1,nobj) + g ;

for i = 1:nobj
    f(i) = f(i) * prod(cos((x(1:nobj - i) .^ alpha) .* (0.5 * pi)));
    if (i ~= 1)
        f(i) = f(i) * sin((x((nobj - i) + 1) ^ alpha) * (0.5 * pi));
    end
end
end