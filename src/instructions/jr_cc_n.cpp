#include "z80/cpu.hpp"

/*
If following condition is true then add n to current address and jump to it:
  Use with:
    n = one byte signed immediate value
    cc = NZ, Jump if Z flag is reset.
    cc=Z, JumpifZflagisset.
    cc = NC, Jump if C flag is reset.
    cc=C, JumpifCflagisset.
*/
void
Z80::CPU::jr_cc_n()
{
  bool jumped = false;
  uint8_t SIGNED_THRESHOLD = 127;
  uint8_t instruction = this->mmu->readByte(
    REGISTER(REG_PC).getValue()
  );

  this->incrementPC(1);

  int jmp_bytes = this->mmu->readByte(
    REGISTER(REG_PC).getValue()
  );

  // if > 127, we're jumping back n amount of instructions
  if ( jmp_bytes > SIGNED_THRESHOLD )
  {
    jmp_bytes = -((~jmp_bytes + 1) & 255);
  }

  switch (instruction)
  {
    case 0x20:
      if ( !this->flagIsset(ZERO_FLAG) )
      {
        REGISTER(REG_PC).setValue(
          REGISTER(REG_PC).getValue() + jmp_bytes
        );
        jumped = true;
      }
      break;
    default:
      throw std::string("Invalid JR command jr_cc_n: ").append(std::to_string(instruction)).c_str();
  }

  this->clock.incrementMachineCycles(2);

  if (!jumped)
  {
    this->incrementPC(1);
  }
}