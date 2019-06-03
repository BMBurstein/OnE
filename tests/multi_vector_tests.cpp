#include "bone/multi_vector.hpp"

#include "catch.hpp"

TEST_CASE("multi vector") {
  SECTION("3d") {
    bone::multi_vector<int, 3> a(4,2,3);

    SECTION("size") {
      REQUIRE(a.size() == 4);
      REQUIRE(a(0).size() == 2);
      REQUIRE(a(0,0).size() == 3);
    }

    SECTION("assign") {
      a(0,0,0) = 42;
      a(3)(1)(2) = 228;
      a[1](0,2) = 55;
      a(0,1)[2] = 66;
      a[1][1][1] = 77;
      REQUIRE(a(3,1,2) == 228);
      REQUIRE(a(0,0,0) == 42);
      REQUIRE(a(1)(0)(2) == 55);
      REQUIRE(a[0][1][2] == 66);
      REQUIRE(a(1,1,1) == 77);
    }
  }

  SECTION("1d") {
    bone::multi_vector<char, 1> a(5);

    SECTION("size") {
      REQUIRE(a.size() == 5);
    }

    SECTION("assign") {
      a[0] = 'c';
      REQUIRE(a[0] == 'c');
    }
  }
}
