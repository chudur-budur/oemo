function[] = plot_gain(nplot, gbest, phi_desired, distance)

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

figure(nplot);
plot(phi, yax, 'g');
xlabel('Azimuth angle(deg)');
ylabel('Gain(db)');

end