#include "z80/cpu.hpp"

// Put A into memory address HL. Decrement HL
// when assembled, the instruction is only 1 byte
//  ldd     (hl),a
//    0x32
//  ld      b,0
//    0x06  0x00
void
Z80::CPU::ld_hld_a()
{
  uint16_t to_address = REGISTER(REG_HL).getValue();
  uint8_t value = REGISTER(REG_AF).getUpper();

  this->mmu->setByte(to_address, value);
  REGISTER(REG_HL).decrement();

  this->incrementPC(1);
  this->clock.incrementMachineCycles(2);
}