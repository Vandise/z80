#include "z80/register.hpp"

Z80::Register::Register(const uint16_t value)
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