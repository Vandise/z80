#ifndef __HEX_DUMP
#define __HEX_DUMP 1

#include <streambuf>
#include <iomanip>

struct hexdump {
  void const* data;
  int len;

  hexdump(void const* data, int len) : data(data), len(len) {}

  template<class T>
  hexdump(T const& v) : data(&v), len(sizeof v) {}

  friend
  std::ostream& operator<<(std::ostream& s, hexdump const& v) {
    // don't change formatting for s
    std::ostream out (s.rdbuf());
    out << std::hex << std::setfill('0');

    unsigned char const* pc = reinterpret_cast<unsigned char const*>(v.data);

    std::string buf;
    buf.reserve(17); // premature optimization

    int i;
    for (i = 0; i < v.len; ++i, ++pc) {
      if ((i % 16) == 0) {
        if (i) {
          out << "  " << buf << '\n';
          buf.clear();
        }
        out << "  " << std::setw(4) << i << ' ';
      }

      out << ' ' << std::setw(2) << unsigned(*pc);
      buf += (0x20 <= *pc && *pc <= 0x7e) ? *pc : '.';
    }
    if (i % 16) {
      char const* spaces16x3 = "                                                ";
      out << &spaces16x3[3 * (i % 16)];
    }
    out << "  " << buf << '\n';

    return s;
  }
};

#endif