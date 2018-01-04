#include "bone/step_iterator.hpp"

#include "catch.hpp"

#include <vector>

TEST_CASE("step iterator") {
  std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

  SECTION("exact fit") {
    auto i1 = bone::make_step_iterator(v.begin(), v.end(), 2);
    auto i2 = bone::make_step_iterator(v.begin(), 2, 10);

    i1++;
    ++i1;
    auto i3 = i1;
    i3 += 3;
    i3--;
    i1 -= 2;
    REQUIRE(i1 == i2);
    REQUIRE(i3 - i1 == 4);
    REQUIRE(i1 < i3);
    REQUIRE(i1 != i3);
    REQUIRE_FALSE(i1 == i3);
    REQUIRE_FALSE(i1 + 5 <= i3);
    REQUIRE(*i1 == 1);
    REQUIRE(*i3 == 9);
    REQUIRE(i1 + 5 == bone::make_step_iterator(v.end()));
  }

  SECTION("not exact fit") {
    auto i1 = bone::make_step_iterator(v.begin(), v.end(), 3);
    auto i2 = bone::make_step_iterator(v.begin(), 3, 10);

    i1++;
    ++i1;
    auto i3 = i1;
    i3 += 2;
    i3--;
    i1 -= 2;
    REQUIRE(i1 == i2);
    REQUIRE(i3 - i1 == 3);
    REQUIRE(i1 < i3);
    REQUIRE(i1 != i3);
    REQUIRE_FALSE(i1 == i3);
    REQUIRE_FALSE(i1 + 4 <= i3);
    REQUIRE(*i1 == 1);
    REQUIRE(*i3 == 10);
    REQUIRE(4 + i1 == bone::make_step_iterator(v.end()));
  }
}
