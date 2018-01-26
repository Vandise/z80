#include "z80/memory.hpp"

Z80::Memory::Memory()
{
  for (int i = 0; i < Z80_MEMORY_SIZE; i++)
  {
    this->memory[i] = 0;
  }
}

void
Z80::Memory::setAddress(const unsigned short int address, const uint8_t value)
{
  //TODO: do I allow int overflow or not?
  this->memory[address] = value;
}

uint8_t
Z80::Memory::getAddress(const unsigned short int address)
{
  //TODO: do I allow int overflow or not?
  /*
  if (address > Z80_MEMORY_SIZE)
  {
    throw std::string("Invalid address ").append(std::to_string(address)).append(" given.").c_str();
  }
  */
  return this->memory[address];
}