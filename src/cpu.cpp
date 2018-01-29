#include "z80/cpu.hpp"

Z80::CPU::CPU(Z80::MMU *mmu)
{
  this->clock = Z80::Clock();
  this->mmu = mmu;
  this->registers = {
    { REG_AF, Z80::Register(REG_AF_DEFAULT_VALUE) },
    { REG_BC, Z80::Register(REG_BC_DEFAULT_VALUE) },
    { REG_DE, Z80::Register(REG_DE_DEFAULT_VALUE) },
    { REG_HL, Z80::Register(REG_HL_DEFAULT_VALUE) },
    { REG_SP, Z80::Register(REG_SP_DEFAULT_VALUE) },
    { REG_PC, Z80::Register(REG_PC_DEFAULT_VALUE) }
  };
}

Z80::Clock*
Z80::CPU::getClock()
{
  return &(this->clock);
}

Z80::Register*
Z80::CPU::getRegister(const std::string identifier)
{
  return &(this->registers[identifier]);
}