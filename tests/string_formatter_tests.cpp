#include "bone/string_formatter.hpp"

#include "catch.hpp"

TEST_CASE("string formatter") {
  SECTION("ctor") {
    REQUIRE_NOTHROW(bone::string_formatter("abc%%"));
    REQUIRE_NOTHROW(bone::string_formatter("abc%%%%"));
    REQUIRE_NOTHROW(bone::string_formatter("abc"));
    REQUIRE_NOTHROW(bone::string_formatter("abc%d"));
    REQUIRE_NOTHROW(bone::string_formatter("%dabc"));
    REQUIRE_NOTHROW(bone::string_formatter("abc%0.0llX"));
    REQUIRE_THROWS_AS(bone::string_formatter("abc%llcxyz"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%LLxyz"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%hld"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%t"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%0.9ll"), std::logic_error);
    REQUIRE_THROWS_AS(bone::string_formatter("abc%%%"), std::logic_error);
  }
}
