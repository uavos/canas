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

} // namespace canas
