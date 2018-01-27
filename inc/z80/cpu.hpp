#ifndef __Z80_CPU
#define __Z80_CPU 1

#include <map>
#include <string>
#include "z80/register.hpp"
#include "z80/clock.hpp"
#include "z80/common.hpp"

#define REG_PC_DEFAULT_VALUE 0x0100
#define REG_SP_DEFAULT_VALUE 0xFFFE
#define REG_AF_DEFAULT_VALUE 0x0100
#define REG_DE_DEFAULT_VALUE 0x00D8
#define REG_BC_DEFAULT_VALUE 0x0013
#define REG_HL_DEFAULT_VALUE 0x014D

namespace Z80
{
  class CPU
  {

    private:
      Z80::Clock clock;
      std::map<std::string, Z80::Register> registers;

    public:
      CPU();
      Z80::Clock* getClock();
      Z80::Register* getRegister(const std::string identifier);

  };
}

#endif