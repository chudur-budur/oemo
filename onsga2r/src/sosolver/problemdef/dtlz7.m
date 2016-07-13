function f = dtlz7(x)
%   This procedure implements dtlz7 function.

global nobj ;

k = length(x) - nobj + 1;

x_ = x(((end-k)+1):end);
g = 1.0 + ((9.0 * sum(x_)) / k);
f = zeros(1, nobj);
f(1:nobj-1) = x(1:nobj-1);
h = sum((f(1:nobj-1) ./ (1.0 + g)) .* (1.0 + sin((3.0 * pi) .* f(1:nobj-1))));
h = nobj - h;
f(end) = (1.0 + g) * h;

end