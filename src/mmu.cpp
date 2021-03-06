#include "z80/mmu.hpp"

Z80::MMU::MMU()
{
  this->memory = Z80::Memory();
}

Z80::MMU::~MMU()
{
  // todo
}

void
Z80::MMU::setByte(const unsigned short int address, const uint8_t value)
{
  // we clone / shadow the following address range: C000 - DDFF
  // to an 8k higher region
  if ( address >= 0xC000 && address <= 0xDDFF )
  {
    this->memory.setByte( (address + 0x2000), value );
  }
  this->memory.setByte( address, value );
}

uint8_t
Z80::MMU::readByte(const unsigned short int address)
{
  return this->memory.readByte(address);
}

uint16_t
Z80::MMU::readWord(const unsigned short int address)
{
  return this->readByte(address) | this->readByte(address + 1) << 8;
}