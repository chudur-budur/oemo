#!/usr/bin/python3

import sys
import os
import re
import subprocess


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def get_gpstr(algo_files):
    pt_type = 1
    gpstr = ''
    for algo in sorted(algo_files):
        if algo == 'onsga2r':
            ptlst = [str(i) for i in range(pt_type, pt_type + 5)]
            gpstr += """
        \"{0:s}\" using 1:2 ls {5:s} ti '{10:s}', \\
        \"{1:s}\" using 1:2 ls {6:s} ti '{11:s}', \\
        \"{2:s}\" using 1:2 ls {7:s} ti '{12:s}', \\
        \"{3:s}\" using 1:2 ls {8:s} ti '{13:s}', \\
        \"{4:s}\" using 1:2 ls {9:s} ti '{14:s}', \\"""\
                        .format(*(sorted(algo_files[algo]) + ptlst
                                  + ['extreme pts', 'opp. child', 'onsga2r', 'opp. parent', 'survived pts']))
            pt_type += 5
        else:
            try:
                regex = re.compile('.*all_pop.*')
                gpstr += """        \"{0:s}\" using 1:2 ls {1:d} ti '{2:s}', \\"""\
                    .format([fname for fname in algo_files[algo] if regex.match(fname)][0],
                            pt_type, algo)
                pt_type += 1
            except Exception as e:
                print(e.message, e.args)
                sys.exit()
    return gpstr[:-3]


def save_plot(cmd, out_file):
    print("saving {}".format(out_file))
    lines = parse_gpcmd(cmd)
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
            if os.path.exists(snap_dir):
                prefix_lst = [f.split('-')[0] + '-gen-'
                              for f in os.listdir(snap_dir) if f.endswith('.out')]
                algo_prefix[algo] = (algo_prefix[algo] + prefix_lst) \
                    if algo in algo_prefix else prefix_lst
                algo_prefix[algo] = list(set(algo_prefix[algo]))
                gen_lst += [f.split('-')[2].split('.')[0]
                            for f in os.listdir(snap_dir) if f.endswith('.out')]
                gen_lst = list(set(gen_lst))
            else:
                print(
                    "\'{0:s}\' does not exist, hence skipping.".format(snap_dir))
        gen_lst = sorted(gen_lst, key=lambda x: int(x))
        if gen_lst:
            for gen in gen_lst:
                algo_files = {}
                for algo in algo_prefix:
                    for prefix in algo_prefix[algo]:
                        pth = os.path.join(root_path, algo, prob_name,
                                           'snaps-run-' + run, prefix + gen + '.out')
                        if algo in algo_files:
                            algo_files[algo].append(pth)
                        else:
                            algo_files[algo] = [pth]
                out_file = os.path.join(plot_dir, 'gen-' + gen + '.pdf')
                save_plot(pf2dcmd + get_gpstr(algo_files), out_file)
        else:
            print(
                "gen_lst is empty, hence \'{0:s}\' is not generated.".format(out_file))
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
"""


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./plotburst.py [root_folder] [prob_name] [run]\n")
    sys.exit()

# ./plotburst experiments/ zdt1 [1]
if __name__ == '__main__':
    argv = sys.argv[1:]
    algo_names = ['onsga2r', 'nsga2re', 'nsga2r', 'onsga2rm']
    prob_set = {'zdt1': 2}
    if len(argv) >= 2:
        run = '1' if len(argv) == 2 else argv[2]
        save_plotspf(argv[0], algo_names, argv[1], run)
    else:
        usage()
