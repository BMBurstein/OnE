#pragma once

#include <type_traits>
#include <cstdint>
#include <limits>

namespace bone {

template <std::uintmax_t N>
using uint_min_size_t =
  std::conditional_t<
    N <= std::numeric_limits<std::uint8_t>::max(),
    std::uint8_t,
  std::conditional_t<
    N <= std::numeric_limits<std::uint16_t>::max(),
    std::uint16_t,
  std::conditional_t<
    N <= std::numeric_limits<std::uint32_t>::max(),
    std::uint32_t,
  std::conditional_t<
    N <= std::numeric_limits<std::uint64_t>::max(),
    std::uint64_t,
  std::uintmax_t
>>>>;

}