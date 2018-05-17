# GB Emulator (C)

## Goal
To build a clone of the GB/GBC. From C based Emulator right through to custom
hardware that fits inside the original gameboy case.

### C based emulator Todo List
- [x] Basic CPU
- [x] Memory (basic no paging)
- [x] SDL host screen
- [x] Boot rom w/ swap in/out
- [x] Timer
- [ ] Memory Bank controllers
- [x] Interrupts
- [ ] DMA
- [ ] PPU
- [ ] Keyboard inputs
- [ ] GBC upgrade changes

### Unit Tests
- [ ] Instruction Unit tests
- [x] Timer
- [x] Boot Rom
- [x] Memory

### Blarggs Tests
- [ ] 01 - special
- fails on DAA
- [x] 02 - Interrupts
- [ ] 03 - OP SP,HL
- [ ] 04 - OP r,imm
- [x] 05 - OP rp
- [x] 06 - OP ld r,r
- [ ] 07 - jr, jp, call, ret, rst
- [x] 08 - misc instrs
- [ ] 09 - OP r,r
- [ ] 10 - bit ops
- [ ] 11 - OP a, (hl)
- [ ] cpu_instrs

## Building
To build and run unit tests against the source

```
make
```

To build and run the emulator. Cart is defined for host in src/host/cart.c
```
make run
```
