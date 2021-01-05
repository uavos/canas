#ifndef CANAS_TIMPL_H
#define CANAS_TIMPL_H

#include <cstdint>
#include <iostream>
#include <limits>
#include "canas.h"

namespace canas
{

template<>
constexpr uint8_t PAYLOAD_TYPE<float> = FLOAT;
template<>
constexpr uint8_t PAYLOAD_TYPE<int32_t> = LONG;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint32_t> = ULONG;
template<>
constexpr uint8_t PAYLOAD_TYPE<int16_t> = SHORT;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint16_t> = USHORT;
template<>
constexpr uint8_t PAYLOAD_TYPE<int16_t[2]> = SHORT2;
template<>
constexpr uint8_t PAYLOAD_TYPE<int8_t> = CHAR;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t> = UCHAR;
template<>
constexpr uint8_t PAYLOAD_TYPE<uint8_t[4]> = UCHAR4;
template<>
constexpr uint8_t PAYLOAD_TYPE<nodata> = NODATA;
template<>
constexpr uint8_t PAYLOAD_TYPE<EmergencyData> = ERROR;

template<>
constexpr size_t PAYLOAD_SIZE<nodata> = 0;
template<>
constexpr size_t PAYLOAD_SIZE<EmergencyData> = 4;

template<typename It>
uint8_t getByteAt(It begin, It end, uint8_t idx)
{
    static_assert(sizeof(typename It::value_type) == 1, "Container of bytes required");
    if(std::distance(begin, end) >= int(PACKET_MIN_SIZE)) {
        std::advance(begin, idx);
        return *begin;
    }

    std::cerr << "getByteAt: Wrong message size" << std::endl;
    return std::numeric_limits<uint8_t>::max();
}

template<typename C>
uint16_t getIdFromRaw(const C &data)
{
    return getIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint16_t getIdFromRaw(It begin, It end)
{
    auto byte0 = getByteAt(begin, end, 0);
    auto byte1 = getByteAt(begin, end, 1);
    uint16_t id = ((uint16_t)byte1 << 8) | byte0;
    return id;
}

template<typename C>
uint8_t getDataTypeFromRaw(const C &data)
{
    return getDataTypeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end)
{
    return getByteAt(begin, end, 4);
}

template<typename C>
uint8_t getSrvCodeFromRaw(const C &data)
{
    return getSrvCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end)
{
    return getByteAt(begin, end, 5);
}

template<typename C>
uint8_t getMsgCodeFromRaw(const C &data)
{
    return getMsgCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end)
{
    return getByteAt(begin, end, 6);
}

}

#endif // CANAS_TIMPL_H
