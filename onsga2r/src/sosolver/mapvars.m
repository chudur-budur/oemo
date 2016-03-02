function [yvals] = mapvars(xvals)
%MAPVARS Maps the given x to y
%   xvals: is an array of N random variables in U(0,1)
%   yvals: y(1:N/2) is an array of random variables in [1,N]
%          y(N/2+1:N) is an array of random variables in [-180, 180]

N = length(xvals);
x1_min = 1 ; x1_max = N ;
x2_min = -180 ; x2_max = 180 ;
x1_ = round(x1_min + (xvals(1:N/2) .* (x1_max - x1_min)));
x2_ = x2_min + (xvals(N/2+1:N) .* (x2_max - x2_min));
yvals = [x1_, x2_];

end

