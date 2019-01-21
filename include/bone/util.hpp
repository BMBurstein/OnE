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

template <std::intmax_t MAX, std::intmax_t MIN=0>
using sint_min_size_t =
  std::conditional_t<
    MAX <= std::numeric_limits<std::int8_t>::max() && MIN >= std::numeric_limits<std::int8_t>::min(),
    std::int8_t,
  std::conditional_t<
    MAX <= std::numeric_limits<std::int16_t>::max() && MIN >= std::numeric_limits<std::int16_t>::min(),
    std::int16_t,
  std::conditional_t<
    MAX <= std::numeric_limits<std::int32_t>::max() && MIN >= std::numeric_limits<std::int32_t>::min(),
    std::int32_t,
  std::conditional_t<
    MAX <= std::numeric_limits<std::int64_t>::max() && MIN >= std::numeric_limits<std::int64_t>::min(),
    std::int64_t,
  std::uintmax_t
>>>>;

template <std::uintmax_t MAX, std::intmax_t MIN=0>
using int_min_size_t = std::conditional_t<MIN < 0, sint_min_size_t<MAX,MIN>, uint_min_size_t<MAX>>;

}
