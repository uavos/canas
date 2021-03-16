#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include "core.h"

namespace canas
{

template<>
constexpr uint8_t PAYLOAD_TYPE<float> = ptFloat;
template<>
constexpr uint8_t PAYLOAD_TYPE<int32_t> = ptLong;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint32_t> = ptUlong;
template<>
constexpr uint8_t PAYLOAD_TYPE<int16_t> = ptShort;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint16_t> = ptUshort;
template<>
constexpr uint8_t PAYLOAD_TYPE<int16_t[2]> = ptShort2;
template<>
constexpr uint8_t PAYLOAD_TYPE<int8_t> = ptChar;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t> = ptUchar;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t[2]> = ptUchar2;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t[3]> = ptUchar3;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t[4]> = ptUchar4;
template<>
constexpr uint8_t PAYLOAD_TYPE<nodata> = ptNoData;
template<>
constexpr uint8_t PAYLOAD_TYPE<EmergencyData> = ptError;

template<>
constexpr size_t PAYLOAD_SIZE<nodata> = 0;
template<>
constexpr size_t PAYLOAD_SIZE<EmergencyData> = 4;

template<typename It>
std::byte getByteAt(It begin, It end, uint8_t idx)
{
    if(std::distance(begin, end) >= int(PACKET_MIN_SIZE)) {
        std::advance(begin, idx);
        return *begin;
    }

    std::cerr << "getByteAt: Wrong message size" << std::endl;
    return std::numeric_limits<std::byte>::max();
}

template<typename C>
uint32_t getIdFromRaw(const C &data)
{
    return getIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint32_t getIdFromRaw(It begin, It end)
{
    uint32_t id = uint32_t(getByteAt(begin, end, 3)) << 24 |
                  uint32_t(getByteAt(begin, end, 2)) << 16 |
                  uint32_t(getByteAt(begin, end, 1)) << 8 |
                  uint32_t(getByteAt(begin, end, 0));
    return id;
}

template<typename C>
uint8_t getDlcFromRaw(const C &data)
{
    return getDlcFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDlcFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 4));
}

template<typename C>
uint8_t getNodeIdFromRaw(const C &data)
{
    return getNodeIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getNodeIdFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 5));
}

template<typename C>
uint8_t getDataTypeFromRaw(const C &data)
{
    return getDataTypeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 6));
}

template<typename C>
uint8_t getSrvCodeFromRaw(const C &data)
{
    return getSrvCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 7));
}

template<typename C>
uint8_t getMsgCodeFromRaw(const C &data)
{
    return getMsgCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 8));
}

} // namespace canas
