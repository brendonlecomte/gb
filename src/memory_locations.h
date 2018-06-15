#ifndef MEM_LOC_H
#define MEM_LOC_H


//MEMORY CHUNKS
#define CART_SIZE (0x8000)
#define SRAM_SIZE (0x2000)
#define IO_SIZE (0x100)
#define VRAM_SIZE (0x2000)
#define OAM_SIZE (0x100)
#define WRAM_SIZE (0x2000)
#define HRAM_SIZE (0x80)
#define FULL_MEMORY (0x10000)


//DISPLAY REGISTERs
#define LCDC (0xFF40)
#define STAT (0xFF41)
#define SCY (0xFF42)
#define SCX (0xFF43)
#define LY (0xFF44) //current output line (R)
#define LYC (0xFF45) //Compare against LY
#define WY (0xFF4A)
#define WX (0xFF4B)
#define SPRITES (0xFE00)

#define BGP (0xFF47) //background palette
#define OBP0 (0xFF48) //alt palette
#define OBP1 (0xFF49) //alt palette 2

//CGB only
#define BCPS (0xFF68)
#define BCPD (0xFF69)
#define OCPS (0xFF6A)
#define OCPD (0xFF6B)
#define HDMA1 (0xFF51)
#define HDMA2 (0xFF51)
#define HDMA3 (0xFF51)
#define HDMA4 (0xFF51)
#define HDMA5 (0xFF51)

#define DMA (0xFF46)

//SOUND REGISTERS
//sound channel 1 tone and sweep
#define NR10 (0xFF10)
#define NR11 (0xFF11)
#define NR12 (0xFF12)
#define NR13 (0xFF13)
#define NR14 (0xFF14)
//sound channel 2 tone
#define NR21 (0xFF16)
#define NR22 (0xFF17)
#define NR23 (0xFF18)
#define NR24 (0xFF19)
//sound channel 3 wave
#define NR30 (0xFF1A)
#define NR31 (0xFF1B)
#define NR32 (0xFF1C)
#define NR33 (0xFF1D)
#define NR34 (0xFF1E)
#define WAVE_PATTERN (0xFF30)
//sound channel 4 noise
#define NR41 (0xFF20)
#define NR42 (0xFF21)
#define NR43 (0xFF22)
#define NR44 (0xFF23)
#define WAVE_PATTERN (0xFF30)
//sound control registers
#define NR50 (0xFF24)
#define NR51 (0xFF25)
#define NR52 (0xFF26)

//IO REGISTERS
#define JOYP (0xFF00)

//BOOT
#define BOOT (0xFF50)

//SERIAL CABLE
#define SB (0xFF01)
#define SC (0xFF02)

//TIMES AND DIVIDE
#define DIV (0xFF04)
#define TIMA (0xFF05)
#define TMA (0xFF06)
#define TAC (0xFF07)

//INTERRUPTS
#define IE (0xFFFF)
#define IF (0xFF0F)

//CGB only
#define KEY1 (0xFF4D)
#define RP (0xFF56)
#define SVBK (0xFF70)


#endif //MEM_LOC_H
