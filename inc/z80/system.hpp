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
      bool terminated = true;
      bool booted = false;
      Z80::CPU cpu;
      Z80::MMU mmu;
      Z80::Cartridge *cartridge;

    public:
      System(): mmu(), cpu(&mmu), cartridge(nullptr){};
      void loadCartridge(Z80::Cartridge *cartridge);
      void dumpMemory();
      bool isTerminated();
      bool isBooted();
      void boot();
      Z80::CPU* getCPU();
      void run();
  };
}

#endif