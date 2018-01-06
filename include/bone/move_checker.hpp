#pragma once

struct copy_counter {
  int copies = 0;
  int moves = 0;

  copy_counter() = default;
  copy_counter(copy_counter const& rhs) noexcept { copies = rhs.copies + 1; }
  copy_counter(copy_counter&& rhs) noexcept { rhs.moves++; }
  copy_counter& operator=(copy_counter const& rhs) noexcept { copies = rhs.copies + 1; }
  copy_counter& operator=(copy_counter&& rhs) noexcept { moves = rhs.moves++; }
};

struct move_only {
  move_only() = default;
  move_only(move_only const&) = delete;
  move_only(move_only&&) = default;
  move_only& operator=(move_only const&) = delete;
  move_only& operator=(move_only&&) = default;
};
