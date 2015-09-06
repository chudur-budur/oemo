#!/usr/bin/python3

import sys
import os
import re
import numpy as np

def load_data(file_path):
    data = []
    try:
        fd = open(file_path, 'r')
        for line in fd:
            data.append([float(val) for val in line.split()])
    except Exception as e:
        print(e.message, e.args)
        sys.exit()
    return data

def compute_speedup(root_path, problem, algorithms, tol):
    path1 = os.path.join(root_path, 'results', problem, problem + '-' + algorithms[0] + '-hv.stat')
    path2 = os.path.join(root_path, 'results', problem, problem + '-' + algorithms[1] + '-hv.stat')
    data1 = load_data(path1)
    data2 = load_data(path2)
    # print("data1: {}\n".format(data1))
    # print("data2: {}\n".format(data2))
    # print("len(data1): {0:d}\tlen(data2): {1:d}".format(len(data1), len(data2)))
    max1 = max([val[-1] for val in data1])
    max2 = max([val[-1] for val in data2])
    # print("max1: {0:f}\tmax2: {1:f}".format(max1, max2))
    if max1 > max2:
        max1 = max1 * tol
        fe2 = int(next((val[0] for val in data2 if val[-1] > max1), data2[-1][0]))
        fe1 = int(next((val[0] for val in data1 if val[-1] > max1), data1[-1][0]))
    else:
        max2 = max2 * tol
        fe1 = int(next((val[0] for val in data1 if val[-1] > max2), data1[-1][0]))
        fe2 = int(next((val[0] for val in data2 if val[-1] > max2), data2[-1][0]))
    speedup = fe2/fe1 if fe2 > fe1 else 0
    return [[algorithms[0], fe1], [algorithms[1], fe2], speedup]

def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./speedup.py [root_folder] [prob_name]\n")
    sys.exit()

if __name__ == '__main__':
    algos = ['onsga2r', 'nsga2r']
    argv = sys.argv[1:]
    if len(argv) >= 2:
        root_path = argv[0]
        problem = argv[1]
        tol = 0.9 if len(argv) == 2 else (float(argv[2]) \
                if float(argv[2]) < 1.0 else (float(argv[2])/100.0))
        result = compute_speedup(root_path, problem, algos, tol)
        print("{5:s} -- {0:s}: {1:d}\t{2:s}: {3:d}\tspeed-up: {4:.2f}"\
                .format(result[0][0], result[0][1], \
                        result[1][0], result[1][1], \
                        result[2], problem))
    else:
        usage()
