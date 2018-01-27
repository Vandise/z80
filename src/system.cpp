#include "z80/system.hpp"

Z80::System::System()
{
  this->cpu = Z80::CPU();
  this->mmu = Z80::MMU();
  this->memory = Z80::Memory();

  this->mmu.setStrategy( &(this->memory) );
  this->cartridge = nullptr;
}

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
    memory[i] = this->memory.readByte(i);
  }
  std::cout << hexdump(memory) << std::endl;
}