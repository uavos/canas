#include <catch2/catch.hpp>

#include "canas/canas.h"

using namespace canas;
using namespace canas::cansocket;

namespace cansocket_test
{

TEST_CASE("cansocket::getters", "[CanAs]")
{
    Packet<nodata> packet;
    packet.id = 1;
    packet.messageCode = 2;
    packet.serviceCode = 3;
    auto frame = serialize(packet);
    REQUIRE(frame.can_id == 1);
    REQUIRE(frame.can_dlc == 4);
    REQUIRE(getMsgCodeFromRaw(frame) == 2);
    REQUIRE(getSrvCodeFromRaw(frame) == 3);
    REQUIRE(getDataTypeFromRaw(frame) == ptNoData);
}

template<typename T>
void checkPacket(PayloadType type, uint8_t size)
{
    Packet<T> packet;
    auto frame = serialize(packet);
    REQUIRE(frame.can_dlc == size + 4);
    REQUIRE(getDataTypeFromRaw(frame) == type);
}

TEST_CASE("cansocket::types and sizes", "[CanAs]")
{
    checkPacket<float>(ptFloat, 4);
    checkPacket<int32_t>(ptLong, 4);
    checkPacket<uint32_t>(ptUlong, 4);
    checkPacket<int16_t>(ptShort, 2);
    checkPacket<uint16_t>(ptUshort, 2);
    checkPacket<int16_t[2]>(ptShort2, 4);
    checkPacket<int8_t>(ptChar, 1);
    checkPacket<uint8_t>(ptUchar, 1);
    checkPacket<uint8_t[4]>(ptUchar4, 4);
    checkPacket<nodata>(ptNoData, 0);
    checkPacket<EmergencyData>(ptError, 4);
}

template<typename T>
void checkSerialize(const std::vector<uint8_t> &data, const T &value)
{
    Packet<T> packet;
    memcpy(&packet.data, &value, sizeof(T));
    auto frame = serialize(packet);
    REQUIRE(frame.can_id == 0);
    REQUIRE(frame.can_dlc == data.size());
    for(size_t i = 0; i < frame.can_dlc; i++) {
        REQUIRE(uint8_t(frame.data[i]) == data[i]);
    }
}

TEST_CASE("cansocket::serialize", "[CanAs]")
{
    checkSerialize<float>({0, ptFloat, 0, 0, 0, 0, 0, 0}, 0);
    checkSerialize<int32_t>({0, ptLong, 0, 0, 0, 0, 0, 42}, 42);
    checkSerialize<uint32_t>({0, ptUlong, 0, 0, 0, 0, 0, 42}, 42);
    checkSerialize<int16_t>({0, ptShort, 0, 0, 0, 42}, 42);
    checkSerialize<uint16_t>({0, ptUshort, 0, 0, 0, 42}, 42);
    checkSerialize<int16_t[2]>({0, ptShort2, 0, 0, 0, 4, 0, 2}, {4, 2});
    checkSerialize<int8_t>({0, ptChar, 0, 0, 42}, 42);
    checkSerialize<uint8_t>({0, ptUchar, 0, 0, 42}, {42});
    checkSerialize<uint8_t[4]>({0, ptUchar4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkSerialize<nodata>({0, ptNoData, 0, 0}, nodata());
    checkSerialize<EmergencyData>({0, ptError, 0, 0, 0, 1, 2, 3}, {1, 2, 3});
}

template<typename T>
void checkDeserialize(const std::vector<uint8_t> &data, const T &value)
{
    can_frame frame;
    frame.can_id = 0;
    frame.can_dlc = data.size();
    for(size_t i = 0; i < data.size(); i++)
        frame.data[i] = data[i];
    auto packet = deserialize<Packet<T>>(frame);
    REQUIRE(packet.id == 0);
    REQUIRE(packet.dlc == data.size());
    REQUIRE(packet.nodeId == frame.data[0]);
    REQUIRE(packet.dataType == frame.data[1]);
    REQUIRE(packet.serviceCode == frame.data[2]);
    REQUIRE(packet.messageCode == frame.data[3]);
    if constexpr(std::is_array_v<T>)
        for(size_t i = 0; i < std::extent_v<T>; i++)
            REQUIRE(packet.data[i] == value[i]);
    else
        REQUIRE((packet.data == value));
}

TEST_CASE("cansocket::deserialize", "[CanAs]")
{
    checkDeserialize<float>({0, ptFloat, 0, 0, 0, 0, 0, 0}, 0);
    checkDeserialize<int32_t>({0, ptLong, 0, 0, 0, 0, 0, 42}, 42);
    checkDeserialize<uint32_t>({0, ptUlong, 0, 0, 0, 0, 0, 42}, 42);
    checkDeserialize<int16_t>({0, ptShort, 0, 0, 0, 42}, 42);
    checkDeserialize<uint16_t>({0, ptUshort, 0, 0, 0, 42}, 42);
    checkDeserialize<int16_t[2]>({0, ptShort2, 0, 0, 0, 4, 0, 2}, {4, 2});
    checkDeserialize<int8_t>({0, ptChar, 0, 0, 42}, 42);
    checkDeserialize<uint8_t>({0, ptUchar, 0, 0, 42}, {42});
    checkDeserialize<uint8_t[4]>({0, ptUchar4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkDeserialize<nodata>({0, ptNoData, 0, 0}, nodata());
    checkDeserialize<EmergencyData>({0, ptError, 0, 0, 0, 1, 2, 3}, {1, 2, 3});
}
}

} // namespace cansocket_test