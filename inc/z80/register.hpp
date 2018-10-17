#ifndef __Z80_REGISTER
#define __Z80_REGISTER 1

#include <cstdint>

/*

  Z80 registers are 8bit. However, some instructions allow two registers
  to be addressed as 16bit.
  
  For now I'll leave the register to contain a 16bit value and update
  with 8 and 16 bit operations.
  
  The register associations are as follows:

    UPPER      LOWER
      A          F
      B          C
      D          E
      H          L

  However, there are also two 16bit registers:
  
    SP (stack pointer)
    PC (program counter)

*/

namespace Z80
{
  class Register
  {
    private:
      uint16_t value;

    public:
      Register(const uint16_t value = 0x0000);
      void     setLower(const uint8_t value);
      void     setUpper(const uint8_t value);
      void     setValue(const uint16_t value);
      uint8_t  getLower();
      uint8_t  getUpper();
      uint16_t getValue();
      void clear();
  };
}

#endif