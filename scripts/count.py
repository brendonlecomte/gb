#!/usr/bin/env python3

import re
import os
import sys
from op_codes import op_code_lut


def file_handler(path):
    path = os.path.abspath(path)

    if not os.path.exists(path):
        raise FileExistsError("File not found")

    with open(path, 'r') as f:
        for line in f:
            yield line


op_state = re.compile(".*OP:(0x[0-9A-F]{2}).*")

if __name__ == '__main__':
    ref_path = sys.argv[1]

    ops = {}
    for emu in file_handler(ref_path):
        op_code = op_state.match(emu).group(1)
        try:
            ops[op_code] += 1
        except KeyError as err:
            ops[op_code] = 1

    for code in ops.keys():
        # print("{}".format(int(code,16)))
        print("{}: {}".format(op_code_lut[int(code,16)], ops[code]))
