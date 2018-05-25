#!/usr/bin/env python3
import re
import os
import sys

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

op_code_lut = [
'NOP','LD_BC_d16','LD_mBC_A','INC_BC','INC_B','DEC_B','LD_B_d8','RLCA','LD_a16_SP',
'ADD_HL_BC','LD_A_BC','DEC_BC','INC_C','DEC_C','LD_C_d8','RRCA',
'STOP','LD_DE_d16','LD_DE_A','INC_DE','INC_D','DEC_D','LD_D_d8','RLA','JR_r8',
'ADD_HL_DE','LD_A_DE','DEC_DE','INC_E','DEC_E','LD_E_d8','RRA',
'JR_NZ_r8','LD_HL_d16','LD_HLp_A','INC_HL','INC_H','DEC_H','LD_H_d8','DAA','JR_Z_r8',
'ADD_HL_HL','LD_A_HLp','DEC_HL','INC_L','DEC_L','LD_L_d8','CPL',
'JR_NC_r8','LD_SP_d16','LD_HLs_A','INC_SP','INC_aHL','DEC_aHL','LD_mHL_d8','SCF',
'JR_C_r8','ADD_HL_SP','LD_A_HLs','DEC_SP','INC_A','DEC_A','LD_A_d8','CCF',
'LD_B_B','LD_B_C','LD_B_D','LD_B_E','LD_B_H','LD_B_L','LD_B_HLm','LD_B_A',
'LD_C_B','LD_C_C','LD_C_D','LD_C_E','LD_C_H','LD_C_L','LD_C_HLm','LD_C_A',
'LD_D_B','LD_D_C','LD_D_D','LD_D_E','LD_D_H','LD_D_L','LD_D_HLm','LD_D_A',
'LD_E_B','LD_E_C','LD_E_D','LD_E_E','LD_E_H','LD_E_L','LD_E_HLm','LD_E_A',
'LD_H_B','LD_H_C','LD_H_D','LD_H_E','LD_H_H','LD_H_L','LD_H_HLm','LD_H_A',
'LD_L_B','LD_L_C','LD_L_D','LD_L_E','LD_L_H','LD_L_L','LD_L_HLm','LD_L_A',
'LD_HLm_B','LD_HLm_C','LD_HLm_D','LD_HLm_E','LD_HLm_H','LD_HLm_L','HALT',
'LD_L_A','LD_A_B','LD_A_C','LD_A_D','LD_A_E','LD_A_H','LD_A_L','LD_A_HLm','LD_A_A',
'ADD_A_B','ADD_A_C','ADD_A_D','ADD_A_E','ADD_A_H','ADD_A_L','ADD_A_HLm','ADD_A_A',
'ADC_A_B','ADC_A_C','ADC_A_D','ADC_A_E','ADC_A_H','ADC_A_L','ADC_A_HLm','ADC_A_A',
'SUB_B','SUB_C','SUB_D','SUB_E','SUB_H','SUB_L','SUB_HLm','SUB_A','SBC_A_B','SBC_A_C',
'SBC_A_D','SBC_A_E','SBC_A_H','SBC_A_L','SBC_A_HLm','SBC_A_A',
'AND_B','AND_C','AND_D','AND_E','AND_H','AND_L','AND_HLm','AND_A','XOR_B','XOR_C',
'XOR_D','XOR_E','XOR_H','XOR_L','XOR_HLm','XOR_A',
'OR_B','OR_C','OR_D','OR_E','OR_H','OR_L','OR_HLm','OR_A','CP_B','CP_C','CP_D','CP_E',
'CP_H','CP_L','CP_HLm','CP_A',
'RET_NZ','POP_BC','JP_NZ_a16','JP_a16','CALL_NZ_a16','PUSH_BC','ADD_A_d8','RST_00H',
'RET_Z','RET','JP_Z_a16','PREFIX_CB','CALL_Z_a16','CALL_a16','ADC_A_d8','RST_08H',
'RET_NC','POP_DE','JP_NC_a16','no_op_code','CALL_NC_a16','PUSH_DE','SUB_d8','RST_10H',
'RET_C','RETI','JP_C_a16','no_op_code','CALL_C_a16','no_op_code','SBC_A_d8','RST_18H',
'LDH_a8_A','POP_HL','LD_Cm_A','no_op_code','no_op_code','PUSH_HL','AND_d8','RST_20H',
'ADD_SP_r8','JP_HLm','LD_a16_A','no_op_code','no_op_code','no_op_code','XOR_d8','RST_28H',
'LDH_A_a8','POP_AF','LD_A_Cm','DI','no_op_code','PUSH_AF','OR_d8','RST_30H','LD_HL_SPr8',
'LD_SP_HL','LD_A_a16','EI','no_op_code','no_op_code','CP_d8','RST_38H']

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
