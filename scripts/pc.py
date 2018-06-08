#!/usr/bin/env python3

import re
import os
import sys
from collections import OrderedDict


def file_handler(path):
    path = os.path.abspath(path)

    with open(path, 'r') as f:
        for line in f:
            yield line


pc_state = re.compile(".*PC:(0x[0-9A-F]{4}).*")

if __name__ == '__main__':
    ref_path = sys.argv[1]

    pc_count = OrderedDict()

    for emu in file_handler(ref_path):
        pc = pc_state.match(emu).group(1)
        try:
            pc_count[pc] += 1
        except KeyError as err:
            pc_count[pc] = 1

    for c in pc_count.keys():
        # print("{}".format(int(code,16)))
        print("{}: {}".format(c, pc_count[c]))
