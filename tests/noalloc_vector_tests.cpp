#include "bone/noalloc_vector.hpp"

#include "catch.hpp"

namespace {
  const std::size_t N = 16;
}

TEST_CASE("noalloc vector") {
  bone::noalloc_vector<int, N> v;

  SECTION("basic") {
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);
    REQUIRE(v.push_back(42));
    REQUIRE_FALSE(v.empty());
    REQUIRE(v.size() == 1);
    REQUIRE(v.front() == 42);
    REQUIRE(v.back() == 42);
    REQUIRE(v.emplace_back(228));
    REQUIRE(v.size() == 2);
    REQUIRE(v.front() == 42);
    REQUIRE(v.back() == 228);
    v.pop_back();
    REQUIRE(v.size() == 1);
    REQUIRE(v.front() == 42);
    REQUIRE(v.back() == 42);
    v.pop_back();
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);
  }

  SECTION("full vector") {
    for(int i=0; i<N; ++i) {
      REQUIRE(v.emplace_back(i));
    }
    REQUIRE_FALSE(v.emplace_back(42));
    REQUIRE(*v.erase(v.begin()+3) == 4);
    REQUIRE(v.emplace(v.end()-3, 42));
    REQUIRE(v[11] == 12);
    REQUIRE(v[12] == 42);
    REQUIRE(v[13] == 13);
    REQUIRE_FALSE(v.emplace(v.end()-3, 42));
    for (auto& i : v) {
      i = 228;
    }
    while(!v.empty()) {
      REQUIRE(v.back() == 228);
      v.pop_back();
    }
    REQUIRE(v.size() == 0);
  }
}
