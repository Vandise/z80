#include "z80/cpu.hpp"

void
Z80::CPU::jp_a16()
{
  this->incrementPC(1);
  (this->registers[REG_PC]).setValue(
    this->mmu->readWord( (this->registers[REG_PC]).getValue() )
  );
  this->clock.incrementMachineCycles(16);
}