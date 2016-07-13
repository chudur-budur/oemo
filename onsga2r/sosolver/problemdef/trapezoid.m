function[q] = trapezoid(xval, upper, lower, N1, ...
                                phi_desired, distance,dim)         
% This function performs integration by trapezoidal rule

y = zeros(1,N1+1);

h = (upper-lower) / N1 ;
x = lower ;
y(1) = abs(realpow(array_factor(xval, x, ...
    phi_desired, distance, dim), 2) * sin(x - pi/2));
for i = 2:N1+1 
    x = x + h;
    y(i) = abs(realpow(array_factor(xval, x, ...
        phi_desired, distance, dim), 2) * sin(x - pi/2));
end;

y(2:N1) = 2 .* y(2:N1);
q = (h / 2) * sum(y);

end