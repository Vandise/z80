#ifndef __Z80_SYSTEM
#define __Z80_SYSTEM 1

#include <iostream>

#include "z80/common.hpp"
#include "util/hexdump.hpp"
#include "z80/cpu.hpp"
#include "z80/mmu.hpp"
#include "z80/cartridge.hpp"

namespace Z80
{
  class System
  {
    private:
      Z80::CPU cpu;
      Z80::MMU mmu;
      Z80::Cartridge *cartridge;

    public:
      System();
      void loadCartridge(Z80::Cartridge *cartridge);
      void dumpMemory();
  };
}

#endif