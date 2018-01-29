#include "test/catch.hpp"
#include "z80/system.hpp"

SCENARIO("A Z80 system is initialized", "[z80_system]")
{
  Z80::System system = Z80::System();

  GIVEN("A system hasn't been booted yet")
  {
    THEN("It's status is terminated")
    {
      REQUIRE(system.isTerminated() == true);
    }
    THEN("It hasn't been booted")
    {
      REQUIRE(system.isBooted() == false);
    }
  }
}