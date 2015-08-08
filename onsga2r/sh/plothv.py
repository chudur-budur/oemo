#!/usr/bin/python3

import sys
import os
import re
import shutil
import subprocess
import uuid
import numpy as np


def load_data(file_path, nobj):
    fronts = {}
    try:
        fd = open(file_path, 'r')
        header = [item for item in fd.readline().split() if item.isnumeric()]
        for line in fd:
            vals = line.split()
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
    if not fronts:
        sys.exit("error: file {:s} is empty".format(file_path))
    return [header, fronts]


def calc_hv(fronts):
    tmp_file = "/tmp/{:s}.out".format(str(uuid.uuid4()))
    try:
        fd = open(tmp_file, 'w')
        fd.write('#\n')
        for key in sorted(fronts):
            for lst in fronts[key]:
                fd.write("{:s}\n".format(' '.join(lst)))
            fd.write('#\n')
        fd.close()
        wfg = os.path.join(
            os.path.join('/', *os.path.abspath(__file__).split('/')[:-2]), 'wfg')
        hv_str = subprocess.check_output([wfg, tmp_file])
        hv = float(hv_str.decode("utf-8").rstrip('\n'))
        os.remove(tmp_file)
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


def dump_hv_stats_gen(root_path, algo_name, prob_name, max_gen, nobj):
    max_run = find_maxrun(os.path.join(root_path, *[algo_name, prob_name]))
    print("generating hv data for problem {0:s} over max_gen = {1:d} and max_run = {2:d} for {3:s}".
          format(prob_name, max_gen, max_run, algo_name))
    hv_dir = os.path.join(root_path, 'results', prob_name)
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(
            hv_dir, prob_name + '-' + algo_name + '-hv.stat')
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
                [header, fronts] = load_data(path, nobj)
                gen_fe[gen] = [int(header[1])] if int(header[1]) not in gen_fe \
                    else gen_fe[gen] + int(header[1])
                hv_lst.append(calc_hv(fronts))
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


def dump_hv_stats_feval(root_path, algo_name, prob_name, max_feval, nobj):
    max_run = find_maxrun(os.path.join(root_path, *[algo_name, prob_name]))
    print("generating hv data for problem {0:s} over max_feval = {1:d} and max_run = {2:d} for {3:s}".
          format(prob_name, max_feval, max_run, algo_name))
    hv_dir = os.path.join(root_path, 'results', prob_name)
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(
            hv_dir, prob_name + '-' + algo_name + '-hv.stat')
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
                [header, fronts] = load_data(path, nobj)
                gen_fe[gen] = [int(header[1])] if int(header[1]) not in gen_fe \
                    else gen_fe[gen] + int(header[1])
                hv_lst.append(calc_hv(fronts))
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
            gen += 1
            fe = int(header[1])
        fd.close()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return [file_name, gen_fe[gen - 1][0]]


def dump_hv_stats(root_path, algo_lst, prob_name, max_gen, nobj):
    file_lst = []
    [dat_file, max_fe] = dump_hv_stats_gen(
        root_path, algo_lst[0], prob_name, max_gen, nobj)
    file_lst.append((algo_lst[0], dat_file))
    for algo in algo_lst[1:]:
        [dat_file, dummy] = dump_hv_stats_feval(
            root_path, algo, prob_name, max_fe, nobj)
        file_lst.append((algo, dat_file))
    return file_lst


def parse_gpcmd(gpcmd):
    lines = [line + '\n' for line in
             list(filter((lambda line: len(line) != 0 or line != ''),
                         [line.strip() for line in gpcmd.splitlines()])) if line.split()[0] != '#']
    return lines


def save_plot(cmd, file_lst):
    out_file = file_lst[0][1].split('-')[0] + '-' \
        + '-'.join([item[0] for item in file_lst]) + '-hvstat.pdf'
    print("saving {}".format(out_file))
    command = cmd.format(out_file)
    gpstr = """        \"{1:s}\"   using 1:3:2:6:5 with candlesticks \\
        fs transparent solid 0.3 ls 1 lw 3 title '{0:s}' whiskerbars 0.5, \\
        \"{1:s}\"   using 1:7:7:7:7 with candlesticks ls 3 lw 3 title 'mean', \\
        \"{1:s}\"   using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \\"""\
        .format(file_lst[0][0], file_lst[0][1])
    ls = 2
    for item in file_lst[1:]:
        gpstr += """
        \"{1:s}\"   using 1:3:2:6:5 with candlesticks \\
                fs transparent solid 0.3 ls {2:d} lw 3 title '{0:s}' whiskerbars 0.5, \\
        \"{1:s}\"   using 1:7:7:7:7 with candlesticks ls 3 lw 3 noti, \\
        \"{1:s}\"   using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \\"""\
            .format(item[0], item[1], ls)
        ls += 1
    # print(command + gpstr[:-3])
    lines = parse_gpcmd(command + gpstr[:-3])
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
    set term pdf enhanced color
    # set term pdf monochrome
    set style fill noborder
    set boxwidth 0.5 relative
    set output \"{0:s}\"
    load \'~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt\'
    # set xrange[0:]
    set xlabel \'function evaluations\'
    set ylabel \'hypervolume\'
    set format x \'%.1s%c\'
    plot \\
"""
# fs transparent solid 0.3 lt 3 lw 3 title 'nsga2' whiskerbars 0.5, \\
# \"{1:s}\"   using 1:7:7:7:7 with candlesticks lt 4 lw 3 title 'mean', \\
# \"{1:s}\"   using 1:4:4:4:4 with candlesticks lt -1 lw 3 title 'median', \\
# fs transparent solid 0.5 lt 2 lw 3 title 'onsga2' whiskerbars 0.5, \\
# \"{2:s}\"   using 1:7:7:7:7 with candlesticks lt 4 lw 3 noti, \\
# \"{2:s}\"   using 1:4:4:4:4 with candlesticks lt -1 lw 3 noti


if __name__ == '__main__':
    # prob_set = {'zdt1': 13, 'zdt2': 35, 'zdt3': 20, 'zdt4': 20, 'zdt6': 35}
    prob_set = {'zdt1': [15, 2]}
    algo_set = ['onsga2r', 'nsga2r']
    argv = sys.argv[1:]
    if len(argv) >= 2:
        root_path = argv[0]
        prob_name = argv[1]
        for prob_name in prob_set:
            max_gen = int(argv[2]) if (
                len(argv) >= 3 and argv[2].isdigit()) else prob_set[prob_name][0]
            nobj = prob_set[prob_name][1]
            file_lst = dump_hv_stats(
                root_path, algo_set, prob_name, max_gen, nobj)
            save_plot(boxcmd, file_lst)
    else:
        usage()
