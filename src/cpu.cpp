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

  this->instructions[0x00] = &Z80::CPU::nop;

}

void
Z80::CPU::incrementPC(unsigned short int amount)
{
  uint16_t value = (this->registers[REG_PC]).getValue();
  value += amount;
  (this->registers[REG_PC]).setValue(value);
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

void
Z80::CPU::cycle()
{
  uint8_t instruction = this->mmu->readByte(
    (this->registers[REG_PC]).getValue()
  );

  if ( this->instructions.count(instruction) )
  {
    // execute the instruction if implemented
    (this->*(this->instructions[instruction]))();
  }
  else
  {
    if (DEBUG_SYSTEM)
    {
      std::cout << hexdump(instruction);
    }
    throw std::string("Unimplemented instruction: ").append(std::to_string(instruction)).c_str();
  }
}