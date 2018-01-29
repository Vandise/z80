#include "z80/cpu.hpp"

void
Z80::CPU::nop()
{
  this->incrementPC(1);
  this->clock.incrementMachineCycles(4);
}