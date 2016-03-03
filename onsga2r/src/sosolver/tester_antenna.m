% the testing code

rng(123456, 'twister');

N = 12 ; % number of antenna elements

% code to generate 3000 sample objective values and save in
% the mat data format.
M = 2000 ;
mcf = zeros(M,3); % 3-obj
for i = 1:M
    x = rand(1,N);
    mcf(i,:) = antenna(x);    
end
% % plot the generated data
figure(1);
scatter3(mcf(:,1), mcf(:,2), mcf(:,3)) % 3-obj
% and save
save('antenna_mcf.mat', 'mcf')
fprintf('done.\n')

% display the frequency domain plot of a single solution
% x_ = [0.31734, 0.066496, 0.88683, 0.66221, 0.12396, 0.43691, 0.28435, 0.41935];
% x = mapvars(x_);
% plot_gain(2, x, 180, 0.5);
% x_ = [0.3093, 0.6185, 0.68918, 0.12031, 0.4014, 0.81329, 0.50161, 0.71623];
% x = mapvars(x_);
% plot_gain(3, x, 180, 0.5);
% x_ = [0.55461, 0.40988, 0.58627, 0.64679, 0.023027, 0.76575, 0.78093, 0.16094];
% x = mapvars(x_);
% plot_gain(4, x, 180, 0.5);

% testing array_factor
% x_ = rand(1,N)
% x = mapvars(x_)
% y = array_factor(x, (pi/180) * 0.25, 180, 0.5, length(x))
% x_ = rand(1,N)
% x = mapvars(x_)
% y = array_factor(x, (pi/180) * 0.25, 180, 0.5, length(x))

% testing trapezoid
% x_ = rand(1,N)
% x = mapvars(x_)
% uavg = trapezoid(x, 0, 2 * pi, 50, 180, 0.5, length(x))
% x_ = rand(1,N)
% x = mapvars(x_)
% uavg = trapezoid(x, 0, 2 * pi, 50, 180, 0.5, length(x))

% testing antenna function with one instance
% x = rand(1,N)
% f = antenna(x)
% x = rand(1,N)
% f = antenna(x)

% testing antenna function with extreme point solver
% patternsearch results
% 1st obj
% x1 = [0.84462, 0.13638, 0.16392, 0.46169, ...
%       0.28273, 0.97768, 0.92514, 0.39731, ...
%       0.68641, 0.77553, 0.52271, 0.95873];
% % 2nd obj
% x2 = [0.99962, 0.31066, 0.25892, 0.12385, ...
%       0.68773, 0.68126, 0.99951, 0.93460, ...
%       0.92962, 0.66357, 0.98771, 0.99131];
% % 3rd obj
% x3 = [0.89962, 0.25138, 0.12392, 0.27527, ...
%       0.50773, 0.64554, 0.96951, 0.45795, ...
%       0.69693, 0.67357, 0.61271, 0.96131];

% fmincon results
% obj1
x1 = [0.73494, 0.38080, 0.30814, 0.31818, ...
      0.54510, 0.56339, 0.87562, 0.64308, ...
      0.67407, 0.60221, 0.55992, 0.89254];
% obj2
x2 = [0.92962, 0.31638, 0.18392, 0.20456, ...
      0.56773, 0.59554, 0.96451, 0.65318, ...
      0.74891, 0.65357, 0.74771, 0.96131];
% obj3
x3 = [0.50000, 0.50000, 0.50000, 0.50000, ...
      0.50000, 0.50000, 0.58451, 0.54722, ...
      0.41012, 0.51975, 0.56110, 0.55947];

% x = mapvars(x1);
% plot_gain(5, x, 180, 0.5);
% x = mapvars(x2);
% plot_gain(6, x, 180, 0.5);
% x = mapvars(x3);
% plot_gain(7, x, 180, 0.5);

f1 = antenna(x1);
f2 = antenna(x2);
f3 = antenna(x3);
exf = [f1; f2; f3];

load antenna_mcf ;
figure(1);
scatter3(mcf(:,1), mcf(:,2), mcf(:,3), 'y') % 3-obj
hold on ;
scatter3(exf(:,1), exf(:,2), exf(:,3), 'b');