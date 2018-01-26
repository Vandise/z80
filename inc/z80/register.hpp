#ifndef __Z80_REGISTER
#define __Z80_REGISTER 1

#include <cstdint>

namespace Z80
{
  class Register
  {
    private:
      uint16_t value;

    public:
      Register(const uint16_t value = 0x0000);
      uint8_t  getLower();
      uint8_t  getUpper();
      uint16_t getValue();
  };
}

#endif