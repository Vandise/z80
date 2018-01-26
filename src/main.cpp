#include <iostream>
#include "z80/cartridge.hpp"

int
main( const int argc, const char **argv )
{
  //-BREAKPOINT-
  Z80::Cartridge c = Z80::Cartridge("resources/roms/tetris.gb");
  c.initialize();
  return 0;
}