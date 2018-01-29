#include "z80/cpu.hpp"

void
Z80::CPU::jp_a16()
{
  //this->incrementPC(1);
  this->clock.incrementMachineCycles(16);
}