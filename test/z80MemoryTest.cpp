#include "test/catch.hpp"
#include "z80/memory.hpp"

SCENARIO("Memory is initialized", "[z80_memory]")
{

  Z80::Memory m = Z80::Memory();
  const uint8_t addressValue = 0x0F;
  const unsigned short int address = 0xFFF0;

  GIVEN("A new memory object is initiated")
  {

    THEN("The entire memory region is empty")
    {
      for (int i = 0; i < Z80_MEMORY_SIZE; i++)
      {
        REQUIRE( m.readByte(i) == 0 );
      }
    }

  }

  GIVEN("Memory is being addressed")
  {

    WHEN("An address is being modified")
    {
      THEN("The address is updated")
      {
        m.setByte(address, addressValue);
        REQUIRE( m.readByte(address) == addressValue );
      }
    }

    WHEN("An address is requested")
    {

      THEN("The address contents are returned")
      {
        const uint8_t value = 0xFF;
        m.setByte(address, value);
        REQUIRE( m.readByte(address) == value );
      }

    }

    WHEN("An an out-of-bound address is requested")
    {

      THEN("The unsigned address overflows")
      {
        int overflowAddress = Z80_MEMORY_SIZE + 1; // overflows to 0
        m.setByte(overflowAddress, addressValue);
        REQUIRE( m.readByte(0) == addressValue );
      }

    }

    /*
    TODO: to allow int overflow or not?
    WHEN("An invalid address is requested")
    {
      THEN("It throws an exception")
      {
        int address = 65536;
        const char* e = std::string("Invalid address ").append(std::to_string(address)).append(" given.").c_str();
        REQUIRE_THROWS_WITH( m.readByte(address), e);
      }
    }
    */
  }
}