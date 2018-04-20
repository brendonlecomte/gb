#!/usr/bin/env python3
import re
import os
import sys

def file_handler(path):
    path = os.path.abspath(path)

    if not os.path.exists(path):
        raise FileExistsError("File not found")

    with open(path, 'r') as f:
        for line in f:
            yield line

def compare(ref, gb):
    return ref == gb

class gameboy:
    registers_state = re.compile(".*AF:(0x[0-9A-F]{4}).+BC:(0x[0-9A-F]{4}).+DE:(0x[0-9A-F]{4}).+HL:(0x[0-9A-F]{4})")
    cpu_state = re.compile("PC:(0x[0-9A-F]{4}).+OP:(0x[0-9A-F]{2}).+SP:(0x[0-9A-F]{4})")
    interrupt_state = re.compile(".*IME:(0x[0-9]+) IF:(0x[0-9A-F]+) IE:(0x[0-9A-F]+)")

    def __init__(self):
        self.state = {'AF': 0,
                    'BC': 0,
                    'DE':0,
                    'HL':0,
                    'PC':0,
                    'SP':0,
                    'OP':0,
                    'IME':0,
                    'IE':0,
                    'IF':0}

        self.AF = 0
        self.BC = 0
        self.DE = 0
        self.HL = 0

        self.PC = 0
        self.SP = 0
        self.OP = 0

        self.IME = 0
        self.IE  = 0
        self.IF  = 0


    def parse_debug(self, dbg):
        rs = self.registers_state.match(dbg)
        cs = self.cpu_state.match(dbg)

        if(rs):
            self.AF = int(rs.group(1), 16)
            self.BC = int(rs.group(2), 16)
            self.DE = int(rs.group(3), 16)
            self.HL = int(rs.group(4), 16)

        if(cs):
            self.PC = int(cs.group(1), 16)
            self.OP = int(cs.group(2), 16)
            self.SP = int(cs.group(3), 16)
        return cs and rs

    def __repr__(self):
        return "OP:{:#x}\nPC:{:#x} SP:{:#x}\nAF:{:#x} BC:{:#x} DE:{:#x} HL:{:#x}\n".format(self.OP,
                                                                                            self.PC,
                                                                                            self.SP,
                                                                                            self.AF,
                                                                                            self.BC,
                                                                                            self.DE,
                                                                                            self.HL)


    def mask(self):
        
        return self


    def __eq__(self , other):
        if isinstance(self, other.__class__):
            return self.mask().__dict__ == other.mask().__dict__
        return False

if __name__ == '__main__':
    ref_path = sys.argv[1]
    emu_path = sys.argv[2]
    my_emu = gameboy()
    ref_emu = gameboy()
    # gb.parse_debug("PC:0x073F OP:0x03 AF:0x2750 BC:0xFB34 DE:0xFF56 HL:0x0B8F SP:0xDFF3 IME:0x0 IF:0x00 IE:0x00")

    # while(compare(ref.parse_debug(file_handler(ref_path)), gb.parse_debug(gb_path))):
    #     input("matching gb states")

    for ref, emu in zip(file_handler(ref_path), file_handler(emu_path)):
        ref_emu.parse_debug(ref)
        my_emu.parse_debug(emu)
        if(not compare(ref_emu, my_emu)):
            print("Emu:"),
            print(my_emu)
            print("REF:"),
            print(ref_emu)
            if(input(":") == "x"):
                break
    # print("Emu:")
    # print(gb)
    #
    # print("Ref")
    # print(ref)
    # print("test")
