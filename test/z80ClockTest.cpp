#include "test/catch.hpp"
#include "z80/clock.hpp"

SCENARIO("Initializing a cpu clock", "[z80_clock")
{

  Z80::Clock c = Z80::Clock();

  GIVEN("A clock is initialized")
  {

    WHEN("It hasn't been updated")
    {
      THEN("It defaults to zero")
      {
        REQUIRE(c.getMachineCycles() == 0);
      }
    }

    WHEN("It needs to be updated")
    {
      THEN("It can be updated via machine cycles")
      {
        c.incrementMachineCycles(2);
        REQUIRE(c.getMachineCycles() == 2);
      }
    }

    WHEN("Clock information is required")
    {
      c.incrementMachineCycles(3);
      THEN("It can be retrieved as machineCycles")
      {
        REQUIRE(c.getMachineCycles() == 3);
      }

      THEN("It can be retrieved as clock cycles")
      {
        REQUIRE(c.getClockCycles() == 12);
      }
    }

  }

}