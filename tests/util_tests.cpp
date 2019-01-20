#include "bone/util.hpp"

static_assert(std::is_same_v<bone::uint_min_size_t<UINT8_MAX>, std::uint8_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<UINT8_MAX+1>, std::uint16_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<UINT16_MAX>, std::uint16_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<UINT16_MAX+1>, std::uint32_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<UINT32_MAX>, std::uint32_t>);
static_assert(std::is_same_v<bone::uint_min_size_t<uint64_t(UINT32_MAX)+1>, std::uint64_t>);

static_assert(std::is_same_v<bone::sint_min_size_t<INT8_MAX>, std::int8_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT8_MAX+1>, std::int16_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT16_MAX>, std::int16_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT16_MAX+1>, std::int32_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT32_MAX>, std::int32_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<int64_t(INT32_MAX)+1>, std::int64_t>);

static_assert(std::is_same_v<bone::sint_min_size_t<INT8_MAX,INT8_MIN>, std::int8_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT8_MAX,INT8_MIN-1>, std::int16_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT8_MAX+1,INT8_MIN>, std::int16_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT16_MAX,INT16_MIN>, std::int16_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT16_MAX,INT16_MIN-1>, std::int32_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT16_MAX+1,INT16_MIN>, std::int32_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT32_MAX,INT32_MIN>, std::int32_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<INT32_MAX,int64_t(INT32_MIN)-1>, std::int64_t>);
static_assert(std::is_same_v<bone::sint_min_size_t<int64_t(INT32_MAX)+1,INT32_MIN>, std::int64_t>);

static_assert(std::is_same_v<bone::int_min_size_t<UINT8_MAX>, std::uint8_t>);
static_assert(std::is_same_v<bone::int_min_size_t<UINT8_MAX+1>, std::uint16_t>);
static_assert(std::is_same_v<bone::int_min_size_t<UINT16_MAX>, std::uint16_t>);
static_assert(std::is_same_v<bone::int_min_size_t<UINT16_MAX+1>, std::uint32_t>);
static_assert(std::is_same_v<bone::int_min_size_t<UINT32_MAX>, std::uint32_t>);
static_assert(std::is_same_v<bone::int_min_size_t<uint64_t(UINT32_MAX)+1>, std::uint64_t>);

static_assert(std::is_same_v<bone::int_min_size_t<INT8_MAX,INT8_MIN>, std::int8_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT8_MAX,INT8_MIN-1>, std::int16_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT8_MAX+1,INT8_MIN>, std::int16_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT16_MAX,INT16_MIN>, std::int16_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT16_MAX,INT16_MIN-1>, std::int32_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT16_MAX+1,INT16_MIN>, std::int32_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT32_MAX,INT32_MIN>, std::int32_t>);
static_assert(std::is_same_v<bone::int_min_size_t<INT32_MAX,int64_t(INT32_MIN)-1>, std::int64_t>);
static_assert(std::is_same_v<bone::int_min_size_t<int64_t(INT32_MAX)+1,INT32_MIN>, std::int64_t>);
