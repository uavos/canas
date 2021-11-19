#include <catch2/catch.hpp>

#include "canas/utils.h"

using namespace canas;

TEST_CASE("id2string", "[CanAs]")
{
    std::string str = id2string(ptuYawPos);
    REQUIRE(str == "ptuYawPos");
    str = id2string(Id(42));
    REQUIRE(str == "Unknown id(42)");
}