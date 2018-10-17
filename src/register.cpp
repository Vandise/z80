#include "z80/register.hpp"

Z80::Register::Register(const uint16_t value)
{
  this->value = value;
}


void
Z80::Register::setLower(const uint8_t value)
{
  this->value = (this->value & 0xFF00) | value;
}

void
Z80::Register::setUpper(const uint8_t value)
{
  this->value = (this->value & 0x00FF) | ( value << 8 );
}

void
Z80::Register::setValue(const uint16_t value)
{
  this->value = value;
}

uint8_t
Z80::Register::getLower()
{
  return (uint8_t)(this->value & 0x00FF);
}

uint8_t
Z80::Register::getUpper()
{
  return (uint8_t)((this->value & 0xFF00) >> 8);
}

uint16_t
Z80::Register::getValue()
{
  return this->value;
}

void Z80::Register::clear() {
  this->value = 0x0000;
}
