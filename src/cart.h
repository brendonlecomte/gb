#ifndef CART_H
#define CART_H
#include <stdint.h>

enum {
    ROM_ONLY,
    MBC1,
    MBC1_RAM,
    MBC1_RAM_BATTERY,
    MBC2,
    MBC2_BATTERY,
    ROM_RAM,
    ROM_RAM_BATTERY,
    MMM01,
    MMM01_RAM,
    MMM01_RAM_BATTERY,
    MBC3_TIMER_BATTERY,
    MBC3_TIMER_RAM_BATTERY,
    MBC3,
    MBC3_RAM,
    MBC_RAM_BATTERY,
    MBC4,
    MBC4_RAM,
    MBC4_RAM_BATTERY,
    MBC5,
    MBC5_RAM,
    MBC5_RAM_BATTERY,
    MBC5_RUMBLE,
    MBC5_RUMBLE_RAM,
    MBC5_RUMBLE_RAM_BATTERY,
    CAMERA,
    BANDAI,
    HUC3,
    HUC1_MBC_RAM_BATTERY
} cart_type_e;



typedef struct {
    uint8_t entry[0x04]; // 0x100-103
    uint8_t logo[0x2F];  //0x104 - 0x133
    uint8_t title[0x0F]; // 0x134 - 0x143
    uint8_t cgb_flag; //0x143
    uint16_t licensee; //0x144 - 0x145
    uint8_t sgb_flag; //0x146
    uint8_t cart_type; //0x147
    uint8_t rom_size; //0x148
    uint8_t ram_size; //0x149
    uint8_t dest_code; ///0x14A
    uint8_t old_licensee; //0x14B
    uint8_t version; //0x14D
    uint8_t header_checksum;
    uint16_t checksum; //0x14E - 0x14F
} cart_t;


void cart_load(uint8_t *mem, uint16_t size);

#endif CART_H
