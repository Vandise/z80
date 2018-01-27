#include <iostream>
#include "z80/cartridge.hpp"
#include "z80/system.hpp"

int
main( const int argc, const char **argv )
{
  //-BREAKPOINT-
  Z80::Cartridge c = Z80::Cartridge("resources/roms/tetris.gb");
  Z80::System system = Z80::System();

  if ( c.isLoaded() )
  {
    c.initialize();
  }
  else
  {
    // cartridge not found
    return 1;
  }

  if ( c.isValid() )
  {
    system.loadCartridge(&c);
    system.dumpMemory();
  }
  else
  {
    // invalid or unsupported cartridge
    return 1;
  }

  return 0;
}