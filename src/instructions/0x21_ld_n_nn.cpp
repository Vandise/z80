#include "z80/cpu.hpp"

void
Z80::CPU::ld_n_nn()
{
  uint8_t n_reg = this->mmu->readByte(
    REGISTER(REG_PC).getValue()
  );

  this->incrementPC(1);
  switch(n_reg) {
    case 0x21:
      REGISTER(REG_HL).setValue(
        this->mmu->readWord( REGISTER(REG_PC).getValue() )
      );
      break;
    default:
      throw std::string("Invalid register for ld_n_nn: ").append(std::to_string(n_reg)).c_str();
  }

  // loaded 16bits
  this->incrementPC(2);

  this->clock.incrementMachineCycles(3);
}