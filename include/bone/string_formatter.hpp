#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace bone {

class string_formatter {
public:
  string_formatter(std::string format)
    : base(std::move(format))
  {
    std::size_t pos1 = 0;
    for (std::size_t pos2 = 0; pos2 < base.size(); ++pos2) {
      if (base[pos2] == '%') {
        if (++pos2 == base.size()) throw std::logic_error("Bad format string");
        if (base[pos2] == '%') {
          base.erase(pos2, 1);
          --pos2;
          continue;
        }
        parts.emplace_back(base.data() + pos1, pos2 - pos1);
        auto& c = convs.emplace_back();
        for (bool stop = false; !stop && (pos2 < base.size());) {
          switch (base[pos2++]) {
          case '+':
            c.sign = true;
            break;
          case '-':
            c.ljust = true;
            break;
          case '0':
            c.zero = true;
            break;
          case '#':
            c.alt = true;
            break;
          default:
            stop = true;
            --pos2;
            break;
          }
        }
        while (pos2 < base.size() && base[pos2] >= '0' && base[pos2] <= '9') {
          c.width *= 10;
          c.width += base[pos2] - '0';
          ++pos2;
        }
        if (pos2 < base.size() && base[pos2] == '.') {
          ++pos2;
          while (pos2 < base.size() && base[pos2] >= '0' && base[pos2] <= '9') {
            c.precision *= 10;
            c.precision += base[pos2] - '0';
            ++pos2;
          }
        }
        for (bool stop = false; !stop && (pos2 < base.size());) {
          switch (base[pos2]) {
          case 'h':
            if (c.lenmod == 0)
              c.lenmod = 'h';
            else if (c.lenmod == 'h')
              c.lenmod = 'H';
            else
              stop = true;
            break;
          case 'l':
            if (c.lenmod == 0)
              c.lenmod = 'l';
            else if (c.lenmod == 'l')
              c.lenmod = 'O';
            else
              stop = true;
            break;
          case 'j':
          case 'z':
          case 't':
          case 'L':
            if (c.lenmod == 0)
              c.lenmod = base[pos2];
            else
              stop = true;
            break;
          case 'c':
          case 's':
          case 'd':
          case 'i':
          case 'o':
          case 'x':
          case 'X':
          case 'u':
          case 'f':
          case 'e':
          case 'E':
          case 'a':
          case 'A':
          case 'g':
          case 'G':
          case 'n':
          case 'p':
            if (c.type == 0)
              c.type = base[pos2];
            stop = true;
            break;
          default:
            stop = true;
          }
          ++pos2;
        }
        if (c.type == 0) throw std::logic_error("Bad format string");
        pos1 = pos2;
      }
    }
    parts.emplace_back(base.data() + pos1, base.size() - pos1);
  }

  string_formatter& operator()(int val) {
    if (convs.front().type == 'c') {

    }
  }
private:
  enum class length_modifier { NA, hh, h, l, ll, j, z, t, L };
  enum class conversion_type { NA, c, s, d, o, x, X, u, f, e, E, a, A, g, G, n, p };

  struct conversion {
    int width = 0;
    int precision = 0;
    char lenmod = 0;
    char type = 0;
    bool ljust = false;
    bool sign = false;
    bool alt = false;
    bool zero = false;
  };

  std::string base;
  std::vector<std::string_view> parts;
  std::vector<conversion> convs;

  void error(std::string got) {
    throw std::logic_error("Expected __ got " + got);
  }
};

}
