function f = dtlz1(x)
%%   This procedure implements dtlz1 function.

global nobj ;

k = length(x) - nobj + 1; % k = 12 - 3 + 1 = 10

x_ = x(((end - k) + 1):end); % 12 - 10 + 1 = 3
% (x_i - 0.5) was in the original definition
g = 100.0 * (k + sum(((x_ - 0.5) .* (x_ - 0.5)) - ...
                        cos(20.0 .* pi .* (x_ - 0.5))));
f = (ones(1,nobj) + g) .* 0.5 ;

for i = 1:nobj
    f(i) = f(i) * prod(x(1:nobj - i));
    if (i ~= 1)
        f(i) = f(i) * (1.0 - x((nobj - i) + 1));
    end
end
end