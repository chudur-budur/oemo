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

def load_data():
    fd = open("W3D_300.dat", 'r')
    data = []
    for line in fd:
        data.append([float(v) for v in line.split()])
    fd.close()
    return data

def process(data_):
    first_three = data_[0:3]
    data = data_[3:]
    data = sorted(data, key = lambda x: x[0])
    for i in range(0, len(data)):
        if ((2 * i) + 1) < len(data):
            data.pop((2 * i) + 1)
    return first_three + data[1:]

def save(data):
    fd = open("W3D_200.dat", 'w')
    for d in data:
        fd.write(' '.join([str(v) for v in d]))
        fd.write('\n')
    fd.close()

if __name__ == '__main__':
    rdata = load_data()
    data = process(rdata)
    save(data)
