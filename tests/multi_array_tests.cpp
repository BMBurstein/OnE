#include "bone/multi_array.hpp"

#include "catch.hpp"

TEST_CASE("multi array") {
  SECTION("3d") {
    bone::multi_array<int, 3> a(4,2,3);

    SECTION("size") {
      REQUIRE(a.size() == 4);
      REQUIRE(a(0).size() == 2);
      REQUIRE(a(0,0).size() == 3);
    }

    SECTION("assign value") {
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

    SECTION("assign list") {
      a(2,1) = {1,2,3};
      // a[1] = {{4,5,6},{7,8,9}};
      REQUIRE(a(2,1,0) == 1);
      REQUIRE(a(2,1,1) == 2);
      REQUIRE(a(2,1,2) == 3);
    }

    SECTION("assign fragment") {
      a(0,1) = {1,2,3};
      a(2)[1] = a[0][1];
      REQUIRE(a(2,1,0) == 1);
      REQUIRE(a(2,1,1) == 2);
      REQUIRE(a(2,1,2) == 3);
    }

    SECTION("compare") {
      bone::multi_array<int,2> b(2,3);
      a(2,1) = {42,34,56};
      a(2,2) = {1,2,3};
      b(1) = {42,34,56};
      b(2) = {1,2,3};
      REQUIRE(a[2] == b);
      REQUIRE(a(2)[0] == b[0]);
      REQUIRE(a(2,1) == b(1));
      REQUIRE_FALSE(a(2)[1] == b[0]);
      REQUIRE_FALSE(a(2,0) == b(1));
      
      REQUIRE_FALSE(a[2] != b);
      REQUIRE_FALSE(a(2)[0] != b[0]);
      REQUIRE_FALSE(a(2,1) != b(1));
      REQUIRE(a(2)[1] != b[0]);
      REQUIRE(a(2,0) != b(1));
    }
  }

  SECTION("1d") {
    bone::multi_array<char, 1> a(5);

    SECTION("size") {
      REQUIRE(a.size() == 5);
    }

    SECTION("assign") {
      a[0] = 'c';
      REQUIRE(a[0] == 'c');
    }
  }
}
