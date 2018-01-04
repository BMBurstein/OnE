#include "bone/event_dispatcher.hpp"

#include "catch.hpp"

namespace {
  struct S {
    mutable int c = 0;

    bool run1() const { c++; return true; }
    bool run2() { c++; return false; }
    void run3() { c++; }

    bool flag;

    void count() const { c++; }
  };

  void func1(S) { }
  void func2(S const) { }
  void func3(S& s) { s.count(); }
  void func4(S const& s) { s.count(); }

  bool true_f(int a, int& b) { b += a; return true; }
  bool false_f(int a, int& b) { b += a; return false; }
}

TEST_CASE("event_dispatcher") {
  SECTION("basic") {
    bone::event_dispatcher<int, int&> ed;

    int step = 3;
    int sum = 42;
    ed.add(true_f);
    ed.add(true_f);
    ed.add(true_f);

    REQUIRE(ed(step, sum));
    REQUIRE(sum == 51);
  }

  SECTION("false") {
    bone::event_dispatcher<int, int&> ed;

    int step = 3;
    int sum = 42;
    ed.add(true_f);
    ed.add(false_f);
    ed.add(true_f);

    REQUIRE_FALSE(ed(step, sum));
    REQUIRE(sum == 48);
  }

  SECTION("object") {
    bone::event_dispatcher<S> ed;
    S s;

    ed.add(&S::run1);
    ed.add(&S::run3);
    ed.add(func1);
    ed.add(func2);
    //ed.add(func3); //wont compile
    ed.add(func4);
    ed.add(&S::flag);
    ed.add(&S::run2);

    REQUIRE_FALSE(ed(s));
    REQUIRE(s.c == 0);
  }

  SECTION("object ref") {
    bone::event_dispatcher<S&> ed;
    S s;

    s.flag = false;
    ed.add(&S::run1);
    ed.add(&S::run3);
    ed.add(func1);
    ed.add(func2);
    ed.add(func3);
    ed.add(func4);
    ed.add(&S::flag);

    REQUIRE_FALSE(ed(s));
    REQUIRE(s.c == 4);
  }

  SECTION("object const") {
    bone::event_dispatcher<S const> ed;
    const S s{};

    ed.add(&S::run1);
    //ed.add(&S::run3); //wont compile
    ed.add(func1);
    ed.add(func2);
    //ed.add(func3); //wont compile
    ed.add(func4);

    REQUIRE(ed(s));
    REQUIRE(s.c == 0);
  }

  SECTION("object const ref") {
    bone::event_dispatcher<S const&> ed;
    const S s{};

    ed.add(&S::run1);
    //ed.add(&S::run3); //wont compile
    ed.add(func1);
    ed.add(func2);
    //ed.add(func3); //wont compile
    ed.add(func4);

    REQUIRE(ed(s));
    REQUIRE(s.c == 2);
  }
}
