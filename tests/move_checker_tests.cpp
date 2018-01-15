#include "bone\move_checker.hpp"

#include "catch.hpp"

#include <vector>

TEST_CASE("move_checker") {
  std::vector<bone::move_only> v;
  v.emplace_back();
  v.push_back(bone::move_only());
  v.emplace_back();
  v.push_back(bone::move_only());
  v.resize(v.capacity() + 100);
  bone::move_only m;
  CHECK(v[0].cc.copies == 0);
  CHECK(v[0].cc.moves <= 4);
  CHECK(v[1].cc.copies == 0);
  CHECK(v[1].cc.moves <= 4);
  CHECK(v[2].cc.copies == 0);
  CHECK(v[2].cc.moves <= 2);
  CHECK(v[3].cc.copies == 0);
  CHECK(v[3].cc.moves <= 2);
  CHECK(v[4].cc.copies == 0);
  CHECK(v[4].cc.moves == 0);
}
