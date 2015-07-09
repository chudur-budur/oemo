#!/usr/bin/python3

import os
import sys
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
        header = [item for item in fd.readline().split() if item.isnumeric()];
        for line in fd:
            vals = line.split()
            if vals[-3] in fronts:
                if not (vals[-3] == '1' and float(vals[-2]) == 1.00e+14):
                    fronts[vals[-3]] += [vals[0:nobj]] 
            else:
                if not (vals[-3] == '1' and float(vals[-2]) == 1.00e+14):
                    fronts[vals[-3]] = [vals[0:nobj]]
        fd.close()
    except BaseException as e:
        sys.exit(str(e))
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
    except BaseException as e:
        sys.exit(str(e))
    return hv

def dump_hv_stats(path, prob_name, algo_name, max_gen, max_run, nobj):
    print("generating hv data for problem {0:s} over max_gen = {1:d} and max_run = {2:d} for {3:s}".\
            format(prob_name, max_gen, max_run, algo_name))
    hv_dir = "../experiments/hv-plots"
    try:
        if(not os.path.exists(hv_dir)):
            os.makedirs(hv_dir)
        file_name = os.path.join(hv_dir, prob_name + '-' + algo_name + '.stat')
        fd = open(file_name, 'w')
        for gen in range(1, max_gen + 1):
            hv_lst = []
            for run in range(1, max_run + 1):
                [header, fronts] = load_data(path.format(prob_name, run, gen), nobj)
                hv_lst.append(calc_hv(fronts))
            a = np.array(hv_lst)
            iqr = [header[0], \
                    '{:.3f}'.format(np.min(a)), \
                    '{:.3f}'.format(np.percentile(a, 25)), \
                    '{:.3f}'.format(np.percentile(a, 50)), \
                    '{:.3f}'.format(np.percentile(a, 75)), \
                    '{:.3f}'.format(np.max(a)), \
                    '{:.3f}'.format(np.mean(a))]
            fd.write('\t'.join(iqr))
            fd.write('\n')
        fd.close()
    except BaseException as e:
        sys.exit(str(e))
    return file_name

def plot_box(file_onsga2, file_nsga2):
    print("saving plot")
    pdf_file = replace_file_ext(file_onsga2, 'pdf')
    try:
        proc = subprocess.Popen(['gnuplot', '-p'], shell = True, stdin = subprocess.PIPE)
        proc.stdin.write(bytes("set term pdf enhanced color\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("set boxwidth 0.5 relative\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("set output \"{:s}\"\n".format(pdf_file), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("plot \"{:s}\" using 1:3:2:6:5 with candlesticks lt 3 lw 2 title 'Quartiles-nsga2' whiskerbars 0.5, \\\n".format(file_nsga2), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("\'\'                 using 1:4:4:4:4 with candlesticks lt -1 lw 2 title 'Median-nsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("\'\'                 using 1:7:7:7:7 with candlesticks lt 4 lw 2 title 'Mean-nsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("\"{:s}\" using 1:3:2:6:5 with candlesticks lt 2 lw 2 title 'Quartiles-onsga2' whiskerbars 0.5, \\\n".format(file_onsga2), "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("\'\'                 using 1:4:4:4:4 with candlesticks lt -1 lw 2 title 'Median-onsga2', \\\n", "ascii"))
        proc.stdin.flush()
        proc.stdin.write(bytes("\'\'                 using 1:7:7:7:7 with candlesticks lt 4 lw 2 title 'Mean-onsga2', \\\n", "ascii"))
        proc.stdin.flush()
    except BaseException as e:
        sys.exit(str(e))
    

if __name__ == '__main__':
    path1 = "../experiments/onsga2r/{0:s}/pfsnaps-run-{1:d}/all_pop-{1:d}-gen-{2:d}.out"
    path2 = "../experiments/nsga2r/{0:s}/pfsnaps-run-{1:d}/all_pop-{1:d}-gen-{2:d}.out"
    # zdt_set = [['zdt1', 13], ['zdt2', 35], ['zdt3', 20], ['zdt4', 20], ['zdt6', 35]]
    zdt_set = [['zdt6', 35]]
    dtlz_set = [['dtlz2', 15]]
    max_run = 11
    
    for prob in zdt_set:
        file1 = dump_hv_stats(path1, prob[0], 'onsga2', prob[1], max_run, 2)
        file2 = dump_hv_stats(path2, prob[0], 'nsga2', prob[1], max_run, 2)
        plot_box(file1, file2)

    # for prob in dtlz_set:
    #     file1 = dump_hv_stats(path1, prob[0], 'onsga2', prob[1], max_run, 3)
    #     file2 = dump_hv_stats(path2, prob[0], 'nsga2', prob[1], max_run, 3)
    #     plot_box(file1, file2)
