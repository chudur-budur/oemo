function [theta, db] = get_radiation_data(gbest, phi_desired, distance)
%GET_RADIATION_DATA From an antenna design variable, generate the 
%the data for the radiation pattern.
%   Takes the design variable and returns theta and db

N = 5000 ;
dim = length(gbest);
phi = linspace(0, 360, N);
% This loop finds out the maximum gain 
yax = zeros(1,N);
yax(1) = array_factor(gbest, (pi/180) * phi(1), ...
            phi_desired, distance, dim);
maxi = yax(1);
for i = 2:5000 
    yax(i) = array_factor(gbest, (pi/180) * phi(i), ...
                    phi_desired, distance, dim);
    if maxi < yax(i)
        maxi = yax(i);
    end;
end;

% This loop normalizes the Y-axis and finds 
% the normalized gain values in decibels 
yax = yax ./ maxi ;
yax = 20 .* log10(yax) ;

theta = phi ;
db = yax ;

end

