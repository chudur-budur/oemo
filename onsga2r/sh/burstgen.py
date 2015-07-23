#!/usr/bin/python3

import os
import sys

file_prefixes = ['all_pop-', 'all_source-',
                 'all_opposite-', 'all_extreme-', 'all_survived-']
algorithms = ['onsga2r', 'nsga2r']


def burst_file(root_folder, algo_name, file_prefix, problem_name, run):
    root_path = ""
    if root_folder != "":
        root_path = os.path.join(root_path, root_folder)
    if algo_name != "":
        root_path = os.path.join(root_path, algo_name)
    if problem_name != "":
        root_path = os.path.join(root_path, problem_name)
    file_name = file_prefix + run + '.out'
    in_file = os.path.join(root_path, file_name)
    if os.path.exists(in_file):
        try:
            out_dir = os.path.join(root_path, "snaps-run-" + run)
            if not os.path.exists(out_dir):
                os.makedirs(out_dir)
            in_fd = open(in_file, 'r')
            line = in_fd.readline()  # header
            line = in_fd.readline()  # header
            cur_gen = 0
            out_fd = None
            for line in in_fd:
                tokens = line.split()
                if tokens[1] == 'gen':
                    # print(line)
                    if int(tokens[3]) > cur_gen:
                        if out_fd is not None:
                            out_fd.close()
                        out_file = os.path.join(out_dir,
                                                file_prefix + "gen-" + tokens[3] + ".out")
                        out_fd = open(out_file, 'w')
                        cur_gen = int(tokens[3])
                if out_fd is not None:
                    out_fd.write(line)
        except Exception as e:
            print(e.message, e.args)
            sys.exit()
    else:
        print("\'{0:s}\' does not exist, hence skipping.".format(in_file))


def usage():
    print("error: some of the parameters are missing, hence exiting ...")
    print("Usage: ./burstgen.py [root_folder] [prob_name] [run]\n")
    sys.exit()

if __name__ == '__main__':
    if len(sys.argv[1:]) > 2:
        if len(sys.argv[1:]) == 2:
            run = 1
        else:
            run = sys.argv[3]
        for fp in file_prefixes:
            for algo in algorithms:
                # burst_file(root_folder, algo_name, fp, prob_name, run)
                burst_file(sys.argv[1], algo, fp, sys.argv[2], run)
    else:
        usage()
