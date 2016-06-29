function f = antenna(x)
% function [sllreturn, y, y3, y1, sumf] = antenna(xvals)

% This function calculates the fitness value of 
% array 'x1' which is returned in 'y'

% not sure, what the f*ck this is for, not used at all
% global directivity 

% custom pi
pi = 3.141592654;

null = [50, 120] ;
phi_desired = 180 ;
distance = 0.5 ;

dim = length(x);
% x_ = mapvars(x) % not doing it anymore
x_ = x;

% y = 0;
num_null = size(null, 2); % 1,2 = size(null)
num1 = 300;
phi = linspace(0, 360, num1);

phizero = 0;
yax = zeros(1, num1);
yax(1) = array_factor(x_, (pi/180) * phi(1), phi_desired, distance, dim);
maxi = yax(1);
phi_ref = 1;
% This loop finds out the maximum gain 
for i = 2:num1 
    yax(i) = array_factor(x_, (pi/180) * phi(i), phi_desired, distance, dim);
    if maxi < yax(i)
        maxi = yax(i);
        phizero = phi(i);
        phi_ref = i;
    end;
end;

% maxtem = 0 ;
lobes = cell(1,1);
count = 0 ;
if yax(1) > yax(num1) && yax(1) > yax(2)
    count = count + 1;
    % sidelobes(count) = yax(1);
    lobes{count} = yax(1);
    % sllphi(count) = phi(1); % wtf, sllphi has not being used anywhere.
end
if yax(num1) > yax(1) && yax(num1) > yax(num1-1)
    count = count + 1;
    % sidelobes(count) = yax(num1);
    lobes{count} = yax(num1);
    % sllphi(count) = phi(num1);
end
for i = 2:num1-1
    if yax(i) > yax(i+1) && yax(i) > yax(i-1)
        count = count + 1;
        % sidelobes(count) = yax(i);
        lobes{count} = yax(i);
        % sllphi(count) = phi(i);
    end
end
sidelobes = [lobes{:}];

% sort?? matlab coders are notorious for their lower IQ, 
% now looks like this is a 'fact'
% sidelobes = sort(sidelobes, 'descend');

% lets do this instead --
[ignore, index] = max(sidelobes);
sidelobes(index) = realmin('double');
y = max(sidelobes)/maxi;
sllreturn = 20 * log10(y);

upper_bound = 180;
lower_bound = 180;
for i = 1:num1/2
    if (phi_ref+i) > num1-1
        upper_bound = 180;
        break;
    end
    % tem = yax(phi_ref+i);
    if yax(phi_ref + i) < yax(phi_ref + i - 1) && ...
            yax(phi_ref + i) < yax(phi_ref + i + 1)
        upper_bound = phi(phi_ref + i) - phi(phi_ref);
        break;
    end;
end
for i = 1:num1/2
    if (phi_ref - i) < 2
        lower_bound = 180;
        break;
    end
    % tem = yax(phi_ref - i);
    if yax(phi_ref - i) < yax(phi_ref - i - 1) && ...
            yax(phi_ref - i) < yax(phi_ref - i + 1)
        lower_bound = phi(phi_ref) - phi(phi_ref - i);
        break;
    end;
end
bwfn = upper_bound + lower_bound;

% bwfn
% y = maxtem;
% The objective function for null control is calculated here
y1 = 0;
for i = 1:num_null     
    y1 = y1 + (array_factor(x_, null(i), phi_desired, distance, dim)/maxi);
end;

% wtf, nothing below is being used.
% y2 = 0;
% uavg = trapezoid(x_, 0, 2*pi, 50, phi_desired, distance, dim);
% y2 = abs(2 * pi * maxi * maxi/uavg);
% directivity = 10 * log10(y2);

y3 = abs(phizero - phi_desired);
if y3 < 5
    y3 = 0;
end

y = 0;
if bwfn > 80
    y = y + abs(bwfn - 80);
end;

% directivity
% y3 = abs((phizero - phi_desired) * (pi/180));
% y = y + y1 + 1/y2 + y3;

% sllreturn = 1st term, suppress sidelobes
% y = 2nd term, maximize directivity
% y3 = 3rd term, minimize |phi_0 - phi_des|
% y1 = 4th term, null control 

% f = sllreturn + y + y3 + y1 ; % single objective case
f = [sllreturn, y + y3, y1] ; % MOP case

end