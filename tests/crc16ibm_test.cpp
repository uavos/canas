#include <catch.hpp>

#include "canas/crc16ibm.h"

using namespace crc16ibm;

template<typename... Ts>
std::vector<std::byte> make_bytes(Ts &&... args) noexcept
{
    return {std::byte(std::forward<Ts>(args))...};
}

TEST_CASE("calc", "[CRC16IBM]")
{
    std::vector<std::byte> data;
    uint16_t crc;

    data = {};
    crc = INIT_VALUE;
    REQUIRE(crc == calc(data));

    data = make_bytes(1);
    crc = 0x807E;
    REQUIRE(crc == calc(data));

    data = make_bytes(1, 2, 3);
    crc = 0x6161;
    REQUIRE(crc == calc(data));

    data = make_bytes(1, 2, 3, 4);
    crc = 0x2BA1;
    REQUIRE(crc == calc(data));

    data = make_bytes(1, 219, 2, 192);
    crc = 0xD370;
    REQUIRE(crc == calc(data));

    data = make_bytes(219, 1, 192, 2);
    crc = 0xC1BA;
    REQUIRE(crc == calc(data));
}
