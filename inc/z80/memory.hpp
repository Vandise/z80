#ifndef __Z80_MEMORY
#define __Z80_MEMORY 1

#include <cstdint>
#include <string>

// Max addressable memory is 65k
#define Z80_MEMORY_SIZE 0xFFFF

namespace Z80
{
  class Memory
  {
    private:
      uint8_t memory[Z80_MEMORY_SIZE];

    public:
      Memory();
      void setAddress(const unsigned short int address, const uint8_t value);
      uint8_t getAddress(const unsigned short int address);
  };
}

#endif