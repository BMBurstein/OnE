#include "bone/util.hpp"

namespace {
  template <typename T>
  using nl = std::numeric_limits<T>;

  using u8  = std::uint8_t;
  using i8  = std::int8_t;
  using u16 = std::uint16_t;
  using i16 = std::int16_t;
  using u32 = std::uint32_t;
  using i32 = std::int32_t;
  using u64 = std::uint64_t;
  using i64 = std::int64_t;

  template <typename T>
  constexpr int64_t max() {
    return std::numeric_limits<T>::max();
  }

  template <typename T>
  constexpr int64_t max1() {
    return int64_t(std::numeric_limits<T>::max()) + 1;
  }

  template <typename T>
  constexpr int64_t min() {
    return std::numeric_limits<T>::min();
  }

  template <typename T>
  constexpr int64_t min1() {
    return int64_t(std::numeric_limits<T>::min()) - 1;
  }
}

static_assert(std::is_same_v<bone::uint_min_size_t<max<u8>()>, u8>);
static_assert(std::is_same_v<bone::uint_min_size_t<max1<u8>()>, u16>);
static_assert(std::is_same_v<bone::uint_min_size_t<max<u16>()>, u16>);
static_assert(std::is_same_v<bone::uint_min_size_t<max1<u16>()>, u32>);
static_assert(std::is_same_v<bone::uint_min_size_t<max<u32>()>, u32>);
static_assert(std::is_same_v<bone::uint_min_size_t<max1<u32>()>, u64>);

static_assert(std::is_same_v<bone::sint_min_size_t<max<i8>()>, i8>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i8>()>, i16>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i16>()>, i16>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i16>()>, i32>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i32>()>, i32>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i32>()>, i64>);

static_assert(std::is_same_v<bone::sint_min_size_t<max<i8>(),min<i8>()>, i8>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i8>(),min1<i8>()>, i16>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i8>(),min<i8>()>, i16>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i16>(),min<i16>()>, i16>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i16>(),min1<i16>()>, i32>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i16>(),min<i16>()>, i32>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i32>(),min<i32>()>, i32>);
static_assert(std::is_same_v<bone::sint_min_size_t<max<i32>(),min1<i32>()>, i64>);
static_assert(std::is_same_v<bone::sint_min_size_t<max1<i32>(),min<i32>()>, i64>);

static_assert(std::is_same_v<bone::int_min_size_t<max<u8>()>, u8>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<u8>()>, u16>);
static_assert(std::is_same_v<bone::int_min_size_t<max<u16>()>, u16>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<u16>()>, u32>);
static_assert(std::is_same_v<bone::int_min_size_t<max<u32>()>, u32>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<u32>()>, u64>);

static_assert(std::is_same_v<bone::int_min_size_t<max<i8>(),min<i8>()>, i8>);
static_assert(std::is_same_v<bone::int_min_size_t<max<i8>(),min1<i8>()>, i16>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<i8>(),min<i8>()>, i16>);
static_assert(std::is_same_v<bone::int_min_size_t<max<i16>(),min<i16>()>, i16>);
static_assert(std::is_same_v<bone::int_min_size_t<max<i16>(),min1<i16>()>, i32>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<i16>(),min<i16>()>, i32>);
static_assert(std::is_same_v<bone::int_min_size_t<max<i32>(),min<i32>()>, i32>);
static_assert(std::is_same_v<bone::int_min_size_t<max<i32>(),min1<i32>()>, i64>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<u32>(),min<i32>()>, i64>);

static_assert(std::is_same_v<bone::int_min_size_t<max<u8>(), -1>, i16>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<i8>(), -1>, i16>);
static_assert(std::is_same_v<bone::int_min_size_t<max<u16>(), -1>, i32>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<i16>(), -1>, i32>);
static_assert(std::is_same_v<bone::int_min_size_t<max<u32>(), -1>, i64>);
static_assert(std::is_same_v<bone::int_min_size_t<max1<i32>(), -1>, i64>);
