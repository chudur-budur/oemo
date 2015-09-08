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


def get_gpstr_2d(algo_files):
    lstyle = 1
    gpstr = ''
    algoname_regex = re.compile('onsga2r*')
    for algo in sorted(algo_files):
        if algoname_regex.match(algo):
            lslst = [str(i) for i in range(lstyle, lstyle + 5)]
            args = sorted(algo_files[algo]) + lslst \
                + ['extreme-pts', 'opp-child',
                    'opp-parent', algo, 'survived-pts']
            gpstr += """
            \"{0:s}\" using 1:2 w circles ls {5:s} ti '{10:s}', \\
            \"{1:s}\" using 1:2 w circles ls {6:s} ti '{11:s}', \\
            \"{2:s}\" using 1:2 w circles ls {7:s} ti '{12:s}', \\
            \"{3:s}\" using 1:2 w circles ls {8:s} ti '{13:s}', \\
            \"{4:s}\" using 1:2 w circles ls {9:s} ti '{14:s}', \\\n""".format(*args)
            lstyle += 5
        else:
            try:
                regex = re.compile('.*all_pop.*')
                gpstr += """            \"{0:s}\" using 1:2 w circles ls {1:s} ti '{2:s}', \\\n"""\
                    .format([fname for fname in algo_files[algo] if regex.match(fname)][0],
                            str(lstyle), algo)
                lstyle += 1
            except Exception as e:
                print(e.message, e.args)
                sys.exit()
    gpstr = os.linesep.join([s for s in gpstr.splitlines() if s])
    return gpstr[:-3]


def get_gpstr_3d(algo_files):
    lstyle = 1
    gpstr = ''
    algoname_regex = re.compile('onsga2r*')
    for algo in sorted(algo_files):
        if algoname_regex.match(algo):
            lslst = [str(i) for i in range(lstyle, lstyle + 5)]
            args = sorted(algo_files[algo]) + lslst \
                + ['extreme-pts', 'opp-child',
                    'opp-parent', algo, 'survived-pts']
            gpstr += """
            \"{0:s}\" using 1:2:3 w circles ls {5:s} ti '{10:s}', \\
            \"{1:s}\" using 1:2:3 w circles ls {6:s} ti '{11:s}', \\
            \"{2:s}\" using 1:2:3 w circles ls {7:s} ti '{12:s}', \\
            \"{3:s}\" using 1:2:3 w circles ls {8:s} ti '{13:s}', \\
            \"{4:s}\" using 1:2:3 w circles ls {9:s} ti '{14:s}', \\\n""".format(*args)
            lstyle += 5
        else:
            try:
                regex = re.compile('.*all_pop.*')
                gpstr += """            \"{0:s}\" using 1:2:3 w circles ls {1:s} ti '{2:s}', \\\n"""\
                    .format([fname for fname in algo_files[algo] if regex.match(fname)][0],
                            str(lstyle), algo)
                lstyle += 1
            except Exception as e:
                print(e.message, e.args)
                sys.exit()
    gpstr = os.linesep.join([s for s in gpstr.splitlines() if s])
    return gpstr[:-3]


def save_pdf_plot(algo_files, out_file, problem):
    print("saving {}".format(out_file))
    prob_set = {'zdt1': 2, 'zdt2': 2, 'zdt3': 2, 'zdt4': 2, 'zdt6': 2, \
            'dtlz1': 3, 'dtlz2': 3, 'dtlz3': 3, 'dtlz4': 3, 'dtlz5': 3, 'dtlz6': 3, 'dtlz7': 3}
    if prob_set[problem] == 2:
        cmd = pf2dcmd.format(out_file) + get_gpstr_2d(algo_files)
    else:
        cmd = pf3dcmd.format(out_file) + get_gpstr_3d(algo_files)
    lines = parse_gpcmd(cmd)
    # print(cmd)
    # for line in lines:
    #     print(line)
    # return
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


def save_pf(root_path, algo_names, prob_name, run):
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
                print("warning: \'{0:s}\' does not exist, hence skipping.".format(snap_dir))
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
                save_pdf_plot(algo_files, out_file, prob_name)
        else:
            print("warning: gen_lst is empty, hence \'{0:s}\' is not generated.".format(out_file))
    except Exception as e:
        print(e.message, e.args)
        sys.exit()

pf2dcmd = """
	set term pdf enhanced color
	set style fill transparent solid 0.75 noborder
        set output \"{0:s}\"
	load \'~/gnuplot-utils/gnuplot-palettes/dark2.pal\'
	set style circle radius screen 0.0075
	set xlabel \'f1\'
	set ylabel \'f2\'
	set key out horiz bot cent
	plot \\
"""

pf3dcmd = """
	set term pdf enhanced color
	set style fill transparent solid 0.75 noborder
        set output \"{0:s}\"
	load \'~/gnuplot-utils/gnuplot-palettes/dark2.pal\'
	set style circle radius screen 0.0075
	set xlabel \'f1\'
	set ylabel \'f2\'
	set key out horiz bot cent
	splot \\
"""


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./plotburst.py [root_folder] [prob_name] [run]\n")
    sys.exit()

# ./plotburst experiments/ zdt1 [1]
if __name__ == '__main__':
    argv = sys.argv[1:]
    # algo_names = ['onsga2r', 'nsga2re', 'nsga2r', 'onsga2rm']
    # algo_names = ['onsga2r', 'onsga2rm']
    algo_names = ['nsga2r', 'onsga2rw']
    # algo_names = ['onsga2r']
    if len(argv) >= 2:
        run = '1' if len(argv) == 2 else argv[2]
        save_pf(argv[0], algo_names, argv[1], run)
    else:
        usage()
