#include "z80/cpu.hpp"

void
Z80::CPU::jp_a16()
{
  this->incrementPC(1);
  REGISTER(REG_PC).setValue(
    this->mmu->readWord( REGISTER(REG_PC).getValue() )
  );
  this->clock.incrementMachineCycles(16);
}