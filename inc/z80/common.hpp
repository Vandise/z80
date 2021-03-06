#ifndef __Z80_COMMON
#define __Z80_COMMON 1

#define DEBUG_SYSTEM true

#define REG_AF "af"
#define REG_BC "bc"
#define REG_DE "de"
#define REG_HL "hl"
#define REG_SP "sp"
#define REG_PC "pc"

// start address to write the cartridge to in memory
#define CARTRIDGE_START_ADDRESS 0x0000

// where our the game starts
#define CARTRIDGE_GAME_START_ADDRESS 0x0100

// Max cartridge size (32k)
#define MAX_CARTRIDGE_SIZE 0x8000

// Max addressable memory is 65k
#define Z80_MEMORY_SIZE 0xFFFF

// Max Cartridge size is 32kB (32767 bytes)
#define CARTRIDGE_START_ADDRESS 0x0000
#define CARTRIDGE_END_ADDRESS   0x7FFF 

// Max video ram size is 8kB
#define VIDEO_START_ADDRESS 0x8000
#define VIDEO_END_ADDRESS   0x9FFF

// Max switchable RAM is 8kB
#define SRAM_START_ADDRESS 0xA000
#define SRAM_END_ADDRESS   0xBFFF

// Max internal RAM is 8Kb
#define INTERNAL_RAM_START_ADDRESS 0xC000
#define INTERAL_RAM_END_ADDRESS    0xDFFF

// Echo of internal RAM (apparently)
// If this isn't used for anything else, it's probably not needed
// echo range: C000 - DDFF
// offset is 0x2000 (8k higher)
#define ECHO_INTERNAL_RAM_START_ADDRESS 0xE000
#define ECHO_INTERNAL_RAM_END_ADDRESS   0xFDFF

// Sprite attribute memory
#define OAM_START_ADDRESS 0xFE00
#define OAM_END_ADDRESS   0xFEFF

// Empty, unaddressable region (possibly)
#define EMPTY_START_ADDRESS 0xFEA0
#define EMPTY_END_ADDRESS   0xFEFF

// IO Ports
#define IO_START_ADDRESS 0xFF00
#define IO_END_ADDRESS   0xFF4B

// System internal ram
#define SYSTEM_RAM_START_ADDRESS 0xFF80
#define SYSTEM_RAM_END_ADDRESS   0xFFFE

/*
  lower 0: VBlank
        1: LCD stat off
        2: Timer off
        3: Serial off
        4: Joypad off
*/
#define VBLANK_INTERRUPT_HANDLER_ADDRESS 0x0040

// when bits are set, an interrupt has happened
#define INTERRUPT_FLAGS_REGISTER  0xFF0F
// interrupt register
#define INTERRUPT_ENABLE_REGISTER 0xFFFF

#endif