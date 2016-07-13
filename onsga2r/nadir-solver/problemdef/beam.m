function f = beam(x)
%   The beam design problem

h =  x(1); b = x(2); l = x(3); t = x(4) ;
f1 = (1.10471 * h * h * l) + (0.04811 * t * b * (14.0 + l));
f2 = 2.1952 / (t * t * t * b) ;

f = [f1, f2];

end