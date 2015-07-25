#!/usr/bin/python3

import os
import sys
import subprocess


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def save_plot(cmd, file_lst, out_file):
    print("saving {}".format(out_file))
    command = cmd.format(out_file, *file_lst)
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


def save_plotspf(root_path, algo_names, prob_name, run):
    algo_prefix = {}
    gen_lst = []
    try:
        plot_dir = os.path.join(
            root_path, 'results', prob_name, 'snaps-run-' + run)
        if not os.path.exists(plot_dir):
            os.makedirs(plot_dir)
        for algo in algo_names:
            snap_dir = os.path.join(
                root_path, algo, prob_name, 'snaps-run-' + run)
            prefix_lst = [f.split('-')[0] + '-gen-'
                          for f in os.listdir(snap_dir) if f.endswith('.out')]
            algo_prefix[algo] = (algo_prefix[algo] + prefix_lst) \
                if algo in algo_prefix else prefix_lst
            algo_prefix[algo] = list(set(algo_prefix[algo]))
            gen_lst += [f.split('-')[2].split('.')[0]
                        for f in os.listdir(snap_dir) if f.endswith('.out')]
            gen_lst = list(set(gen_lst))
        gen_lst = sorted(gen_lst, key=lambda x: int(x))
        for gen in gen_lst:
            file_lst = []
            for algo in algo_prefix:
                for prefix in algo_prefix[algo]:
                    file_lst.append(os.path.join(root_path, algo, prob_name,
                                                 'snaps-run-' + run, prefix + gen + '.out'))
            file_lst = sorted(file_lst)
            out_file = os.path.join(plot_dir, 'gen-' + gen + '.pdf')
            save_plot(pf2dcmd, file_lst, out_file)
    except Exception as e:
        print(e.message, e.args)
        sys.exit()

pf2dcmd = """
    set term pdf enhanced color
    set output \"{0:s}\"
    # load \'~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Set3.plt\'
    # load \'~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Set2.plt\'
    # load \'~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Pastel1.plt\'
    # load \'~/gnuplot-utils/gnuplot-colorbrewer/sequential/Oranges.plt\'
    # load \'~/gnuplot-utils/gnuplot-colorbrewer/diverging/Spectral.plt\'
    set xlabel \'f1\'
    set ylabel \'f2\'
    plot \\
            \"{1:s}\" using 1:2 ls 1 ti 'nsga2', \\
            \"{2:s}\" using 1:2 ls 2 ti 'extreme points', \\
            \"{3:s}\" using 1:2 ls 3 ti 'opposite child points', \\
            \"{4:s}\" using 1:2 ls 4 ti 'onsga2', \\
            \"{5:s}\" using 1:2 ls 5 ti 'opposite parent points', \\
            \"{6:s}\" using 1:2 ls 6 ti 'opposite survived points'
"""


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./plotburst.py [root_folder] [prob_name] [run]\n")
    sys.exit()

# ./plotburst experiments/ zdt1 [1]
if __name__ == '__main__':
    argv = sys.argv[1:]
    algo_names = ['nsga2r', 'onsga2r']
    prob_set = {'zdt1': 2}
    if len(argv) >= 2:
        run = '1' if len(argv) == 2 else argv[2]
        save_plotspf('../experiments', algo_names, argv[1], run)
    else:
        usage()
