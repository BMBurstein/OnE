#pragma once

#include <stdexcept>

namespace bone{

struct copy_counter {
  int copies = 0;
  int moves = 0;
  mutable int copied_from = 0;
  mutable int moved_from = 0;

  copy_counter() = default;
  copy_counter(copy_counter const& rhs) noexcept { copies = rhs.copies; moves = rhs.moves; copies++; rhs.copied_from++; }
  copy_counter(copy_counter&& rhs) noexcept { copies = rhs.copies; moves = rhs.moves; moves++; rhs.moved_from++; }
};

struct copy_only {
  copy_only() = default;
  copy_only(copy_only const&) = default;
  copy_only(copy_only&&) = delete;

  copy_counter cc;
};

struct move_only {
  move_only() = default;
  move_only(move_only const&) = delete;
  move_only(move_only&&) = default;

  copy_counter cc;
};

struct move_only_rt {
  move_only_rt() = default;
  move_only_rt(move_only_rt const&) { throw std::logic_error("called copy ctor"); }
  move_only_rt(move_only_rt&&) = default;

  copy_counter cc;
};

struct no_move_copy {
  no_move_copy() = default;
  no_move_copy(no_move_copy const&) = delete;
  no_move_copy(no_move_copy&&) = delete;

  copy_counter cc;
};

struct no_move_copy_rt {
  no_move_copy_rt() = default;
  no_move_copy_rt(no_move_copy_rt const&) { throw std::logic_error("called copy ctor"); }
  no_move_copy_rt(no_move_copy_rt&&) { throw std::logic_error("called move ctor"); }

  copy_counter cc;
};

}
