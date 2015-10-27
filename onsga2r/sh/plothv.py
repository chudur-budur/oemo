#!/usr/bin/python3

import sys
import os
import time
import re
import shutil
import subprocess
import uuid
import numpy as np
import operator as op

def within(vals, ref):
    return all(list(map(op.le, vals, ref)))

def load_data(file_path, nobj, ref):
    fronts = {}
    try:
        fd = open(file_path, 'r')
        header = [item for item in fd.readline().split() if item.isnumeric()]
        for line in fd:
            vals = line.split()
            if within([float(v) for v in vals[0:nobj]], ref):
                if header[0] == '1':
                    fronts[vals[-3]] = [vals[0:nobj]] if vals[-3] not in fronts \
                        else fronts[vals[-3]] + [vals[0:nobj]]
                elif not (vals[-3] == '1' and float(vals[-2]) == 1.00e+14):
                    fronts[vals[-3]] = [vals[0:nobj]] if vals[-3] not in fronts \
                        else fronts[vals[-3]] + [vals[0:nobj]]
        fd.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return [header, fronts]


def calc_hv(fronts, ref):
    tmp_file = "/tmp/{:s}.out".format(str(uuid.uuid4()))
    try:
        if fronts:
            wfg = os.path.join(os.path.join('/', *os.path.abspath(__file__).split('/')[:-2]), 'wfg')
            if os.path.exists(wfg):
                fd = open(tmp_file, 'w')
                fd.write('#\n')
                for key in sorted(fronts):
                    for lst in fronts[key]:
                        fd.write("{:s}\n".format(' '.join(lst)))
                    fd.write('#\n')
                fd.close()
                args = [wfg, tmp_file] + [str(v) for v in ref]
                hv_str = subprocess.check_output(args)
                hv = float(hv_str.decode("utf-8").rstrip('\n'))
                os.remove(tmp_file)
            else:
                sys.exit("error: file {:s} does not exist, build it with 'make wfg'.".format(wfg))
        else:
            hv = 0.0
    except Exception as e:
        if os.path.exists(tmp_file):
            os.remove(tmp_file)
        print(e.message, e.args)
        sys.exit()
    if os.path.exists(tmp_file):
        os.remove(tmp_file)
    return hv


def find_maxrun(path):
    try:
        regex = re.compile('snaps-run-*')
        return len([d.split('-')[-1] for d in os.listdir(path) if regex.match(d)])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def dump_hv_stats_gen(root_path, algo_name, prob_name, max_gen, nobj, ref):
    max_run = find_maxrun(os.path.join(root_path, *[algo_name, prob_name]))
    print("generating hv data for problem {0:s} over max_gen = {1:d} and max_run = {2:d} for {3:s}".
          format(prob_name, max_gen, max_run, algo_name))
    hv_dir = os.path.join(root_path, 'results', prob_name)
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(hv_dir, prob_name + '-' + algo_name + '-hv.stat')
        fd = open(file_name, 'w')
        gen_fe = {}
        for gen in range(1, max_gen + 1):
            hv_lst = []
            for run in range(1, max_run + 1):
                # path = "../experiments/onsga2r/{0:s}/snaps-run-{1:d}/all_pop-gen-{2:d}.out"
                path = os.path.join(root_path,
                                    *[algo_name, "{}".format(prob_name),
                                      "snaps-run-{}".format(run),
                                      "all_pop-gen-{}.out".format(gen)])
                [header, fronts] = load_data(path, nobj, ref)
                gen_fe[gen] = [int(header[1])] if int(header[1]) not in gen_fe \
                        else gen_fe[gen] + int(header[1])
                hv_lst.append(calc_hv(fronts, ref))
            a = np.array(hv_lst)
            iqr = [header[1],  # header 0 is generation, 1 is fe
                   '{:.3f}'.format(np.min(a)),
                   '{:.3f}'.format(np.percentile(a, 25)),
                   '{:.3f}'.format(np.percentile(a, 50)),
                   '{:.3f}'.format(np.percentile(a, 75)),
                   '{:.3f}'.format(np.max(a)),
                   '{:.3f}'.format(np.mean(a))]
            fd.write('\t'.join(iqr))
            fd.write('\n')
        fd.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return [file_name, gen_fe[max_gen][0]]


def find_maxgen(path):
    try:
        regex = re.compile('all_pop-gen-*')
        return len([d.split('-')[-1] for d in os.listdir(path) if regex.match(d)])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def dump_hv_stats_feval(root_path, algo_name, prob_name, max_feval, nobj, ref):
    max_run = find_maxrun(os.path.join(root_path, *[algo_name, prob_name]))
    max_gen = find_maxgen(os.path.join(root_path, *[algo_name, prob_name, "snaps-run-1"]))
    print("generating hv data for problem {0:s} over max_feval = {1:d} and max_run = {2:d} for {3:s}".
          format(prob_name, max_feval, max_run, algo_name))
    hv_dir = os.path.join(root_path, 'results', prob_name)
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(hv_dir, prob_name + '-' + algo_name + '-hv.stat')
        fd = open(file_name, 'w')
        gen_fe = {}
        # for gen in range(1, max_gen + 1):
        fe = 0
        gen = 1
        while fe < max_feval:
            hv_lst = []
            for run in range(1, max_run + 1):
                # path = "../experiments/onsga2r/{0:s}/snaps-run-{1:d}/all_pop-gen-{2:d}.out"
                path = os.path.join(root_path,
                                    *[algo_name, "{}".format(prob_name),
                                      "snaps-run-{}".format(run),
                                      "all_pop-gen-{}.out".format(gen)])
                [header, fronts] = load_data(path, nobj, ref)
                hv_lst.append(calc_hv(fronts, ref))
                gen_fe[gen] = [int(header[1])] if int(header[1]) not in gen_fe \
                        else gen_fe[gen] + int(header[1])
            a = np.array(hv_lst)
            iqr = [header[1],  # header 0 is generation, 1 is fe
                   '{:.3f}'.format(np.min(a)),
                   '{:.3f}'.format(np.percentile(a, 25)),
                   '{:.3f}'.format(np.percentile(a, 50)),
                   '{:.3f}'.format(np.percentile(a, 75)),
                   '{:.3f}'.format(np.max(a)),
                   '{:.3f}'.format(np.mean(a))]
            fd.write('\t'.join(iqr))
            fd.write('\n')
            fe = int(header[1])
            gen += 1
            if gen > max_gen:
                break
        fd.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return [file_name, gen_fe[gen - 1][0]]


def dump_hv_stats(root_path, algo_lst, prob_name, max_gen, nobj, ref):
    file_lst = []
    [dat_file, max_fe] = dump_hv_stats_gen(root_path, algo_lst[0], prob_name, max_gen, nobj, ref)
    file_lst.append((algo_lst[0], dat_file))
    for algo in algo_lst[1:]:
        [dat_file, dummy] = dump_hv_stats_feval(root_path, algo, prob_name, max_fe, nobj, ref)
        file_lst.append((algo, dat_file))
    return file_lst


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def get_onsga2_minfe(file_lst):
    fd = open(file_lst[0][1], 'r')
    return int(fd.readline().split()[0])


def save_plot(boxcmd, linecmd, file_lst):
    out_file = file_lst[0][1].split('-')[0] + '-' \
        + '-'.join([item[0] for item in file_lst]) + '-hvstat.pdf'
    print("saving {}".format(out_file))
    # command = boxcmd.format(out_file)
    if color == "mono":
        gpstr = """        \"{1:s}\"   us 1:3:2:6:5 with candlesticks \\
            fs transparent solid 0.1 ls 3 ti '{0:s}' whiskerbars 0.5, \\
            \"{1:s}\"   using 1:7:7:7:7 w candlesticks fs solid 1 ti 'mean', \\
            \"{1:s}\"   using 1:4:4:4:4 w candlesticks fs solid 1 ti 'median', \\"""\
            .format(file_lst[0][0], file_lst[0][1])
    else:
        gpstr = """        \"{1:s}\"   us 1:3:2:6:5 with candlesticks \\
            fs transparent solid 0.3 ls 1 lw 3 ti '{0:s}' whiskerbars 0.5, \\
            \"{1:s}\"   us 1:7:7:7:7 w candlesticks ls 8 lw 3 ti 'mean', \\
            \"{1:s}\"   us 1:4:4:4:4 w candlesticks ls 3 lw 3 ti 'median', \\"""\
            .format(file_lst[0][0], file_lst[0][1])
    ls = 2
    for item in file_lst[1:]:
        if color == "mono":
            gpstr += """
            \"{1:s}\"   using 1:3:2:6:5 w candlesticks \\
                    fs pattern {2:d} ti '{0:s}' whiskerbars 0.5, \\
            \"{1:s}\"   using 1:7:7:7:7 w candlesticks fs solid 1 noti, \\
            \"{1:s}\"   using 1:4:4:4:4 w candlesticks fs solid 1 noti, \\"""\
                .format(item[0], item[1], ls-1)
        else:
            gpstr += """
            \"{1:s}\"   us 1:3:2:6:5 w candlesticks \\
                    fs transparent solid 0.3 ls {2:d} lw 3 ti '{0:s}' whiskerbars 0.5, \\
            \"{1:s}\"   us 1:7:7:7:7 w candlesticks ls 8 lw 3 noti, \\
            \"{1:s}\"   us 1:4:4:4:4 w candlesticks ls 3 lw 3 noti, \\"""\
                .format(item[0], item[1], ls)
        ls += 1
    # print(command + gpstr[:-3])
    min_fe = get_onsga2_minfe(file_lst)
    print(min_fe)
    command = boxcmd + gpstr[:-3] + linecmd.format(out_file, min_fe)
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
    print("Usage: ./plothv.py [root_folder] [prob_name] [max_gen]\n")
    sys.exit()


boxcmd = """
    reset
    set terminal unknown
    set key bottom right
    set style fill noborder
    set boxwidth 0.5 relative
    load \'~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt\'
    set xlabel \'function evaluations\'
    set ylabel \'hypervolume\'
    set format x \'%.1s%c\'
    set xrange[0:]
    set yrange[0:]
    plot \\
"""


boxcmd_mono = """
    reset
    set terminal unknown
    set key bottom right
    set style fill pattern noborder
    set boxwidth 0.5 relative
    set xlabel \'function evaluations\'
    set ylabel \'hypervolume\'
    set format x \'%.1s%c\'
    set xrange[0:]
    set yrange[0:]
    plot \\
"""


linecmd = """
    set term pdf enhanced color
    set output \"{0:s}\"
    ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
    # print "ydiff: ", ydiff
    ymin = GPVAL_Y_MIN
    # print "ymin: ", ymin
    liney = ymin + (ydiff * 0.5)
    # print "liney: ", liney
    txtstart = liney + (ydiff * 0.1)
    # print "txtstart: ", txtstart
    xthresh = 50
    set arrow from 0+xthresh,liney to {1:d}-xthresh,liney heads size screen 0.005,90 lw 4 
    set label 1 "cost to find E*" rotate left at ({1:d}+xthresh)/2,txtstart
    set arrow from ({1:d}+xthresh)/2,txtstart-(ydiff * 0.01) to ({1:d}+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
    replot
"""


linecmd_mono = """
    set term pdf monochrome
    set output \"{0:s}\"
    ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
    # print "ydiff: ", ydiff
    ymin = GPVAL_Y_MIN
    # print "ymin: ", ymin
    liney = ymin + (ydiff * 0.5)
    # print "liney: ", liney
    txtstart = liney + (ydiff * 0.1)
    # print "txtstart: ", txtstart
    xthresh = 50
    set arrow from 0+xthresh,liney to {1:d}-xthresh,liney heads size screen 0.005,90 lw 4 
    set label 1 "cost to find E*" rotate left at ({1:d}+xthresh)/2,txtstart
    set arrow from ({1:d}+xthresh)/2,txtstart-(ydiff * 0.01) to ({1:d}+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
    replot
"""

# color = "mono"
color = "color"

if __name__ == '__main__':
    prob_set = {\
            'zdt1': [[150, 2], [2.0, 2.0]], 'zdt2': [[150, 2], [2.0, 2.0]], \
            'zdt3': [[150, 2], [2.0, 2.0]], 'zdt4': [[150, 2], [2.0, 2.0]], \
            'zdt6': [[150, 2], [4.0, 4.0]], 'dtlz1': [[150, 3], [10.0, 10.0, 10.0]], \
            'dtlz2': [[150, 3], [2.0, 2.0, 2.0]], 'dtlz3': [[150, 3], [15.0, 15.0, 15.0]], \
            'dtlz4': [[150, 3], [2.0, 2.0, 2.0]], 'dtlz5': [[150, 3], [2.0, 2.0, 2.0]], \
            'dtlz6': [[150, 3], [4.0, 4.0, 4.0]], 'dtlz7': [[150, 3], [10.0, 10.0, 10.0]], \
            'osy': [[150, 2], [0,80.0]], 'ctp4': [[1000, 2], [2.0, 2.0]]\
            }
    # algo_set = [['onsga2r', 'nsga2re']]
    algo_set = [['onsga2rj', 'nsga2r']]
    # algo_set = [['onsga2rwdom', 'nsga2r']]
    # algo_set = [['onsga2r', 'nsga2re'], ['onsga2r', 'nsga2r'], ['onsga2r', 'onsga2rw']]
    # algo_set = [['onsga2r', 'onsga2rdi']]
    # algo_set = [['onsga2r', 'onsga2rdr']]
    argv = sys.argv[1:]
    if len(argv) >= 2:
        for algo_pair in algo_set:
            root_path = argv[0]
            prob_name = argv[1]
            max_gen = int(argv[2]) if (len(argv) >= 3 and argv[2].isdigit()) else \
                                                prob_set[prob_name][0][0]
            nobj = prob_set[prob_name][0][1]
            ref = prob_set[prob_name][1]
            file_lst = dump_hv_stats(root_path, algo_pair, prob_name, max_gen, nobj, ref)
            if color == "mono":
                save_plot(boxcmd_mono, linecmd_mono, file_lst)
            else:
                save_plot(boxcmd, linecmd, file_lst)
            time.sleep(15)
    else:
        usage()
