#include "z80/mmu.hpp"

Z80::MMU::~MMU()
{
  this->strategy = nullptr;
}

void
Z80::MMU::setStrategy(Z80::Memory *strategy)
{
  this->strategy = strategy;
}

void
Z80::MMU::setByte(const unsigned short int address, const uint8_t value)
{
  // we clone / shadow the following address range: C000 - DDFF
  // to an 8k higher region
  if ( address >= 0xC000 && address <= 0xDDFF )
  {
    this->strategy->setByte( (address + 0x2000), value );
  }
  this->strategy->setByte( address, value );
}

uint8_t
Z80::MMU::readByte(const unsigned short int address)
{
  return this->strategy->readByte(address);
}

uint16_t
Z80::MMU::readWord(const unsigned short int address)
{
  // TODO: s->getb + sgetb << 8
  return 0;
}