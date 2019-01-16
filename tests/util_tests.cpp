#include "bone/util.hpp"

static_assert(std::is_same_v<bone::uint_min_size_t<255>, std::uint8_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<256>, std::uint16_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<65535>, std::uint16_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<65536>, std::uint32_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<0xffffffff>, std::uint32_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<0x100000000>, std::uint64_t>);
