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

  GIVEN("The register is updated")
  {

    uint16_t value = 0xAABB;
    Z80::Register r = Z80::Register(value);

    WHEN("It's lower byte")
    {
      THEN("The lower 8 bits are set")
      {
        uint8_t upper = r.getUpper();
        uint8_t lower = 0xFF;
        r.setLower(lower);
        REQUIRE( r.getLower() == lower );
        REQUIRE( r.getUpper() == upper );
      }
    }

    WHEN("It's upper byte")
    {
      THEN("The upper 8 bits are set")
      {
        uint8_t lower = r.getLower();
        uint8_t upper = 0xFF;
        r.setUpper(upper);
        REQUIRE( r.getLower() == lower );
        REQUIRE( r.getUpper() == upper );
      }
    }

    WHEN("It's the entire register")
    {
      THEN("All 16 bits are set")
      {
        uint16_t value = 0x1234;
        r.setValue(value);
        REQUIRE( r.getValue() == value );
      }
    }

  }

}