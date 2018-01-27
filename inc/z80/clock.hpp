#ifndef __Z80_CLOCK
#define __Z80_CLOCK 1

#include <cstdint>

#define MACHINE_TO_CLOCK_CYCLES(i) (i * 4)

/*

So nintendo does this weird thing where they mesure things in "machine" cycles
as opposed to clock cycles. 1 machine cycle = 4 clock cycles

I have yet to see if some operations require machine or clock cycles, so both
I'll provide both for the time being (only machine cycles can be incremented though)

*/

namespace Z80
{
  class Clock
  {
    private:
      unsigned short cycles;
      unsigned short machineCycles;

    public:
      Clock();
      void incrementMachineCycles(const uint8_t cycles);
      unsigned short getClockCycles();
      unsigned short getMachineCycles();

  };
}

#endif