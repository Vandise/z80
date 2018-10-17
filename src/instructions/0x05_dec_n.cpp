#include "z80/cpu.hpp"

// decrements register b
void
Z80::CPU::dec_n()
{

  bool upperFlag = false;
  uint8_t v;
  std::string reg;
  uint8_t n_reg = this->mmu->readByte(
    REGISTER(REG_PC).getValue()
  );

  //
  // Upper or lower register?
  //
  switch (n_reg)
  {
    case 0x05: // reg B
      reg = REG_BC;
      upperFlag = true;
      break;
    default:
      throw std::string("Invalid register for dec_n: ").append(std::to_string(n_reg)).c_str();
  }

  if (upperFlag)
  {
    v = REGISTER(reg).getUpper();
  }
  else
  {
    v = REGISTER(reg).getLower();
  }

  //
  // Flags
  //
  this->setFlags(SUBTRACT_FLAG);
  if ( v - 1 == 0 )
  {
    this->setFlags( ZERO_FLAG );
  }

  if ( (v & 0xF) == 0x00 )
  {
    this->setFlags(HALFCARRY_FLAG);
  }

  if (this->flagIsset(CARRY_FLAG))
  {
    this->setFlags(CARRY_FLAG);
  }


  if (upperFlag)
  {
    REGISTER(reg).setUpper( v - 1 );
  }
  else
  {
    REGISTER(reg).setLower( v - 1 );
  }


  this->incrementPC(1);
  this->clock.incrementMachineCycles(1);
}