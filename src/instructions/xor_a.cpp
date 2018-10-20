#include "z80/cpu.hpp"

void
Z80::CPU::xor_a()
{
  uint8_t v = REGISTER(REG_AF).getUpper();
  v ^= v;
  REGISTER(REG_AF).setUpper(v);

  this->setFlags( ZERO_FLAG );
  this->clearFlags( CARRY_FLAG | SUBTRACT_FLAG | HALFCARRY_FLAG );

  this->incrementPC(1);
  this->clock.incrementMachineCycles(1);
}