#!/usr/bin/env python3


default_file = """#include "physical_cart.h"

uint8_t game_cart[MAX_CART_SIZE] =
/*START OF CART*/
"""


def bin_to_array(path):
    with open(path, "rb") as f:
        data = bytearray(f.read())  # get the file as a byte array
    return data


def data_to_c_array_format(data):
    arr = "{"
    for byte in data:
        arr += "0x{:02X}".format(byte)
        arr += ","
    arr = arr[:-1]  # remove the last ,
    arr += "};"
    return arr


def populate_c_file(c_file_path, arr_str):
    with open(c_file_path, "w") as f:
        f.write(default_file)
        f.write(arr_str)



if __name__ == "__main__":
    import sys
    c_path = "../src/physical_cart.c"
    bin = bin_to_array(sys.argv[1])
    arr = data_to_c_array_format(bin)
    populate_c_file(c_path, arr)
