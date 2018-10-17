#include "z80/cpu.hpp"

void
Z80::CPU::ld_nn_n()
{
  uint8_t n_reg = this->mmu->readByte(
    REGISTER(REG_PC).getValue()
  );

  this->incrementPC(1);

  switch(n_reg) {
    case 0x0E:
      REGISTER(REG_BC).setLower(
        this->mmu->readByte( REGISTER(REG_PC).getValue() )
      );
      break;
    default:
      throw std::string("Invalid register for ld_nn_n: ").append(std::to_string(n_reg)).c_str();
  }

  this->incrementPC(1);
}