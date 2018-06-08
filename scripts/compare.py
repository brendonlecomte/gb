#!/usr/bin/env python3
import re
import os
import sys
from op_codes import op_code_lut

comp = {'std': lambda a,b: a == b,
        'pc': lambda a,b: a.PC == b.PC,
        'step': lambda a,b: False}

def file_handler(path):
    path = os.path.abspath(path)

    if not os.path.exists(path):
        raise FileExistsError("File not found")

    with open(path, 'r') as f:
        for line in f:
            yield line

def compare(ref, gb, mode='std'):
    return comp[mode](ref, gb)


class gameboy:
    registers_state = re.compile(".*AF:(0x[0-9A-F]{4}).+BC:(0x[0-9A-F]{4}).+DE:(0x[0-9A-F]{4}).+HL:(0x[0-9A-F]{4})")
    cpu_state = re.compile("PC:(0x[0-9A-F]{4}).+OP:(0x[0-9A-F]{2}).+SP:(0x[0-9A-F]{4})")
    interrupt_state = re.compile(".*IME:(0x[0-9]+) IF:(0x[0-9A-F]+) IE:(0x[0-9A-F]+)")

    def __init__(self, iter):
        self.iter = iter
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
        self.parse_debug()


    def parse_debug(self):
        dbg = next(self.iter)
        # print(dbg)
        rs = self.registers_state.match(dbg)
        cs = self.cpu_state.match(dbg)
        ins = self.interrupt_state.match(dbg)

        if(ins):
            self.IME = int(ins.group(1), 16)
            self.IF = int(ins.group(2), 16)
            self.IE = int(ins.group(3), 16)

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
        return "OP:{:#x} {} \nPC:{:#x} SP:{:#x}\nAF:{:#x} BC:{:#x} DE:{:#x} HL:{:#x}\nIME:{:#x}  IF:{:#x}  IE:{:#x}".format(self.OP,
                                                                                            op_code_lut[self.OP],
                                                                                            self.PC,
                                                                                            self.SP,
                                                                                            self.AF,
                                                                                            self.BC,
                                                                                            self.DE,
                                                                                            self.HL,
                                                                                            self.IME,
                                                                                            self.IF,
                                                                                            self.IE)

    def __eq__(self , other):
        mask = ['iter','IME','IF','IE']
        return {k: v for k,v in self.__dict__.items() if k not in mask} == \
                {k: v for k,v in other.__dict__.items() if k not in mask}



mode_change = re.compile("m:(\w*)")
goto = re.compile("(\w)>(0x[0-9A-F]{4})")
ask = re.compile("(\w)?([A-F]{2})")

def parse_ask_command(x):
    y = ask.match(x)
    if y:
        return ask.group(1), ask.group(2)
    return None, None

def parse_mode_command(x):
    mode = mode_change.match(x)
    if(mode):
        return mode.group(1)
    return None

def parse_goto_command(x):
    mode = goto.match(x)
    if(mode):
        return mode.group(1), int(mode.group(2), 16)
    return None, None

if __name__ == '__main__':
    ref_path = sys.argv[1]
    emu_path = sys.argv[2]
    ref_iter = file_handler(ref_path)
    emu_iter = file_handler(emu_path)

    my_emu = gameboy(emu_iter)
    ref_emu = gameboy(ref_iter)


    # while(True):


        # if(not compare(ref_emu, my_emu)):
    print("Emu:"),
    print(my_emu)
    print("REF:"),
    print(ref_emu)

    compare_mode = 'std'

    while(True):
        my_emu.parse_debug()
        ref_emu.parse_debug()
        print("Emu:"),
        print(my_emu)
        print("REF:"),
        print(ref_emu)
        print("-----------")
        if(not compare(ref_emu, my_emu, mode=compare_mode)):
            inp = input('::')
            m = parse_mode_command(inp)
            if m:
                compare_mode = m.lower()
                continue
            a, pc = parse_goto_command(inp)
            if a:
                a = a.lower()
                if a == 'e':
                    while not my_emu.PC == pc:
                        my_emu.parse_debug()
                if a == 'r':
                    while not ref_emu.PC == pc:
                        ref_emu.parse_debug()
