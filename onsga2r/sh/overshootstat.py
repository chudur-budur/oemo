#!/usr/bin/python3

import sys
import os
import re
import subprocess
import numpy as np


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def find_maxrun(path):
    try:
        regex = re.compile('all_overshoot_stat-*')
        return len([d.split('-')[-1] for d in os.listdir(path) if regex.match(d)])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def collate_overshoot_stats(path):
    maxrun = find_maxrun(path)
    data = {}
    try:
        for run in range(1, maxrun + 1):
            file_path = os.path.join(path, 'all_overshoot_stat-' + str(run) + '.out')
            fd = open(file_path, 'r')
            for line in fd:
                vals = [float(val) for val in line.split()]
                data[int(vals[0])] = [vals[1:]] if int(vals[0]) not in data \
                        else data[int(vals[0])] + [vals[1:]]
            fd.close()
        all_gene = []
        zero_gene = []
        for gen in data:
            data[gen] = [np.mean(np.array(list(a))) for a in zip(*data[gen])]
            all_gene.append(data[gen][-2])
            zero_gene.append(data[gen][-1])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return [data, len(data), np.mean(np.array(all_gene)), np.mean(np.array(zero_gene))]


def save_overshoot_stat(root_path, algorithm, problem, data):
    try:
        file_path = os.path.join(root_path, 'results', problem, problem + '-' + algorithm + '-overshoot.stat')
        fd = open(file_path, 'w')
        for gen in data:
            fd.write("{0:d}\t".format(gen) + "\t".join(["{0:10.3f}".format(item) for item in data[gen]]))
            fd.write('\n')
        fd.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return file_path


def save_plot(root_path, problem, algorithm, stat_file, max_gen, all_mean, zero_mean):
    try:
        out_file = os.path.join(root_path, 'results', problem, problem + '-' + algorithm + '-overshoot.pdf')
        if color == 'mono':
            command = gpcmd_mono.format(out_file, stat_file, max_gen, all_mean, zero_mean)
        else:
            command = gpcmd.format(out_file, stat_file, max_gen, all_mean, zero_mean)
        lines = parse_gpcmd(command)
        proc = subprocess.Popen(
            ['gnuplot', '-p'], shell=True, stdin=subprocess.PIPE)
        for line in lines:
            proc.stdin.write(bytes(line, "ascii"))
            proc.stdin.flush()
        proc.stdin.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./overshootstat.py [root_folder] [prob_name]\n")
    sys.exit()


# color = 'mono' will give monochrome plot
color = 'mono'

gpcmd = """
reset
set term pdf enhanced color dashed
set output \"{0:s}\"
set xlabel \"generation\"
set ylabel \"% of individuals with overshot genes\"
set grid
set arrow from 0,{3:.2f} to {2:d},{3:.2f} nohead lw 4 lt 3
set arrow from 0,{4:.2f} to {2:d},{4:.2f} nohead lw 4 lt 3
plot \
        \"{1:s}\" using 1:5 with lines lt 1 lc rgb \'red\' lw 3 ti \"all genes overshot\", \
        \"{1:s}\" using 1:6 with lines lt 1 lc rgb \'green\' lw 3 ti \"0 genes overshot\"
"""


gpcmd_mono = """
reset
set term pdf monochrome dashed
set output \"{0:s}\"
set xlabel \"generation\"
set ylabel \"% of individuals with overshot genes\"
set grid
set arrow from 0,{3:.2f} to {2:d},{3:.2f} nohead lw 4 lt 3
set arrow from 0,{4:.2f} to {2:d},{4:.2f} nohead lw 4 lt 3
plot \
        \"{1:s}\" using 1:5 with lines lt 1 lw 3 ti \"all genes overshot\", \
        \"{1:s}\" using 1:6 with lines lt 4 lw 3 ti \"0 genes overshot\"
"""


if __name__ == '__main__':
    algorithms = ['onsga2r']
    argv = sys.argv[1:]
    if len(argv) == 2:
        for algo in algorithms:
            root_path = argv[0]
            problem = argv[1]
            path = os.path.join(root_path, algo, problem);
            [data, max_gen, all_mean, zero_mean] = collate_overshoot_stats(path)
            stat_file = save_overshoot_stat(root_path, algo, problem, data)
            save_plot(root_path, problem, algo, stat_file, max_gen, all_mean, zero_mean)
    else:
        usage()
