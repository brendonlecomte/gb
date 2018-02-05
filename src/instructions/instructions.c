#include "instructions.h"
#include "memory.h"


uint8_t add_4bit(uint8_t a, uint8_t b, uint8_t *c)
{
    uint8_t res = a + b; // + (*c);
    *c = (res&0x10);
    printf("%d\n",res);
    return res;
}

uint8_t sub_4bit(uint8_t a, uint8_t b, uint8_t *c)
{
    return add_4bit(a, ~b, c);
}

uint8_t add_8bit(uint8_t a, uint8_t b, uint8_t *c, uint8_t *hc)
{
    printf("%d + %d = ?\n",a, b);
    uint8_t low = add_4bit(a, b, c);
    printf("%d + %d = ?\n",a, low);
    *hc = *c; //store hc
    uint8_t high = add_4bit(a>>4, b>>4, hc);
    uint8_t res =  high<<4 + low;
    return res;
}

/*
ADC A,n  - Add n + Carry flag to A.

        n = A,B,C,D,E,H,L,(HL),#

        Flags affected:
        Z - Set if result is zero.
        N - Reset.
        H - Set if carry from bit 3.
        C - Set if carry from bit 7
*/
void instr_adc(uint8_t* A, uint8_t n) {
  uint16_t temp = *A + n + CPU_check_flag(CARRY_FLAG);
  uint8_t hc_temp = (*A & 0x0F) + (n & 0x0F) + CPU_check_flag(CARRY_FLAG);
  *A = (uint8_t)temp & 0xFF;
  if (temp & 0x100)
    CPU_set_flag(CARRY_FLAG);
  if (hc_temp & 0x10)
    CPU_set_flag(HALF_CARRY_FLAG);
  if (temp == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
}

/*
ADD A,n - Add n to A.
        n = A,B,C,D,E,H,L,(HL),#
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Set if carry from bit 3.
                C - Set if carry from bit 7.
*/
void instr_add(uint8_t *A, uint8_t n) {
    uint16_t temp = *A;
    temp += n;
    uint8_t hc_temp = (*A & 0xF) + (n & 0xF);
    *A = (uint8_t)temp;
    if (hc_temp & 0x10){
        CPU_set_flag(HALF_CARRY_FLAG);
    }
    if (temp & 0x100){
        CPU_set_flag(CARRY_FLAG);
    }
    if (temp == 0){
        CPU_set_flag(ZERO_FLAG);
    }
    CPU_clear_flag(SUBTRACT_FLAG);
}

/*
ADD HL,n  - Add n to HL.
        n = BC,DE,HL

        Flags affected:
                Z - Not affected
                N - Reset.
                H - Set if carry from bit 11.
                C - Set if carry from bit 15.
*/
void instr_add_HL(uint16_t *hl, uint16_t n) {
    uint32_t temp = *hl + n;
    uint16_t hc_temp = (*hl & 0x0FFF) + (n & 0x0FFF);
    *hl = temp&0xFFFF;
    if (temp & 0x10000) {
        CPU_set_flag(CARRY_FLAG);
    }
    if (hc_temp & 0x1000) {
        CPU_set_flag(HALF_CARRY_FLAG);
    }
    CPU_clear_flag(SUBTRACT_FLAG);
}

/*
ADD SP,n - Add n to Stack Pointer (SP).

        n = one byte signed immediate value

        Flags affected:
                Z - Reset
                N - Reset.
                H - Set or reset according to operation.
                C - Set or reset according to operation.
*/
void instr_add_SP(uint16_t *sp, uint8_t n) {
  uint32_t temp = *sp + n;
  CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);

  uint16_t hc_temp = (*sp & 0x0FFF) + (n);
  *sp = temp;
  if (temp & 0x10000)
    CPU_set_flag(CARRY_FLAG);
  else
    CPU_clear_flag(CARRY_FLAG);

  if (hc_temp & 0x1000)
    CPU_set_flag(HALF_CARRY_FLAG);
  else
    CPU_clear_flag(HALF_CARRY_FLAG);
}

/*
AND n  - Logically AND n with A, result in A.

        n = A,B,C,D,E,H,L,(HL),#

        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Set.
                C - Reset.
*/
void instr_and(uint8_t *A, uint8_t n) {
  *A = *A & n;
  if (*A == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_set_flag(HALF_CARRY_FLAG);
  CPU_clear_flag(CARRY_FLAG);
}

/*
BIT b,r  - Test bit b in register r.

        b = 0-7, r = A,B,C,D,E,H,L,(HL)

        Flags affected:
                Z - Set if bit b of register r is 0.
                N - Reset.
                H - Set.
                C - Not affected.
*/
void instr_bit(uint8_t b, uint8_t *r) {
  if (((0x01 << b) & *r) == 0)
    CPU_set_flag(ZERO_FLAG);
  else
    CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_set_flag(HALF_CARRY_FLAG);
}

/*
CALL n        - Push address of next instruction onto

                stack and then jump to address n.

        Flags affected:
                None
*/
void instr_call_n(uint16_t n) {
  *gb_cpu->HL = n;
  CPU_stack_push(gb_cpu->PC+1);
  gb_cpu->PC = *gb_cpu->HL;
}

/*CALL cc,n     - Call address n if following condition is true:
        cc = NZ, Call if Z flag is reset.
        cc = Z,  Call if Z flag is set.
        cc = NC, Call if C flag is reset.
        cc = C,  Call if C flag is set.

        Flags affected:
                None
*/
// TODO: CHeck if this works out well.
// #define CALL_NZ(cpu, n)
// (if (CPU_check_flag(cpu, ZERO_FLAG) == 0){instr_call(cpu, n)})
// #define CALL_Z(cpu, n)
// (if (CPU_check_flag(cpu, ZERO_FLAG) == 1){instr_call(cpu, n)})
// #define CALL_NC(cpu, n)
// (if (CPU_check_flag(cpu, CARRY_FLAG) == 0){instr_call(cpu, n)})
// #define CALL_C(cpu, n)
// (if (CPU_check_flag(cpu, CARRY_FLAG) == 1){instr_call(cpu, n)})
// void instr_call_cc(CPU_t *cpu, uint16_t n) {
//   memory_write16(memory, cpu->SP, cpu->PC + 1);
//   cpu->SP -= 1; // inc SP
//   cpu->PC = n;
// }

/*
CCF           - Complement carry flag.
        If C flag is set then reset it.
        If C flag is reset then set it.

        Flags affected:
                Z - Not affected.
                N - Reset.
                H - Reset.
                C - Complemented.
*/
void instr_ccf(void) {
  if (CPU_check_flag(CARRY_FLAG)) {
    CPU_clear_flag(CARRY_FLAG);
  } else {
    CPU_set_flag(CARRY_FLAG);
  }
}

/*
CP n          - Compare A with n.
        This is basically an A - n subtraction
        instruction but the results are thrown away.

        n = A,B,C,D,E,H,L,(HL),#

        Flags affected:
                Z - Set if result is zero. (Set if A = n)
                N - Set.
                H - Set if no borrow from bit 4.
                C - Set for no borrow. (Set if A < n.)
*/
void instr_cp(uint8_t *A, uint8_t n) {
  if(*A == 0) CPU_set_flag(ZERO_FLAG);
  CPU_set_flag(SUBTRACT_FLAG);
  //CPU_clear_flag(HALF_CARRY_FLAG);
  if(*A < n) CPU_set_flag(CARRY_FLAG);
}

/*
CPL           - Complement A register. (Flip all bits.)

        Flags affected:
                Z - Not affected.
                N - Set.
                H - Set.
                C - Not affected.
*/
void instr_cpl(uint8_t *A) {
  uint8_t t = ~*A;
  *A = t;
  CPU_set_flag(SUBTRACT_FLAG);
  CPU_set_flag(HALF_CARRY_FLAG);
}

/*
DAA           - Decimal adjust register A.

        This instruction adjusts register A so that the
        correct representation of Binary Coded Decimal
        (BCD) is obtained.

        Flags affected:
                Z - Set if register A is zero.
                N - Not affected.
                H - Reset.
                C - Set of reset according to operation.
*/
void instr_daa(uint8_t *A) {
  uint16_t t = *A;
  if((t&0x000F) > 9 || CPU_check_flag(HALF_CARRY_FLAG))
    t += 0x06;
  if((t>>4) & (0x000F > 9) || CPU_check_flag(CARRY_FLAG))
    t += 0x60;
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(t&0x100)
    CPU_set_flag(CARRY_FLAG);
  *A = t;
  if(*A == 0)
    CPU_set_flag(ZERO_FLAG);
}

/*
DEC n         - Decrement register n.

        n = A,B,C,D,E,H,L,(HL)

        Flags affected:
                Z - Set if result is zero.
                N - Set.
                H - Set if no borrow from bit 4.
                C - Not affected.
*/
void instr_dec_n(uint8_t *reg) {
  uint8_t t = *reg -1;
  if(*reg&0x0F == 0) CPU_set_flag(HALF_CARRY_FLAG);
  *reg = t;
  if(*reg == 0) CPU_set_flag(ZERO_FLAG);
  CPU_set_flag(SUBTRACT_FLAG);

}

/*
DEC nn        - Decrement register nn.

        nn = BC,DE,HL,SP

        Flags affected:
                None
*/
void instr_dec_nn(uint16_t *nn){
  *nn = *nn - 1;
}

/*
DI            - Disable interrupts.
        Flags affected: None
*/
void instr_di(void)
{
   gb_cpu->interrupts = 0;
}

/*
EI            - Enable interrupts.
        This instruction enables the interrupts but not immediately.
        Interrupts are enabled after the instruction after EI is
        executed.

        Flags affected: None
*/
void instr_ei(void)
{
  gb_cpu->interrupts = 1;
}

/*
INC n         - Increment register n.

        n = A,B,C,D,E,H,L,(HL)

  Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Set if carry from bit 3.
                C - Not affected.
*/
void instr_inc_n(uint8_t *reg) {
  *reg += 1;
  if (*reg == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  if (*reg == 0)
    CPU_set_flag(HALF_CARRY_FLAG); // TODO fix this
}

/*
INC nn        - Increment register nn.
        n = BC,DE,HL,SP

        Flags affected:
                None
*/
void instr_inc_nn(uint16_t *reg) {
  *reg += 1;
}

/*
JP n          - Jump to address n.

        n = two byte immediate value. (LSByte first)
        Flags affected:
                None
*/
void instr_jp(uint16_t addr) {
  gb_cpu->PC = addr; //(addr<<8) + (addr>>8); //TODO: check about LSB first
}

/*
JP cc,n       - Jump to address n if following condition
                is true:
        n = two byte immediate value. (LSByte first.)
        cc = NZ, Jump if Z flag is reset.
  cc = Z,  Jump if Z flag is set.
        cc = NC, Jump if C flag is reset.
  cc = C,  Jump if C flag is set.

        Flags affected:
                None
*/
// TODO: Define for all these

/*
JP [HL]       - Jump to address contained in HL.

        Flags affected:
                None
*/
void instr_jp_hl(void) {
  // TODO: check memory is returned in correct order
  gb_cpu->PC = memory_read16(memory, *gb_cpu->HL);
}

/*
JR n          - Add n to current address and jump to it.
        n = one byte signed immediate value.

        Flags affected:
                None
*/
void instr_jr(uint8_t n) {
  if(n&0x80)
  {
    uint8_t t = ~(n);
    gb_cpu->PC -= t;
  }
  else
    gb_cpu->PC += n;
}

/*
JR cc,n       - If following condition is true then
                add n to current address and jump to it:
        n = one byte signed immediate value
        cc = NZ, Jump if Z flag is reset.
        cc = Z,  Jump if Z flag is set.
        cc = NC, Jump if C flag is reset.
        cc = C,  Jump if C flag is set.

        Flags affected:
                None
*/

/*
HALT          - Power down CPU until an interrupt occurs.
        Flags affected:
                None
*/
void instr_halt(void) {
  // TODO: someting ?
}

/*
LD A,n        - Put value n into A.
        n = A,B,C,D,E,H,L,(BC),(DE),(HL),(nnnn),#
        Flags affected:
                None
*/
// void instr_load_an(uint8_t , uint8_t n) { cpu->registers.A = n; }

/*
LD n,A        - Put value A into n.

n = A,B,C,D,E,H,L,(BC,(DE),(HL),(nnnn)

        Flags affected:
                None
*/
void instr_load_ab(uint8_t *A, uint8_t n) { *A = n; }

/*
LD A,[C]      - Put value at address $FF00 + register C into A.

        Flags affected:
                None
*/

/*
LD A,[HLI]    - Put value at address HL into A. Increment HL.
        Flags affected: None
*/

/*
LD A,[HL+]    - Same as LD A,[HLI].
LD A,[HL-]    - Same as LD A,[HLD].
LD A,[HLD]    - Put value at address HL into A. Decrement HL.
*/

/*
LD [C],A      - Put A into address $FF00 + register C.
        Flags affected: None
*/

/*
LD [HL+],A    - Same as LD [HLI],A.
LD [HL-],A    - Same as LD [HLD],A.
*/

/*
LD [HLI],A    - Put A into memory address HL. Increment HL.
        Flags affected: None
*/

/*
LD [HLD],A    - Put A into memory address HL. Decrement HL.
        Flags affected:        None
*/

/*
LD r1,r2      - Put value r2 into r1.
        Flags affected:        None
*/

/*
LD n,nn       - Put value nn into n.
        n = BC,DE,HL,SP
        nn = 16 bit immediate value
        Flags affected:    Non
*/
void instr_load_ab16(uint16_t *A, uint16_t B) {
  *A = B;
}

/*
LD HL,[SP+n]  - Put SP + n into HL.
        n = one byte signed immediate value
        Flags affected:
                Z - Reset.
                N - Reset.
                H - Set or reset according to operation.
                C - Set or reset according to operation.
*/

/*
LD SP,HL      - Put HL into Stack Pointer (SP).
        Flags affected:    None
*/

/*
LD [n],SP     - Put Stack Pointer (SP) at address n.
        n = two byte immediate address
        Flags affected:    None
*/

/*
LDD A,[HL]    - Same as LD A,[HLD].
*/

/*
LDD [HL],A    - Same as LD [HLD],A.
*/

/*
LDH [n],A     - Put A into memory address $FF00 + n.
        n = one byte immediate value
        Flags affected:     None
*/

/*
LDH A,[n]     - Put memory address $FF00 + n into A.
        n = one byte immediate value
        Flags affected:    None
*/

/*
LDHL SP,n     - Same as LD HL,[SP+n]
*/

/*
LDI A,[HL]    - Same as LD A,[HLI].
*/

/*
LDI [HL],A    - Same as LD [HLI],A.
*/

/*
NOP           - No operation.
        Flags affected:     None
*/
void instr_nop(void) {}

/*
OR n          - Logical OR n with register A, result in A.
        n = A,B,C,D,E,H,L,(HL),#
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Reset.
*/
void instr_or(uint8_t *A, uint8_t n) {
  uint8_t t = *A;
  *A = t | n;
}

/*
POP nn        - Pop two bytes off stack into register pair nn.
                Increment Stack Pointer (SP) twice.
        nn = AF,BC,DE,HL
        Flags affected: None
*/
void instr_pop(uint16_t *nn) {
  *nn = CPU_stack_pop();
}

/*
PUSH nn       - Push register pair nn onto stack.
                Decrement Stack Pointer (SP) twice.
        nn = AF,BC,DE,HL
        Flags affected:    None
*/
void instr_push(uint16_t nn) {
  CPU_stack_push(nn);
}

/*
RES b,r       - Reset bit b in register r.
        b = 0-7, r = A,B,C,D,E,H,L,(HL)
        Flags affected:    None
*/
void instr_res(uint8_t b, uint8_t *r) {
  uint8_t x = *r;
  *r = x & ~(0x01 << b);
}

/*
RET           - Pop two bytes from stack & jump to that address.
        Flags affected:   None
*/
void instr_ret(void) {
  uint16_t t = CPU_stack_pop();
  gb_cpu->PC = t;
}

/*
RET cc        - Return if following condition is true:
        cc = NZ, Return if Z flag is reset.
        cc = Z,  Return if Z flag is set.
        cc = NC, Return if C flag is reset.
        cc = C,  Return if C flag is set.

        Flags affected:  None
*/

/*
RETI          - Pop two bytes from stack & jump to that address
                then enable interrupts.
        Flags affected:        None
*/

/*
RL n          - Rotate n left through Carry flag.

        n = A,B,C,D,E,H,L,(HL)

        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 7 data.
*/
void instr_rl(uint8_t *n) {
  uint8_t c = *n>>7;
  uint8_t x = *n << 1;
  x = x + CPU_check_flag(CARRY_FLAG);
  if(x == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(c) CPU_set_flag(CARRY_FLAG);
  else CPU_clear_flag(CARRY_FLAG);
  *n = x;
}

/*
RLC n         - Rotate n left. Old bit 7 to Carry flag.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 7 data.
*/
void instr_rlc(uint8_t *n) {
  uint8_t c = *n>>7;
  uint8_t x = *n << 1;
  *n = x + c;
  if(x == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(c) CPU_set_flag(CARRY_FLAG);
  else CPU_clear_flag(CARRY_FLAG);
}

/*
RR n          - Rotate n right through Carry flag.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 0 data.
*/
void instr_rr(uint8_t *n) {
  uint8_t c = *n & 0x01;
  uint8_t x = *n >> 1;
  x = x | CPU_check_flag(CARRY_FLAG)<<7;
  if(x == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(c) CPU_set_flag(CARRY_FLAG);
  else CPU_clear_flag(CARRY_FLAG);
  *n = x;
}

/*
RRC n         - Rotate n right. Old bit 0 to Carry flag.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 0 data.
*/
void instr_rrc(uint8_t *n) {
  uint8_t c = *n & 0x01;
  uint8_t x = *n >> 1;
  *n = x | c<<7;
  if(x == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(c) CPU_set_flag(CARRY_FLAG);
  else CPU_clear_flag(CARRY_FLAG);
}

/*
RST n         - Push present address onto stack.
                Jump to address $0000 + n.
        n = $00,$08,$10,$18,$20,$28,$30,$38
        Flags affected: none
*/
void instr_rst(uint8_t n) {
  CPU_stack_push(gb_cpu->PC);
  gb_cpu->PC = 0 + n;
}

/*
SBC A,n       - Subtract n + Carry flag from A.
        n = A,B,C,D,E,H,L,(HL),#
        Flags affected:
                Z - Set if result is zero.
                N - Set.
                H - Set if no borrow from bit 4.
                C - Set if no borrow.
*/
void instr_sbc(uint8_t *A, uint8_t n) {
  uint16_t t = *A;
  t = t + ~n;
  t = t + !CPU_check_flag(CARRY_FLAG);
  if(t == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_set_flag(SUBTRACT_FLAG);
  // if(n + !CPU_check_flag(CARRY_FLAG) > *A)
    // CPU_set_flag(HALF_CARRY_FLAG); //TODO: HC flag is wrong...
  if(!(t&0x100)) CPU_set_flag(CARRY_FLAG);
  *A = (uint8_t)t;
}

/*
SCF           - Set Carry flag.
        Flags affected:
                Z - Not affected.
                N - Reset.
                H - Reset.
                C - Set.
*/
void instr_scf(void) { CPU_set_flag(CARRY_FLAG); }

/*
SET b,r       - Set bit b in register r.
        b = 0-7, r = A,B,C,D,E,H,L,(HL)
        Flags affected        None
*/
void instr_set_b(uint8_t b, uint8_t *r) { *r |= 0x01 << b; }

/*
SLA n         - Shift n left into Carry. LSBit of n set to 0.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 7 data.
*/
void instr_sla(uint8_t n) {
  uint8_t t = n << 1;
  if (t == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if (n & 0x80)
    CPU_set_flag(CARRY_FLAG);
  else
    CPU_clear_flag(CARRY_FLAG);
}

/*
SRA n         - Shift n right into Carry. MSBit doesn't change.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 0 data.
*/
void instr_sra(uint8_t n) {

  uint8_t t = n >> 1;
  t |= (n & 0x80); // ensure MSB is 0
  if (t == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if (n & 0x01)
    CPU_set_flag(CARRY_FLAG);
  else
    CPU_clear_flag(CARRY_FLAG);
}

/*
SRL n         - Shift n right into Carry. MSBit of n set to 0.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Contains old bit 0 data.
*/
void instr_srl(uint8_t n) {
  uint8_t t = n >> 1;
  t &= 0x7F; // ensure MSB is 0
  if (t == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if (n & 0x01)
    CPU_set_flag(CARRY_FLAG);
  else
    CPU_clear_flag(CARRY_FLAG);
}

/*
STOP          - ??? affected:    ?
*/
void instr_stop(void) {
    // assert(0);
}

/*
SUB n         - Subtract n from A.
        n = A,B,C,D,E,H,L,(HL),#
        Flags affected:
                Z - Set if result is zero.
                N - Set.
                H - Set if no borrow from bit 4.
                C - Set if no borrow.
*/
void instr_sub_n(uint8_t *A, uint8_t n) {
  uint16_t t = *A;
  t = t + ~n;
  t = t + 1;
  *A = (uint8_t)t;
  if(t == 0) CPU_clear_flag(ZERO_FLAG);
  CPU_set_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  if(!(t&0x100)) CPU_set_flag(CARRY_FLAG);
}

/*
SWAP n        - Swap upper & lower bits of n.
        n = A,B,C,D,E,H,L,(HL)
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Reset.
*/
void instr_swap(uint8_t *n) {
  uint8_t low, high;
  low = *n;
  high = *n;
  *n = low<<4 | high>>4;
  if (*n == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  CPU_clear_flag(CARRY_FLAG);
}

/*
XOR n         - Logical exclusive OR n with
                register A, result in A.
        n = A,B,C,D,E,H,L,(HL),#
        Flags affected:
                Z - Set if result is zero.
                N - Reset.
                H - Reset.
                C - Reset.
*/
void instr_xor(uint8_t *A, uint8_t n) {
  *A ^= n;
  if (*A == 0)
    CPU_set_flag(ZERO_FLAG);
  CPU_clear_flag(SUBTRACT_FLAG);
  CPU_clear_flag(HALF_CARRY_FLAG);
  CPU_clear_flag(CARRY_FLAG);
}
