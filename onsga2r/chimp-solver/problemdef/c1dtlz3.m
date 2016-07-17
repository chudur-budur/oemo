function f = c1dtlz3(x)
%%   This procedure implements c1dtlz3 function.

global nobj ;

k = length(x) - nobj + 1;

% x_i - 0.5 was already done in the actual problem
% definition, so no adjustment is necessary.

x_ = x(((end - k) + 1):end);
g = sum(((x_ - 0.5) .* (x_ - 0.5)) - cos(20.0 .* pi .* (x_ - 0.5)));
g = 100.0 * (k + g);
f = ones(1,nobj) + g ;

for i = 1:nobj
    f(i) = f(i) * prod(cos(x(1:nobj - i) .* (0.5 * pi)));
    if (i ~= 1)
        f(i) = f(i) * sin(x((nobj - i) + 1) * (0.5 * pi));
    end
end
end