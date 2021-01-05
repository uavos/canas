#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>
#include "canas/canas.h"
#include "canas/serdes.h"

using namespace canas;

TEST_CASE("id", "[CanAs]")
{
    // CanAsPacket<> packet;
    // packet.id = 42;
    // std::vector<uint8_t> raw(sizeof(packet));
    // memcpy(raw.data(), &packet, sizeof(packet));

    // REQUIRE(getIdFromRaw(raw) == 42);
}

TEST_CASE("type", "[CanAs]")
{
    // std::vector<uint8_t> raw;

    // CanPacket<CanAsPacket<float>> fpacket;
    // raw.resize(sizeof(fpacket));
    // memcpy(raw.data(), &fpacket, sizeof(fpacket));
    // REQUIRE(getDataTypeFromRaw(raw) == FLOAT);

    // CanPacket<CanAsPacket<int32_t>> i32packet;
    // raw.resize(sizeof(i32packet));
    // memcpy(raw.data(), &i32packet, sizeof(i32packet));
    // REQUIRE(getDataTypeFromRaw(raw) == LONG);
}

TEST_CASE("serdes", "[CanAs]")
{
    Packet<uint8_t> packet1;
    packet1.data = 42;
    auto data1 = serialize(packet1);
    for(auto c: data1) {
        std::cout << std::hex << int(c) << " ";
    }
    std::cout << std::endl;

    Packet<EmergencyData> packet2;
    packet2.data.errorCode = 1;
    packet2.data.operationId = 2;
    packet2.data.locationId = 3;
    auto data2 = serialize(packet2);
    for(auto c: data2) {
        std::cout << std::hex << int(c) << " ";
    }
    std::cout << std::endl;

    Packet<nodata> packet3;
    auto data3 = serialize(packet3);
    for(auto c: data3) {
        std::cout << std::hex << int(c) << " ";
    }
    std::cout << std::endl;

    auto data4 = data1;
    Packet<uint8_t> packet4;
    packet4 = deserialize<Packet<uint8_t>>(data4);

    auto data5 = data2;
    Packet<EmergencyData> packet5;
    packet5 = deserialize<Packet<EmergencyData>>(data5);

    REQUIRE(packet1.id == packet4.id);
    REQUIRE(packet1.dlc == packet4.dlc);
    REQUIRE(packet1.data == packet4.data);
    REQUIRE(packet1.dataType == packet4.dataType);
    REQUIRE(packet1.messageCode == packet4.messageCode);
    REQUIRE(packet1.nodeId == packet4.nodeId);
    REQUIRE(packet1.serviceCode == packet4.serviceCode);

    REQUIRE(packet2.id == packet5.id);
    REQUIRE(packet2.dlc == packet5.dlc);
    REQUIRE(packet2.data.errorCode == packet5.data.errorCode);
    REQUIRE(packet2.data.operationId == packet5.data.operationId);
    REQUIRE(packet2.data.locationId == packet5.data.locationId);
    REQUIRE(packet2.dataType == packet5.dataType);
    REQUIRE(packet2.messageCode == packet5.messageCode);
    REQUIRE(packet2.nodeId == packet5.nodeId);
    REQUIRE(packet2.serviceCode == packet5.serviceCode);
}