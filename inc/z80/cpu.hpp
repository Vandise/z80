#ifndef __Z80_CPU
#define __Z80_CPU 1

#include <map>
#include <string>
#include <iostream>
#include "util/hexdump.hpp"
#include "z80/register.hpp"
#include "z80/clock.hpp"
#include "z80/mmu.hpp"
#include "z80/common.hpp"

#define REG_PC_DEFAULT_VALUE 0x0100
#define REG_SP_DEFAULT_VALUE 0xFFFE
#define REG_AF_DEFAULT_VALUE 0x0100
#define REG_DE_DEFAULT_VALUE 0x00D8
#define REG_BC_DEFAULT_VALUE 0x0013
#define REG_HL_DEFAULT_VALUE 0x014D

#define REGISTER(r) (this->registers[r])

#define ZERO_FLAG (1 << 7)
#define SUBTRACT_FLAG (1 << 6)
#define HALFCARRY_FLAG (1 << 5)
#define CARRY_FLAG (1 << 4)

namespace Z80
{
  class CPU
  {
    typedef void(Z80::CPU::*instructionHandle)();

    private:
      Z80::Clock clock;
      Z80::MMU *mmu;
      std::map<std::string, Z80::Register> registers;
      std::map<uint8_t, instructionHandle> instructions;

      void incrementPC(unsigned short int amount);

    public:
      CPU(Z80::MMU *mmu);
      Z80::Clock* getClock();
      Z80::Register* getRegister(const std::string identifier);
      void cycle();
      void clearFlags(uint8_t f);
      void setFlags(uint8_t f);
      bool flagIsset(uint8_t f);
      bool interrupted();

    //
    // INSTRUCTIONS
    //
    private:
      void nop();     // 0x00
      void xor_a();   // 0xAF
      void jp_a16();  // 0xC3
      void ld_n_nn(); // 0x01, 0x11, 0x21, 0x31,
      void ld_nn_n(); // 0x06, 0x0E, 0x16, 0x1E, 0x26, 0x2E
      void ld_hld_a(); // 0x32
      void dec_n();    // 0x05
      void jr_cc_n();  // 0x20, 0x28, 0x30, 0x38

  };
}

#endif