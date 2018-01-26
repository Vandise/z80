#ifndef __Z80_MEMORY
#define __Z80_MEMORY 1

#include <cstdint>
#include <string>
#include "z80/common.hpp"

namespace Z80
{
  class Memory
  {
    private:
      uint8_t memory[Z80_MEMORY_SIZE];

    public:
      Memory();
      void setByte(const unsigned short int address, const uint8_t value);
      uint8_t readByte(const unsigned short int address);
  };
}

#endif