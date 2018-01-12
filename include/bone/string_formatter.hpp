#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

class string_formatter {
public:
  string_formatter(std::string format)
    : base(std::move(format))
  {
    std::size_t pos1 = 0;
    for (std::size_t pos2 = 0; pos2 < base.size(); ++pos2) {
      if (base[pos2] == '%') {
        if (++pos2 == base.size()) break;
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
            break;
          }
        }
        if (pos2 == base.size()) break;
        while()
      }
    }
    parts.emplace_back(base.data() + pos1, base.size() - pos1);
  }
private:
  enum class length_modifier { NA, hh, h, l, ll, j, z, t, L };
  enum class conversion_type { c, s, d, o, x, X, u, f, e, E, a, A, g, G, n, p };

  struct conversion {
    int width;
    int precision;
    length_modifier lenmod;
    conversion_type type;
    bool ljust;
    bool sign;
    bool alt;
    bool zero;
  };

  std::string base;
  std::vector<std::string_view> parts;
  std::vector<conversion> convs;
};
