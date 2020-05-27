#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>
#include "canas/canas.h"

using namespace canas;

TEST_CASE("id", "[CanAs]")
{
    CanPacket<> packet;
    packet.id = 42;
    std::vector<uint8_t> raw(sizeof(packet));
    memcpy(raw.data(), &packet, sizeof(packet));

    REQUIRE(getIdFromRaw(raw) == 42);
}

TEST_CASE("type", "[CanAs]")
{
    std::vector<uint8_t> raw;

    CanPacket<CanAsPacket<float>> fpacket;
    raw.resize(sizeof(fpacket));
    memcpy(raw.data(), &fpacket, sizeof(fpacket));
    REQUIRE(getDataTypeFromRaw(raw) == FLOAT);

    CanPacket<CanAsPacket<int32_t>> i32packet;
    raw.resize(sizeof(i32packet));
    memcpy(raw.data(), &i32packet, sizeof(i32packet));
    REQUIRE(getDataTypeFromRaw(raw) == LONG);
}
