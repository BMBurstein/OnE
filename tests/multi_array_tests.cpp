#include "bone/multi_array.hpp"

#include "catch.hpp"

namespace {
  const std::size_t N = 3;
}

TEST_CASE("multi array") {
  bone::multi_array<int, 3> a(4,2,3);

  SECTION("basic") {
    REQUIRE(a.size() == 4);
  }
}
