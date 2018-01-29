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

  // set program counter to the start address of the game data (0x0100)
  this->cpu.getRegister(REG_PC)->setValue(CARTRIDGE_GAME_START_ADDRESS);
  this->booted = true;
}

Z80::CPU*
Z80::System::getCPU()
{
  return &(this->cpu);
}

void
Z80::System::run()
{
  try
  {
    this->cpu.cycle();
  }
  catch (char const* e)
  {
    std::cout << "System Error: " << e << std::endl;
    this->terminated = true;
    this->booted = false;
  }
}
