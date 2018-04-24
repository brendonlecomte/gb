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

### Tests
- [ ] Instruction Unit tests
- [ ] Blarggs Tests
- [ ] Mooneye Tests

## Building
To build and run unit tests against the source

```
make
```

To build and run the emulator. Cart is defined for host in src/host/cart.c
```
make run
```
