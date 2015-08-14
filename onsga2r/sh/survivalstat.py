#!/usr/bin/python3

import sys
import os
import re
import subprocess
import numpy as np


def compute_mean_survival(root_path, problem):
    try:
        path = os.path.join(root_path, 'onsga2r', problem)
        regex = re.compile('all_survival_stat')
        in_files = [os.path.join(path, f)
                    for f in os.listdir(path) if regex.match(f)]
        gen_data = {}
        for f in in_files:
            fd = open(f, 'r')
            for line in fd:
                line = line.strip().split()
                if line:
                    gen_data[int(line[2])] = [float(line[-1])] if int(line[2]) not in gen_data \
                        else gen_data[int(line[2])] + [float(line[-1])]
            fd.close()
        gen_data = {gen: np.mean(data) for gen, data in gen_data.items()}
        min_key = min(gen_data, key=gen_data.get)
        min_val = gen_data[min_key]
        max_key = max(gen_data, key=gen_data.get)
        max_val = gen_data[max_key]
        data_file = os.path.join(
            root_path, 'results', problem, problem + '-survival.stat')
        fd = open(data_file, 'w')
        for gen in sorted(gen_data):
            fd.write("{0:d}\t{1:0.3f}\n".format(gen, gen_data[gen]))
        gens = sorted(list(gen_data.keys()))
        stable_mean = np.mean([gen_data[x] for x in gens[int(len(gens)/2):]])
        return [data_file, [min_key, min_val], [max_key, max_val], stable_mean, gens[-1]]
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def save_plot(cmd, data_file, min_data, max_data, stable_mean, max_gen):
    out_file = os.path.join(os.path.join(*data_file.split('/')[:-1]),
                            data_file.split('/')[-1].split('.')[0] + '.pdf')
    print("saving {}".format(out_file))
    command = cmd.format(out_file, data_file, max_data[0], max_data[1], stable_mean, max_gen)
    lines = parse_gpcmd(command)
    try:
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
    print("Usage: ./survivalstat.py [root_folder] [prob_name]\n")
    sys.exit()

survivalcmd = """
    set term pdf enhanced color dashed
    set output \"{0:s}\"
    set yrange [0:{3:.2f} + 15.0]
    set xlabel \'generations\'
    set ylabel \'mean survival rate\'
    set label 1 \'at generation {2:d}, rate = {3:.2f}%\' at {2:d} + 12.0, {3:.2f} + 5.0
    set arrow from {2:d} + 10.0,{3:.2f} + 3.0 to {2:d},{3:.2f} size screen 0.01,30 lw 4
    set arrow from 5,{4:.2f} to {5:d} - 5,{4:.2f} nohead lt 3 lw 4
    set ytics add {4:.1f}
    plot \"{1:s}\" with lines lw 3 noti
"""

# ./survivalstat.py experiments/ zdt1
if __name__ == '__main__':
    argv = sys.argv[1:]
    if len(argv) == 2:
        root_path = argv[0]
        problem = argv[1]
        [data_file, min_data, max_data, stable_mean, max_gen] = compute_mean_survival(
            root_path, problem)
        save_plot(survivalcmd, data_file, min_data, max_data, stable_mean, max_gen)
        print(stable_mean, max_gen)
    else:
        usage()
