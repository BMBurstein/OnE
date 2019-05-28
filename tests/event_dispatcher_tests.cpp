#include "bone/event_dispatcher.hpp"
#include "bone/move_checker.hpp"

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

  void func1(S s) { s.count(); }
  void func2(S const s) { s.count(); }
  void func3(S& s) { s.count(); }
  void func4(S const& s) { s.count(); }
  void func5(S&& s) { s.count(); }

  bool true_f(int a, int& b) { b += a; a++; return true; }
  bool false_f(int a, int& b) { b += a; a++; return false; }
}

TEST_CASE("event dispatcher") {
  SECTION("basic") {
    bone::event_dispatcher<int, int&> ed;

    int step = 3;
    int sum = 42;
    auto h1 = ed.add(true_f);
    auto h2 = ed.add(true_f);
    auto h3 = ed.add(true_f);

    REQUIRE(ed(step, sum));
    REQUIRE(sum == 51);
    REQUIRE(step == 3);

    ed.remove(h2);
    REQUIRE(ed(step, sum));
    REQUIRE(sum == 57);

    ed.remove(h1);
    ed.remove(h3);
    REQUIRE(ed(step, sum));
    REQUIRE(sum == 57);
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
    REQUIRE(step == 3);
  }

  SECTION("object") {
    bone::event_dispatcher<S> ed;
    S s;

    auto h1 = ed.add(&S::run1);
    auto h2 = ed.add(&S::run3);
    auto h3 = ed.add(func1);
    auto h4 = ed.add(func2);
    //auto h5 = ed.add(func3); //wont compile
    auto h6 = ed.add(func4);
    //auto h7 ed.add(func5);
    auto h8 = ed.add(&S::flag);
    auto h9 = ed.add(&S::run2);

    REQUIRE_FALSE(ed(s));
    REQUIRE(s.c == 0);

    ed.remove(h9);
    ed.remove(h3);
    ed.remove(h8);
  }

  SECTION("object ref") {
    bone::event_dispatcher<S&> ed;
    S s;

    s.flag = false;
    auto h1 = ed.add(&S::run1);
    auto h2 = ed.add(&S::run3);
    auto h3 = ed.add(func1);
    auto h4 = ed.add(func2);
    auto h5 = ed.add(func3);
    auto h6 = ed.add(func4);
    //auto h7 = ed.add(func5); //wont compile
    auto h8 = ed.add(&S::flag);

    REQUIRE_FALSE(ed(s));
    REQUIRE(s.c == 4);

    ed.remove(h3);
    ed.remove(h8);
    ed.remove(h2);

    REQUIRE(ed(s));
    REQUIRE(s.c == 7);
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
    //ed.add(func5); //wont compile

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
    //ed.add(func5); //wont compile

    REQUIRE(ed(s));
    REQUIRE(s.c == 2);
  }

  SECTION("counting copies byval") {
    bone::event_dispatcher<bone::copy_counter> ed;
    bone::copy_counter cc;

    ed.add([](bone::copy_counter cc) {
      REQUIRE(cc.copies <= 2);
      REQUIRE(cc.moves <= 1);
      return true;
    });
    ed.add([](bone::copy_counter cc) {
      REQUIRE(cc.copies <= 2);
      REQUIRE(cc.moves <= 2);
    });

    REQUIRE(ed(cc));
    REQUIRE(cc.copies == 0);
    REQUIRE(cc.moves == 0);
    REQUIRE(cc.copied_from == 1);
    REQUIRE(cc.moved_from == 0);
  }

  SECTION("counting copies byref") {
    bone::event_dispatcher<bone::copy_counter&> ed;
    bone::copy_counter cc;

    ed.add([](bone::copy_counter cc) {
      REQUIRE(cc.copies <= 1);
      REQUIRE(cc.moves == 0);
      return true;
    });
    ed.add([](bone::copy_counter& cc) {
      REQUIRE(cc.copies == 0);
      REQUIRE(cc.moves == 0);
      return true;
    });
    ed.add([](bone::copy_counter cc) {
      REQUIRE(cc.copies <= 1);
      REQUIRE(cc.moves == 0);
    });
    ed.add([](bone::copy_counter& cc) {
      REQUIRE(cc.copies == 0);
      REQUIRE(cc.moves == 0);
    });

    REQUIRE(ed(cc));
    REQUIRE(cc.copies == 0);
    REQUIRE(cc.moves == 0);
    REQUIRE(cc.copied_from == 2);
    REQUIRE(cc.moved_from == 0);
  }
}
