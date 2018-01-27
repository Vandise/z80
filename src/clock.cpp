#include "z80/clock.hpp"

Z80::Clock::Clock()
{
  this->cycles = 0;
  this->machineCycles = 0;
}

void
Z80::Clock::incrementMachineCycles(const uint8_t cycles)
{
  this->machineCycles += cycles;
  this->cycles += MACHINE_TO_CLOCK_CYCLES(cycles);
}

unsigned short
Z80::Clock::getClockCycles()
{
  return this->cycles;
}

unsigned short
Z80::Clock::getMachineCycles()
{
  return this->machineCycles;
}