#include "z80/system.hpp"

void
Z80::System::loadCartridge(Z80::Cartridge *cartridge)
{
  this->cartridge = cartridge;
  uint8_t* contents = this->cartridge->getCartridgeContents();
  for (int i = 0; i < MAX_CARTRIDGE_SIZE; i++)
  {
    this->mmu.setByte( (CARTRIDGE_START_ADDRESS + i),
      *(contents + i)
    );
  }
}

void
Z80::System::dumpMemory()
{
  uint8_t memory[Z80_MEMORY_SIZE];
  for (int i = 0; i <= Z80_MEMORY_SIZE; i++)
  {
    memory[i] = this->mmu.readByte(i);
  }
  std::cout << hexdump(memory) << std::endl;
}

bool
Z80::System::isTerminated()
{
  return this->terminated;
}

bool
Z80::System::isBooted()
{
  return this->booted;
}

void
Z80::System::boot()
{
  this->terminated = false;
  // todo: load the bios into memory
  //       and play the Nintendo screen

  this->booted = true;
}