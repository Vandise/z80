#ifndef __Z80_MEMORY_MANAGEMENT_UNIT
#define __Z80_MEMORY_MANAGEMENT_UNIT 1

#include <cstdint>
#include "z80/common.hpp"
#include "z80/memory.hpp"

namespace Z80
{
  class MMU
  {
    private:
      Z80::Memory *strategy;

    public:
      MMU() = default;
      ~MMU();
      void setStrategy(Z80::Memory *strategy);
      void setByte(const unsigned short int address, const uint8_t value);
      uint8_t readByte(const unsigned short int address);
      uint16_t readWord(const unsigned short int address);
  };
}

#endif