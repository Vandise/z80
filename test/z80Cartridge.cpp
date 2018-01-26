#include "test/catch.hpp"
#include "z80/cartridge.hpp"

std::string cartridgeName = "resources/roms/tetris.gb";

SCENARIO("Initializing a cartridge", "[z80_cartridge]")
{

  GIVEN("A cartridge will be loaded")
  {
    WHEN("It's a valid cartridge")
    {

      Z80::Cartridge c = Z80::Cartridge(cartridgeName);
      c.initialize();

      THEN("It will be marked as valid")
      {
        REQUIRE( c.isValid() == true );
      }

      THEN("It will be marked as loaded")
      {
        REQUIRE( c.isLoaded() == true );
      }

      THEN("The cartridge type is extracted")
      {
        REQUIRE( c.getCartridgeType() == ROM_ONLY );
      }

      THEN("The ROM size is extracted")
      {
        int tetrisRomSize = 0;
        REQUIRE( c.getRomSize() == tetrisRomSize );
      }

      THEN("The RAM size is extracted")
      {
        int tetrisRamSize = 0;
        REQUIRE( c.getRamSize() == tetrisRamSize );
      }

      THEN("The cartridge name will be extracted")
      {
        REQUIRE(c.getTitle().find("TETRIS") != std::string::npos);
      }

    }
  }

}