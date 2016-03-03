% the testing code

rng(123456, 'twister');

N = 12 ; % number of antenna elements

% % code to generate 3000 sample objective values and save in
% % the mat data format.
% M = 5000 ;
% mcf = zeros(M,3); % 3-obj
% for i = 1:M
%     x = rand(1,N);
%     y = mapvars(x);
%     mcf(i,:) = antenna(y);
% end
% % plot the generated data
% figure(1);
% scatter3(mcf(:,1), mcf(:,2), mcf(:,3)) % 3-obj
% % and save
% save('antenna_mcf.mat', 'mcf')
% fprintf('done.\n')

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
% y = mapvars(x)
% f = antenna(y)
% x = rand(1,N)
% y = mapvars(x)
% f = antenna(x)

% testing antenna function with extreme point solver
load pivots_antenna ;
x1 = pivots(1, 1:N);
x2 = pivots(2, 1:N);
x3 = pivots(3, 1:N);

plot_gain(5, x1, 180, 0.5);
plot_gain(6, x2, 180, 0.5);
plot_gain(7, x3, 180, 0.5);

f1 = antenna(x1);
f2 = antenna(x2);
f3 = antenna(x3);
pvf = [f1; f2; f3];

load antenna_mcf ;
figure(8);
scatter3(mcf(:,1), mcf(:,2), mcf(:,3), 'y') % 3-obj
hold on ;
scatter3(pvf(:,1), pvf(:,2), pvf(:,3), 'b');