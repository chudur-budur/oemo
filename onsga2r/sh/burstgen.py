#!/usr/bin/python3

import os
import sys


def burst_file(path_lst, file_prefix, run):
    root_path = ""
    root_path = os.path.join(root_path, *path_lst)
    file_name = file_prefix + run + '.out'
    in_file = os.path.join(root_path, file_name)
    if os.path.exists(in_file):
        try:
            out_dir = os.path.join(root_path, "snaps-run-" + run)
            print(
                "bursting \'{0:s}\' into \'{1:s}\'.".format(in_file, out_dir))
            if not os.path.exists(out_dir):
                os.makedirs(out_dir)
            in_fd = open(in_file, 'r')
            cur_gen = 0
            out_fd = None
            for line in in_fd:
                tokens = line.split()
                if tokens[0] == '#' and tokens[1] == 'gen':
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

# Usage:    ./burstgen [root_folder] [prob_name] [run]
#           ./burstgen experiments/ zdt1 [1]
if __name__ == '__main__':
    argv = sys.argv[1:]
    algorithms = ['onsga2r', 'nsga2re', 'nsga2r', 'onsga2rm']
    file_prefixes = ['all_pop-', 'all_source-',
                     'all_opposite-', 'all_extreme-', 'all_survived-']
    if len(argv) >= 2:
        run = '1' if len(argv) == 2 else (
            argv[2] if argv[2].isdigit() else '1')
        for file_prefix in file_prefixes:
            for algo in algorithms:
                # burst_file([root_folder, algo_name, prob_name], file_prefix, run)
                burst_file([argv[0], algo, argv[1]], file_prefix, run)
    else:
        usage()
