#include <memory>

namespace bone {
class buffer {
public:
  buffer(std::size_t size)
  : p(new char[size]),
    len(size)
  {
  }

  operator int()           { return static_cast<int          >(len); }
  operator unsigned int()  { return static_cast<unsigned int >(len); }
  operator long()          { return static_cast<long         >(len); }
  operator unsigned long() { return static_cast<unsigned long>(len); }
  //operator std::size_t()   { return static_cast<std::size_t  >(len); }

  operator char*()          { return static_cast     <char*         >(p.get()); }
  operator unsigned char*() { return reinterpret_cast<unsigned char*>(p.get()); }
  operator void*()          { return static_cast     <void*         >(p.get()); }

  std::size_t size() { return len; }
  char*       data() { return p.get(); }
private:
  std::unique_ptr<char[]> p;
  std::size_t len;
};

}
