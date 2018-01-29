#include <iostream>
#include "z80/cartridge.hpp"
#include "z80/system.hpp"

void debugCartridge( Z80::Cartridge c )
{
  if ( DEBUG_SYSTEM )
  {
    std::cout << "Catridge title: " << c.getTitle() << std::endl;
    std::cout << "\t Valid: " << c.isValid() << std::endl;
    std::cout << "\t ROM Size: " << c.getRomSize() << std::endl;
    std::cout << "\t RAM Size: " << c.getRamSize() << std::endl;
    std::cout << "\t Cartridge Type: " << c.getCartridgeType() << std::endl;
  }
}

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

  debugCartridge(c);

  if ( c.isValid() )
  {
    // boot the bios
    system.boot();
    // load the cartridge
    system.loadCartridge(&c);

    // game loop
    while(!system.isTerminated())
    {
      // todo
      system.run();
    }

  }
  else
  {
    // invalid or unsupported cartridge
    return 1;
  }

  return 0;
}