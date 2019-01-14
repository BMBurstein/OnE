#include "bone/cyclic_queue.hpp"

#include "catch.hpp"

namespace {
  const std::size_t N = 16;
}

TEST_CASE("cyclic queue") {
  bone::cyclic_queue<int, N> q;

  SECTION("basic") {
    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);
    REQUIRE_FALSE(q.pop());
    REQUIRE(q.push(42));
    REQUIRE_FALSE(q.empty());
    REQUIRE(q.size() == 1);
    REQUIRE(q.front() == 42);
    REQUIRE(q.pop());
    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);
    REQUIRE_FALSE(q.pop());
  }

  SECTION("full queue") {
    for(std::size_t i=0; i<N; ++i) {
      REQUIRE(q.emplace(i));
    }
    REQUIRE_FALSE(q.emplace(42));
    for(std::size_t i=0; i<N; ++i) {
      REQUIRE(q.front() == i);
      REQUIRE(q.pop());
    }
    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);
    REQUIRE_FALSE(q.pop());
  }
}
