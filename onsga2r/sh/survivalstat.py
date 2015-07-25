#!/usr/bin/python3

import sys
import os
import re
import numpy as np

def compute_mean_survival(root_path, problem):
    try:
        path = os.path.join(root_path, 'onsga2r', problem)
        regex = re.compile('all_survival_stat')
        in_files = [os.path.join(path, f) for f in os.listdir(path) if regex.match(f)]
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
        data_file = os.path.join(root_path, 'results', problem, problem + '-survival.stat')
        fd = open(data_file, 'w')
        for gen in sorted(gen_data):
            fd.write("{0:d}\t{1:0.3f}\n".format(gen, gen_data[gen]))
        fd.close()
        return [data_file, [min_key, min_val], [max_key, max_val]]
    except Exception as e:
        print(e.message, e.args)
        sys.exit()    

def save_plot(cmd, data_file, min_data, max_data):
    try:
        print(data_file, min_data, max_data)
    except Exception as e:
        print(e.message, e.args)
        sys.exit()    


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./survivalstat.py [root_folder] [prob_name]\n")
    sys.exit()

survivalcmd = """
"""

# ./survivalstat.py experiments/ zdt1 
if __name__ == '__main__':
    argv = sys.argv[1:]
    if len(argv) == 2:
        root_path = argv[0]
        problem = argv[1]
        [data_file, min_data, max_data] = compute_mean_survival(root_path, problem)
        save_plot('', data_file, min_data, max_data)
    else:
        usage()
