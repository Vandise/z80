#include "test/catch.hpp"
#include "z80/register.hpp"

SCENARIO("Register is initialized", "[z80_register]")
{

  GIVEN("A Register is initialize")
  {

    WHEN("A default value is specified")
    {
      THEN("It sets the register to the specified value")
      {
        uint16_t value = 0xFFAA;
        Z80::Register r = Z80::Register(value);
        REQUIRE( r.getValue() == value );
      }
    }

    WHEN("No value is specified")
    {
      THEN("The register is set to 0x0000")
      {
        Z80::Register r = Z80::Register();
        REQUIRE( r.getValue() == 0x0000 );
      }
    }

  }

  GIVEN("The register value is requested")
  {

    uint16_t value = 0xABCD;
    Z80::Register r = Z80::Register(value);

    WHEN("Addressed as 16 bit")
    {
      THEN("The entire register is returned")
      {
        REQUIRE( r.getValue() == value );
      }
    }

    WHEN("Addressed as lower 8 bits")
    {
      THEN("The lower 8 bits of the register is returned")
      {
        REQUIRE( r.getLower() == 0xCD );
      }
    }

    WHEN("Addressed as upper 8 bits")
    {
      THEN("The upper 8 bits of the register is returned")
      {
        REQUIRE( r.getUpper() == 0xAB );
      }
    }

  }

}