#include "test/catch.hpp"
#include "z80/cpu.hpp"

SCENARIO("The CPU is initialized", "[z80_cpu]")
{

  Z80::MMU mmu = Z80::MMU();
  Z80::CPU cpu = Z80::CPU(&mmu);

  GIVEN("A CPU is initialized")
  {
    THEN("It sets the registers to their default values")
    {
      REQUIRE( cpu.getRegister(REG_AF)->getValue() == REG_AF_DEFAULT_VALUE );
      REQUIRE( cpu.getRegister(REG_BC)->getValue() == REG_BC_DEFAULT_VALUE );
      REQUIRE( cpu.getRegister(REG_DE)->getValue() == REG_DE_DEFAULT_VALUE );
      REQUIRE( cpu.getRegister(REG_HL)->getValue() == REG_HL_DEFAULT_VALUE );
      REQUIRE( cpu.getRegister(REG_SP)->getValue() == REG_SP_DEFAULT_VALUE );
      REQUIRE( cpu.getRegister(REG_PC)->getValue() == REG_PC_DEFAULT_VALUE );
    }
  }

  GIVEN("A register is requested")
  {
    WHEN("It's a valid register")
    {
      THEN("The register is returned")
      {
        REQUIRE( cpu.getRegister(REG_AF)->getValue() == REG_AF_DEFAULT_VALUE );
      }
    }
  }

  GIVEN("A register needs to be updated")
  {
    WHEN("A valid register is requested")
    {
      THEN("The register is updated")
      {
        uint16_t value = 0x1234;
        cpu.getRegister(REG_AF)->setValue(value);
        REQUIRE( cpu.getRegister(REG_AF)->getValue() == value );
      }
    }
  }

  GIVEN("Clock information needs to be updated")
  {
    THEN("Clock data can be accessed")
    {
      REQUIRE( cpu.getClock()->getClockCycles() == 0 );
    }
  }

  GIVEN("An instruction needs to be executed")
  {

    cpu.getRegister(REG_PC)->setValue(CARTRIDGE_GAME_START_ADDRESS);

    WHEN("It's an invalid instruction")
    {
      THEN("It throws an exception")
      {
        //0xF4 does not exist in this version of the z80
        mmu.setByte( CARTRIDGE_GAME_START_ADDRESS, 0xF4 );
        REQUIRE_THROWS( cpu.cycle() );
      }
    }

    WHEN("It's NOP")
    {
      mmu.setByte( CARTRIDGE_GAME_START_ADDRESS, 0x00 );
      cpu.cycle();
      THEN("It takes 4 machine cycles")
      {
        REQUIRE( cpu.getClock()->getMachineCycles() == 4 );
      }
      THEN("It increments the PC by one")
      {
        REQUIRE( cpu.getRegister(REG_PC)->getValue() == 0x101 );
      }
    }

  }

}