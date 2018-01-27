#include "z80/cartridge.hpp"

Z80::Cartridge::Cartridge(std::string fileName)
{
  std::ifstream file(fileName, std::ios::binary );
  if ( file.tellg() <= MAX_CARTRIDGE_SIZE && !!file)
  {
    char byte;
    int i = 0;
    while( file.get(byte) )
    {
      this->buffer[i] = (uint8_t)byte;
      i++;
    }
    this->loaded = true;
  }
}

void
Z80::Cartridge::initialize()
{
  this->cartridgeType = (int)this->buffer[CARTRIDGE_TYPE_ADDRESS];
  this->romSize = (int)this->buffer[ROM_SIZE_ADDRESS];
  this->ramSize = (int)this->buffer[RAM_SIZE_ADDRESS];
  std::ostringstream oss;
  for (int i = TITLE_START_ADDRESS; i <= TITLE_END_ADDRESS; i++)
  {
    oss << this->buffer[i];
  }
  this->title.append(oss.str());
}

uint8_t*
Z80::Cartridge::getCartridgeContents()
{
  return this->buffer;
}

bool
Z80::Cartridge::isLoaded()
{
  return this->loaded;
}

std::string
Z80::Cartridge::getTitle()
{
  return this->title;
}

int
Z80::Cartridge::getRomSize()
{
  return this->romSize;
}

int
Z80::Cartridge::getRamSize()
{
  return this->ramSize;
}

int
Z80::Cartridge::getCartridgeType()
{
  return this->cartridgeType;
}

bool
Z80::Cartridge::isValid()
{
  return this->loaded && this->getCartridgeType() == ROM_ONLY;
}