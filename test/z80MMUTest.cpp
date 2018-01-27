#include "test/catch.hpp"
#include "z80/mmu.hpp"

SCENARIO("Initializing the memory management unit", "[z80_mmu]")
{

  Z80::Memory m = Z80::Memory();
  Z80::MMU mmu = Z80::MMU();
  mmu.setStrategy( &m );

  GIVEN("An address needs to be written to")
  {

    WHEN("The address is not in echo memory")
    {
      THEN("The address is updated")
      {
        short int address = 0x5FFF;
        uint8_t v = 0x11;
        mmu.setByte(address, v);
        REQUIRE( m.readByte(address) == v );
      }
    }

    WHEN("The address will be in echo memory")
    {
      THEN("The value is shadowed 8kB higher in memory")
      {
        short int address = 0xD000;
        uint8_t v = 0x22;
        mmu.setByte(address, v);

        REQUIRE( m.readByte(address) == v );
        REQUIRE( m.readByte(address + 0x2000) == v );
      }
    }

  }

}