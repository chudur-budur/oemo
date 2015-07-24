#!/usr/bin/python3

import os
import sys
import re
import shutil
import subprocess
import uuid
import numpy as np


def replace_file_ext(file_path, ext):
    path = os.path.split(file_path)
    return os.path.join(path[0], path[1].split('.')[0] + '.' + ext)


def load_data(file_path, nobj):
    fronts = {}
    try:
        fd = open(file_path, 'r')
        header = [item for item in fd.readline().split() if item.isnumeric()]
        for line in fd:
            vals = line.split()
            if vals[-3] in fronts:
                if not (vals[-3] == '1' and float(vals[-2]) == 1.00e+14):
                    fronts[vals[-3]] += [vals[0:nobj]]
            else:
                if not (vals[-3] == '1' and float(vals[-2]) == 1.00e+14):
                    fronts[vals[-3]] = [vals[0:nobj]]
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
        hv_str = subprocess.check_output(['../wfg', tmp_file])
        hv = float(hv_str.decode("utf-8").rstrip('\n'))
        os.remove(tmp_file)
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return hv


def find_maxrun(path):
    try:
        regex = re.compile('snaps-run-*')
        return len([d.split('-')[-1] for d in os.listdir(path) if regex.match(d)])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def dump_hv_stats(root_path, algo_name, prob_name, max_gen, nobj):
    max_run = find_maxrun(os.path.join(root_path, *[algo_name, prob_name]))
    print("generating hv data for problem {0:s} over max_gen = {1:d} and max_run = {2:d} for {3:s}".
          format(prob_name, max_gen, max_run, algo_name))
    hv_dir = os.path.join(root_path, 'results')
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(hv_dir, prob_name + '-' + algo_name + '.stat')
        fd = open(file_name, 'w')
        for gen in range(1, max_gen + 1):
            hv_lst = []
            for run in range(1, max_run + 1):
                # path = "../experiments/onsga2r/{0:s}/snaps-run-{1:d}/all_pop-gen-{2:d}.out"
                [header, fronts] = load_data(
                    os.path.join(root_path, *[algo_name, "{}".format(prob_name),
                                              "snaps-run-{}".format(run), "all_pop-gen-{}.out".format(gen)]), nobj)
                hv_lst.append(calc_hv(fronts))
            a = np.array(hv_lst)
            iqr = [header[0],
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
    return file_name


def plot_box(file_onsga2, file_nsga2):
    print("saving plot")
    pdf_file = replace_file_ext(file_onsga2, 'pdf')
    try:
        proc = subprocess.Popen(
            ['gnuplot', '-p'], shell=True, stdin=subprocess.PIPE)
        proc.stdin.write(bytes("set term pdf enhanced color\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("set boxwidth 0.5 relative\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(
            bytes("set output \"{:s}\"\n".format(pdf_file), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "plot \"{:s}\" using 1:3:2:6:5 with candlesticks lt 3 lw 2 title 'Quartiles-nsga2' whiskerbars 0.5, \\\n".format(file_nsga2), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "\'\'                 using 1:4:4:4:4 with candlesticks lt -1 lw 2 title 'Median-nsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "\'\'                 using 1:7:7:7:7 with candlesticks lt 4 lw 2 title 'Mean-nsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "\"{:s}\" using 1:3:2:6:5 with candlesticks lt 2 lw 2 title 'Quartiles-onsga2' whiskerbars 0.5, \\\n".format(file_onsga2), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "\'\'                 using 1:4:4:4:4 with candlesticks lt -1 lw 2 title 'Median-onsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes(
            "\'\'                 using 1:7:7:7:7 with candlesticks lt 4 lw 2 title 'Mean-onsga2', \\\n", "ascii"))
        proc.stdin.flush()
    except Exception as e:
        print(e.message, e.args)
        sys.exit()


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./plothv.py [root_folder] [prob_name] [max_gen]\n")
    sys.exit()


# ./plothv.py experiments/ zdt1 [13] [blah] [blah]
if __name__ == '__main__':
    # prob_set = {'zdt1': 13, 'zdt2': 35, 'zdt3': 20, 'zdt4': 20, 'zdt6': 35}
    prob_set = {'zdt1': 14}
    argv = sys.argv[1:]
    if len(argv) >= 2:
        root_path = argv[0]
        prob_name = argv[1]
        for key in prob_set:
            max_gen = int(argv[2]) if (
                len(argv) >= 3 and argv[2].isdigit()) else prob_set[key]
            file1 = dump_hv_stats(root_path, 'onsga2r', key, max_gen, 2)
            file2 = dump_hv_stats(root_path, 'nsga2r', key, max_gen, 2)
            plot_box(file1, file2)
    else:
        usage()
