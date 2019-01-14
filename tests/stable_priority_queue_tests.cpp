#include "bone/stable_priority_queue.hpp"

#include "catch.hpp"

namespace {
  struct S {
    int a, b;
    S(int a, int b) : a(a), b(b) {}
    bool operator<(S const &rhs) const { return a < rhs.a; }
    bool operator>(S const &rhs) const { return a > rhs.a; }
  };

  const int N = 1000;
} // namespace

TEST_CASE("stable priority queue") {
  SECTION("misc") {
    bone::stable_pq<S> spq;

    SECTION("empty") {
      REQUIRE(spq.empty());
      REQUIRE(spq.size() == 0);
      spq.emplace(1, 2);
      REQUIRE_FALSE(spq.empty());
    }

    SECTION("push") {
      REQUIRE(spq.size() == 0);
      spq.push(S{1, 2});
      REQUIRE(spq.size() == 1);
      spq.push({1, 2});
      REQUIRE(spq.size() == 2);
      S s(1, 2);
      spq.push(s);
      REQUIRE(spq.size() == 3);
      spq.push(std::move(s));
      REQUIRE(spq.size() == 4);
    }

    SECTION("emplcae") {
      REQUIRE(spq.size() == 0);
      spq.emplace(S{1, 2});
      REQUIRE(spq.size() == 1);
      spq.emplace(1, 2);
      REQUIRE(spq.size() == 2);
      S s(1, 2);
      spq.emplace(s);
      REQUIRE(spq.size() == 3);
      spq.emplace(std::move(s));
      REQUIRE(spq.size() == 4);
    }
  }

  SECTION("stable pq") {
    bone::stable_pq<S> spq;

    SECTION("top+pop no doubles") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(i, i);
      }
      REQUIRE(spq.size() == N);

      for (int i = N - 1; i >= 0; --i) {
        REQUIRE(spq.top().a == i);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }

    SECTION("top+pop all doubles") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(42, i);
      }
      REQUIRE(spq.size() == N);

      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 42);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }

    SECTION("top+pop mix") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(42, i);
        spq.emplace(3, i);
        spq.emplace(4, i);
        spq.emplace(43, i);
      }

      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 43);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 42);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 4);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 3);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }
  }

  SECTION("stable pq reverse") {
    bone::stable_pq<S, std::greater<S>> spq;

    SECTION("top+pop no doubles") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(i, i);
      }
      REQUIRE(spq.size() == N);

      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == i);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }

    SECTION("top+pop all doubles") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(42, i);
      }
      REQUIRE(spq.size() == N);

      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 42);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }

    SECTION("top+pop mix") {
      for (int i = 0; i < N; ++i) {
        spq.emplace(42, i);
        spq.emplace(3, i);
        spq.emplace(4, i);
        spq.emplace(43, i);
      }

      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 3);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 4);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 42);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
      for (int i = 0; i < N; ++i) {
        REQUIRE(spq.top().a == 43);
        REQUIRE(spq.top().b == i);
        spq.pop();
      }
    }
  }
}
