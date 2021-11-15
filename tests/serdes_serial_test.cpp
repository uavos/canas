#include <catch2/catch.hpp>

#include "canas/canas.h"

using namespace canas;
using namespace canas::serial;

namespace serial_test
{

TEST_CASE("serial::getters", "[CanAs]")
{
    Packet<nodata> packet;
    packet.id = 1;
    packet.messageCode = 2;
    packet.serviceCode = 3;
    auto raw = serialize(packet);
    REQUIRE(getIdFromRaw(raw) == 1);
    REQUIRE(getDlcFromRaw(raw) == 4);
    REQUIRE(getMsgCodeFromRaw(raw) == 2);
    REQUIRE(getSrvCodeFromRaw(raw) == 3);
    REQUIRE(getDataTypeFromRaw(raw) == ptNoData);
}

template<typename T>
void checkPacket(PayloadType type, uint8_t size)
{
    Packet<T> packet;
    auto raw = serialize(packet);
    REQUIRE(getDataTypeFromRaw(raw) == type);
    REQUIRE(getDlcFromRaw(raw) == size + 4);
}

TEST_CASE("serial::types and sizes", "[CanAs]")
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
    auto raw = serialize(packet);
    REQUIRE(raw.size() == data.size());
    for(size_t i = 0; i < raw.size(); i++) {
        REQUIRE(uint8_t(raw[i]) == data[i]);
    }
}

TEST_CASE("serial::serialize", "[CanAs]")
{
    checkSerialize<float>({0, 0, 0, 0, 8, 0, ptFloat, 0, 0, 0, 0, 0, 0}, 0);
    checkSerialize<int32_t>({0, 0, 0, 0, 8, 0, ptLong, 0, 0, 42, 0, 0, 0}, 42);
    checkSerialize<uint32_t>({0, 0, 0, 0, 8, 0, ptUlong, 0, 0, 42, 0, 0, 0}, 42);
    checkSerialize<int16_t>({0, 0, 0, 0, 6, 0, ptShort, 0, 0, 42, 0}, 42);
    checkSerialize<uint16_t>({0, 0, 0, 0, 6, 0, ptUshort, 0, 0, 42, 0}, 42);
    checkSerialize<int16_t[2]>({0, 0, 0, 0, 8, 0, ptShort2, 0, 0, 4, 0, 2, 0}, {4, 2});
    checkSerialize<int8_t>({0, 0, 0, 0, 5, 0, ptChar, 0, 0, 42}, 42);
    checkSerialize<uint8_t>({0, 0, 0, 0, 5, 0, ptUchar, 0, 0, 42}, {42});
    checkSerialize<uint8_t[4]>({0, 0, 0, 0, 8, 0, ptUchar4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkSerialize<nodata>({0, 0, 0, 0, 4, 0, ptNoData, 0, 0}, nodata());
    checkSerialize<EmergencyData>({0, 0, 0, 0, 8, 0, ptError, 0, 0, 1, 0, 2, 3}, {1, 2, 3});
}

template<typename T, size_t TSize>
void checkDeserialize(const std::array<uint8_t, TSize> &data, const T &value)
{
    std::array<std::byte, TSize> data2;
    for(size_t i = 0; i < TSize; i++)
        data2[i] = std::byte(data[i]);
    auto packet = deserialize<Packet<T>>(data2);
    REQUIRE(packet.dataType == getDataTypeFromRaw(data2));
    if constexpr(std::is_array_v<T>)
        for(size_t i = 0; i < std::extent_v<T>; i++)
            REQUIRE(packet.data[i] == value[i]);
    else
        REQUIRE((packet.data == value));
}

TEST_CASE("serial::deserialize", "[CanAs]")
{
    checkDeserialize<float, 13>({0, 0, 0, 0, 4, 0, ptFloat, 0, 0, 0, 0, 0, 0}, 0);
    checkDeserialize<int32_t, 13>({0, 0, 0, 0, 4, 0, ptLong, 0, 0, 42, 0, 0, 0}, 42);
    checkDeserialize<uint32_t, 13>({0, 0, 0, 0, 4, 0, ptUlong, 0, 0, 42, 0, 0, 0}, 42);
    checkDeserialize<int16_t, 11>({0, 0, 0, 0, 2, 0, ptShort, 0, 0, 42, 0}, 42);
    checkDeserialize<uint16_t, 11>({0, 0, 0, 0, 2, 0, ptUshort, 0, 0, 42, 0}, 42);
    checkDeserialize<int16_t[2], 13>({0, 0, 0, 0, 4, 0, ptShort2, 0, 0, 4, 0, 2, 0}, {4, 2});
    checkDeserialize<int8_t, 10>({0, 0, 0, 0, 1, 0, ptChar, 0, 0, 42}, 42);
    checkDeserialize<uint8_t, 10>({0, 0, 0, 0, 1, 0, ptUchar, 0, 0, 42}, {42});
    checkDeserialize<uint8_t[4], 13>({0, 0, 0, 0, 4, 0, ptUchar4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkDeserialize<nodata, 9>({0, 0, 0, 0, 0, 0, ptNoData, 0, 0}, nodata());
    checkDeserialize<EmergencyData, 13>({0, 0, 0, 0, 4, 0, ptError, 0, 0, 1, 0, 2, 3}, {1, 2, 3});
}

} // namespace serial_test