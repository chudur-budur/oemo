% the testing code

rng(123456, 'twister');

N = 12 ; % number of antenna elements

% exhaustive enumeration -- caution, takes 2/3 hours.
% x1 = linspace(0.2, 1.0, 6);
% x2 = linspace(-180, 180, 6);
% x1_ = perms(x1);
% x2_ = perms(x2);
% x = zeros(length(x1_) * length(x2_), N);
% c = 1 ;
% for i = 1:length(x1_)
%     for j = 1:length(x2_)
%         x(c,:) = [x1_(i,:), x2_(j,:)] ;
%         c = c + 1;
%     end
% end
% disp(length(x));
% save('antenna_permx.mat', 'x'); 
% mcf = zeros(length(x), 3);
% parfor i = 1:length(x)
%     if mod(i, 1000) == 0
%         fprintf('evaluated x(%d).\n',i);
%     end
%     mcf(i,:) = antenna(x(i,:));
% end
% % figure(1);
% % scatter3(mcf(:,1), mcf(:,2), mcf(:,3)) % 3-obj
% % and save
% save('antenna_permf.mat', 'mcf')
% fprintf('done.\n')

% code to generate M random samples
% M = 3000 ;
% mcf = zeros(M,3); % 3-obj
% for i = 1:M
%     x = rand(1,N);
%     y = mapvars(x);
%     mcf(i,:) = antenna(y);
% end
% % plot the generated data
% % figure(1);
% % scatter3(mcf(:,1), mcf(:,2), mcf(:,3)) % 3-obj
% % and save
% save('antenna_mcf.mat', 'mcf')
% fprintf('done.\n')

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

% % testing antenna function with extreme point solver
% load pivots_antenna ;
% pv1 = pivots(1, 1:N);
% pv2 = pivots(2, 1:N);
% pv3 = pivots(3, 1:N);
% 
% plot_pattern(5, pv1, 180, 0.5);
% plot_pattern(6, pv2, 180, 0.5);
% plot_pattern(7, pv3, 180, 0.5);
% 
% pvs = [antenna(pv1); antenna(pv2); antenna(pv3)];
% 
% % load antenna_permf ; % 8.2 MB
% datafile = 'antenna_mcf.mat' ;
% load(datafile) ;
% fig = figure(8);
% clf(fig);
% scatter3(mcf(:,1)', mcf(:,2)', mcf(:,3)', 'y') % 3-obj
% hold on ;
% scatter3(pvs(:,1)', pvs(:,2)', pvs(:,3)', 'b');
% xlabel('f1'); ylabel('f2'); zlabel('f3');
% view(26, 22);
% 
% % save the samples into text format for gnuplot
% [pathstr, fname, ext] = fileparts(datafile);
% outfile = strcat('../../report/figs/data/', fname, '.out'); 
% fp = fopen(outfile, 'w');
% fprintf(fp, '%.3f\t%.3f\t%.3f\n', mcf');
% fclose(fp);
% % save the pivots as well.
% pivotfile = '../../report/figs/data/antenna-pivots-sosolver.out' ;
% fp = fopen(pivotfile, 'w');
% fprintf(fp, '%10.3f\t%10.3f\t%10.3f\n', pivots(:, N+1:N+3)');
% fclose(fp);

% plot the azimuth pattern of the solution found from
% single objective ga
% also saves the data for gnuplot
x1 = [0.97565, 0.5715, 0.30977, 0.32848, 0.25926, 0.79118, ...
    163.77, -170.17, 141.65, 163.08, -154.38, 177.09];
[theta, db] = plot_radiation(9, x1, 180, 0.5);
outfile = '../../report/figs/data/antenna/ga-pattern.out';
fp = fopen(outfile, 'w');
fprintf(fp, '%10.3f\t%10.3f\n', [theta; db]);
fclose(fp);