#ifndef __Z80_CARTRIDGE
#define __Z80_CARTRIDGE 1

#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include "z80/common.hpp"

// Cartridge types
//    currently only support ROM_ONLY (ie tetris) see page 11 of the manual
//    other cartridges can be supported in the future
#define ROM_ONLY 0
#define CARTRIDGE_TYPE_ADDRESS 0x0147
#define ROM_SIZE_ADDRESS       0x0148
#define RAM_SIZE_ADDRESS       0x0149
#define TITLE_START_ADDRESS    0x0134
#define TITLE_END_ADDRESS      0x0142

namespace Z80
{
  class Cartridge
  {
    private:
      int cartridgeType;
      int romSize;
      int ramSize;
      std::string title = "";
      bool loaded = false;
      uint8_t buffer[MAX_CARTRIDGE_SIZE];

    public:
      Cartridge(std::string fileName);
      void initialize();
      bool isLoaded();
      std::string getTitle();
      int getRomSize();
      int getRamSize();
      int getCartridgeType();
      bool isValid();

  };
}


#endif