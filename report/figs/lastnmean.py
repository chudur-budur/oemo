#!/usr/bin/python3

import sys
import os
import re
import numpy as np

def get_last_n_mean(file_path, col_index, last_n):
    fd = open(file_path, 'r')
    data = []
    for line in fd:
        data.append([float(val) for val in line.split()])
    mean = np.mean(np.array([val[col_index] for val in data[-1 * last_n:]]))
    return mean

if __name__ == '__main__':
    argv = sys.argv[1:]
    file_path = argv[0]
    col_index = int(argv[1])
    last_n = int(argv[2])
    mean = get_last_n_mean(file_path, col_index, last_n)
    print(mean)
