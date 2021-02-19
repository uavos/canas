#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>
#include "canas/canas.h"

using namespace canas;

TEST_CASE("getters", "[CanAs]")
{
    Packet<nodata> packet;
    packet.id = 1;
    packet.messageCode = 2;
    packet.serviceCode = 3;
    auto raw = serialize(packet);
    REQUIRE(getIdFromRaw(raw) == 1);
    REQUIRE(getDlcFromRaw(raw) == 0);
    REQUIRE(getMsgCodeFromRaw(raw) == 2);
    REQUIRE(getSrvCodeFromRaw(raw) == 3);
    REQUIRE(getDataTypeFromRaw(raw) == NODATA);
}

template<typename T>
void checkPacket(PayloadType type, uint8_t size)
{
    Packet<T> packet;
    auto raw = serialize(packet);
    REQUIRE(getDataTypeFromRaw(raw) == type);
    REQUIRE(getDlcFromRaw(raw) == size);
}

TEST_CASE("types and sizes", "[CanAs]")
{
    checkPacket<float>(FLOAT, 4);
    checkPacket<int32_t>(LONG, 4);
    checkPacket<uint32_t>(ULONG, 4);
    checkPacket<int16_t>(SHORT, 2);
    checkPacket<uint16_t>(USHORT, 2);
    checkPacket<int16_t[2]>(SHORT2, 4);
    checkPacket<int8_t>(CHAR, 1);
    checkPacket<uint8_t>(UCHAR, 1);
    checkPacket<uint8_t[4]>(UCHAR4, 4);
    checkPacket<nodata>(NODATA, 0);
    checkPacket<EmergencyData>(ERROR, 4);
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

TEST_CASE("serialize", "[CanAs]")
{
    checkSerialize<float>({0, 0, 0, 0, 4, 0, FLOAT, 0, 0, 0, 0, 0, 0}, 0);
    checkSerialize<int32_t>({0, 0, 0, 0, 4, 0, LONG, 0, 0, 42, 0, 0, 0}, 42);
    checkSerialize<uint32_t>({0, 0, 0, 0, 4, 0, ULONG, 0, 0, 42, 0, 0, 0}, 42);
    checkSerialize<int16_t>({0, 0, 0, 0, 2, 0, SHORT, 0, 0, 42, 0}, 42);
    checkSerialize<uint16_t>({0, 0, 0, 0, 2, 0, USHORT, 0, 0, 42, 0}, 42);
    checkSerialize<int16_t[2]>({0, 0, 0, 0, 4, 0, SHORT2, 0, 0, 4, 0, 2, 0}, {4, 2});
    checkSerialize<int8_t>({0, 0, 0, 0, 1, 0, CHAR, 0, 0, 42}, 42);
    checkSerialize<uint8_t>({0, 0, 0, 0, 1, 0, UCHAR, 0, 0, 42}, {42});
    checkSerialize<uint8_t[4]>({0, 0, 0, 0, 4, 0, UCHAR4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkSerialize<nodata>({0, 0, 0, 0, 0, 0, NODATA, 0, 0}, nodata());
    checkSerialize<EmergencyData>({0, 0, 0, 0, 4, 0, ERROR, 0, 0, 1, 0, 2, 3}, {1, 2, 3});
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
        REQUIRE(packet.data == value);
}

bool operator==([[maybe_unused]] const nodata &a, [[maybe_unused]] const nodata &b)
{
    return true;
}

bool operator==(const EmergencyData &a, const EmergencyData &b)
{
    return a.errorCode == b.errorCode &&
           a.locationId == b.locationId &&
           a.operationId == b.operationId;
}

TEST_CASE("deserialize", "[CanAs]")
{
    checkDeserialize<float, 13>({0, 0, 0, 0, 4, 0, FLOAT, 0, 0, 0, 0, 0, 0}, 0);
    checkDeserialize<int32_t, 13>({0, 0, 0, 0, 4, 0, LONG, 0, 0, 42, 0, 0, 0}, 42);
    checkDeserialize<uint32_t, 13>({0, 0, 0, 0, 4, 0, ULONG, 0, 0, 42, 0, 0, 0}, 42);
    checkDeserialize<int16_t, 11>({0, 0, 0, 0, 2, 0, SHORT, 0, 0, 42, 0}, 42);
    checkDeserialize<uint16_t, 11>({0, 0, 0, 0, 2, 0, USHORT, 0, 0, 42, 0}, 42);
    checkDeserialize<int16_t[2], 13>({0, 0, 0, 0, 4, 0, SHORT2, 0, 0, 4, 0, 2, 0}, {4, 2});
    checkDeserialize<int8_t, 10>({0, 0, 0, 0, 1, 0, CHAR, 0, 0, 42}, 42);
    checkDeserialize<uint8_t, 10>({0, 0, 0, 0, 1, 0, UCHAR, 0, 0, 42}, {42});
    checkDeserialize<uint8_t[4], 13>({0, 0, 0, 0, 4, 0, UCHAR4, 0, 0, 1, 2, 3, 4}, {1, 2, 3, 4});
    checkDeserialize<nodata, 9>({0, 0, 0, 0, 0, 0, NODATA, 0, 0}, nodata());
    checkDeserialize<EmergencyData, 13>({0, 0, 0, 0, 4, 0, ERROR, 0, 0, 1, 0, 2, 3}, {1, 2, 3});
}