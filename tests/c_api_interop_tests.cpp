#include "bone/c_api_interop.hpp"

#include "catch.hpp"

#include <algorithm>

namespace {
  std::size_t expLen;

  void check1(char* buf, int size) {
    REQUIRE(size == expLen);
    std::fill_n(buf, size, 0xBB);
  }
  void check2(unsigned char* buf, unsigned int size) {
    REQUIRE(size == expLen);
    std::fill_n(buf, size, 0xAA);
  }
  void check3(void* buf, long size) {
    REQUIRE(size == expLen);
    std::fill_n((char*)buf, size, 0x55);
  }
  void check4(char* buf, unsigned long size) {
    REQUIRE(size == expLen);
    std::fill_n(buf, size, 0x42);
  }
  void check5(int* buf, std::size_t size) {
    REQUIRE(size == expLen);
    std::fill_n(buf, size, 0xC3);
  }
}

TEST_CASE("c api interop") {
  bone::buffer buf(256);
  expLen = 256;
  REQUIRE(buf.size() == 256);

  auto comp = [&buf](unsigned char val) {
    for (std::size_t i = 0; i < buf.size(); ++i) {
      REQUIRE(buf.data()[i] == char(val));
    }
  };

  check1(buf, buf);
  comp(0xBB);
  check2(buf, buf);
  comp(0xAA);
  check3(buf, buf);
  comp(0x55);
  check4(buf, buf);
  comp(0x42);
  //check5(buf, buf); //wont compile
  //comp(0xC3);
}
