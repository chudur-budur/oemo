% This script generates all radiation data for plotting
% It goes through all solutions in a PF and generates
% [theta,db] data vector ansd saves them in /tmp/rad-data/ folder

clc ;
clear ;
addpath('../../src/sosolver');

% where all the data will be stored
datapath = '/tmp/rad-data' ;
% the pf file
pffilepath = 'data/antenna/onsga2r-gen-200.out';
% the pivot file
pivotfilepath = 'data/antenna/extreme-gen-200.out';
% bash command template
bcmd = 'gnuplot -e \"filename=''%s''\" radiation.gp' ;

% open data dir
if exist(datapath, 'dir')
    rmdir(datapath, 's');
end
mkdir(datapath);

% now plotting the extreme points
p = importdata(pivotfilepath);
disp(size(p.data, 1));
n = size(p.data, 1);
for i = 1:n
    x = p.data(i,4:15) ;
    f = p.data(i,1:3);
    [theta, db] = get_radiation_data(x, 180, 0.5);
    header = sprintf('[%.3f]', p.data(i, 1:3));
    filepath = strcat(datapath, '/e-', header, '.out');
    fprintf('%d: saving %s\n', i, filepath);
    fp = fopen(filepath, 'w');
    fprintf(fp, '%10.3f\t%10.3f\n', [theta; db]);
    fclose(fp);
    fprintf('%d: plotting %s\n\n', i, filepath);
    cmd = strcat(sprintf(bcmd, filepath));
    system(cmd)
end

% now plot all the solutions from the pf
a = importdata(pffilepath);
disp(size(a.data, 1));
n = size(a.data, 1);
for i = 1:n
    x = a.data(i,4:15) ;
    f = a.data(i,1:3);
    [theta, db] = get_radiation_data(x, 180, 0.5);
    header = sprintf('[%.3f]', a.data(i, 1:3));
    filepath = strcat(datapath, '/', header, '.out');
    fprintf('%d: saving %s\n', i, filepath);
    fp = fopen(filepath, 'w');
    fprintf(fp, '%10.3f\t%10.3f\n', [theta; db]);
    fclose(fp);
    fprintf('%d: plotting %s\n\n', i, filepath);
    cmd = strcat(sprintf(bcmd, filepath));
    system(cmd)
end
disp('done');