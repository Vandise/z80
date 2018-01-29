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

  GIVEN("Flags need to be altered")
  {
    // ZERO_FLAG | CARRY_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG
    cpu.getRegister(REG_AF)->setLower(0x00); // clear flags
    WHEN("A flag is set")
    {
      THEN("it is registered as set")
      {
        cpu.setFlags(ZERO_FLAG);
        REQUIRE( cpu.flagIsset(ZERO_FLAG) );
      }
    }

    WHEN("A flag is not set")
    {
      THEN("it is registered as not set")
      {
        REQUIRE( cpu.flagIsset(ZERO_FLAG) == false );
      }
    }

    GIVEN("Flags need to be cleared")
    {
      cpu.setFlags(ZERO_FLAG | CARRY_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);
      WHEN("Only one flag is being cleared")
      {
        THEN("The other flags remain unaltered")
        {
          cpu.clearFlags(ZERO_FLAG);
          REQUIRE( cpu.flagIsset(ZERO_FLAG) == false );
          REQUIRE( cpu.flagIsset(CARRY_FLAG) == true );
          REQUIRE( cpu.flagIsset(NEGATIVE_FLAG) == true );
          REQUIRE( cpu.flagIsset(HALFCARRY_FLAG) == true );
        }
      }

      WHEN("Multiple flags are being cleared")
      {
        THEN("All specified flags are cleared")
        {
          cpu.clearFlags(CARRY_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);
          REQUIRE( cpu.flagIsset(ZERO_FLAG) == true );
          REQUIRE( cpu.flagIsset(CARRY_FLAG) == false );
          REQUIRE( cpu.flagIsset(NEGATIVE_FLAG) == false );
          REQUIRE( cpu.flagIsset(HALFCARRY_FLAG) == false );
        }
      }
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

    WHEN("It's jp_a16")
    {
      mmu.setByte(CARTRIDGE_GAME_START_ADDRESS,     0xC3);
      mmu.setByte(CARTRIDGE_GAME_START_ADDRESS + 1, 0x50);
      mmu.setByte(CARTRIDGE_GAME_START_ADDRESS + 2, 0x01);
      cpu.cycle();

      THEN("It takes 16 machine cycles")
      {
        REQUIRE( cpu.getClock()->getMachineCycles() == 16 );
      }
      THEN("It updates the PC to the specified address")
      {
        REQUIRE( cpu.getRegister(REG_PC)->getValue() == 0x0150 );
      }
    }

    WHEN("It's xor_a")
    {
      uint8_t regValue = 0x11;
      mmu.setByte(CARTRIDGE_GAME_START_ADDRESS, 0xAF);
      cpu.getRegister(REG_AF)->setValue(regValue);
      cpu.cycle();

      THEN("The register xor's itself")
      {
        uint8_t v = cpu.getRegister(REG_AF)->getUpper();
        REQUIRE( v == (regValue ^ regValue) );
      }

      THEN("All flags but ZERO are cleared")
      {
        REQUIRE( cpu.flagIsset(ZERO_FLAG) );
        REQUIRE( cpu.flagIsset(CARRY_FLAG) == false );
        REQUIRE( cpu.flagIsset(NEGATIVE_FLAG) == false );
        REQUIRE( cpu.flagIsset(HALFCARRY_FLAG) == false );
      }

    }

  }

}