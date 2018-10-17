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
  this->instructions[0x21] = &Z80::CPU::ld_n_nn;
  this->instructions[0xAF] = &Z80::CPU::xor_a;
  this->instructions[0xC3] = &Z80::CPU::jp_a16;
  this->instructions[0x0E] = &Z80::CPU::ld_nn_n;

}

void
Z80::CPU::clearFlags(uint8_t f)
{
  uint8_t v = REGISTER(REG_AF).getLower();
  v &= ~(f);
  REGISTER(REG_AF).setLower(v);
}

void
Z80::CPU::setFlags(uint8_t f)
{
  uint8_t v = REGISTER(REG_AF).getLower();
  v |= f;
  REGISTER(REG_AF).setLower(v);
}

bool
Z80::CPU::flagIsset(uint8_t f)
{
  return REGISTER(REG_AF).getLower() & f;
}

void
Z80::CPU::incrementPC(unsigned short int amount)
{
  uint16_t value = REGISTER(REG_PC).getValue();
  value += amount;
  REGISTER(REG_PC).setValue(value);
}

bool
Z80::CPU::interrupted()
{
  // return if any interrupt bits have been triggered
  return this->mmu->readByte(INTERRUPT_FLAGS_REGISTER) & this->mmu->readByte(INTERRUPT_ENABLE_REGISTER);
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
    REGISTER(REG_PC).getValue()
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