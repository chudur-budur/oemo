function [c, ceq] = beam_constfunc(x)
%   The caint functions for the beam design problem

h =  x(1); b = x(2); l = x(3); t = x(4) ;
pcx = 64746.022 * (1 - 0.0282346 * t) * t * b * b * b ;
sigmax = 504000 / (t * t * b);
tau_ = 6000 / (sqrt(2) * h * l) ;
tau__ = (6000 * (14 + 0.5 * l) * sqrt(0.25 * (l * l + ((h + t)^2.0)))) ...
    / (2 * (0.707 * h * l * (((l * l) / 12) + (0.25 * ((h + t)^2.0))))) ;
taux = sqrt((tau_ * tau_) + (tau__ * tau__) ...
    + ((l * tau_ * tau__) / sqrt(0.25 * (l * l + ((h + t)^2.0)))));

c(1) = 1.0 - (taux / 13600);
c(2) = 1.0 - (sigmax / 30000);
c(3) = 1.0 - (h/b) ;
c(4) = (pcx/6000) - 1.0 ; 
ceq = [] ;
end