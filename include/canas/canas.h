#ifndef CANAS_H
#define CANAS_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include <cstddef>

namespace canas
{

struct nodata {
};

enum CanAsType {
    NODATA = 0,
    ERROR = 1,
    FLOAT = 2,
    LONG = 3,
    ULONG = 4,
    SHORT = 6,
    USHORT = 7,
    CHAR = 9,
    UCHAR = 10,
    SHORT2 = 12,
    UCHAR4 = 16
};

enum CanAsServiceCode {
    IDS = 0, //identification service
    TIS = 5  //transmission interval service
};

enum CanAsError {
    OK = 0,
    OUT_OF_RANGE = -6 //CAN identifier or transmission rate out of range
};


template<typename T>
CanAsType toCanAsType();

template<typename PACKET>
constexpr size_t getPayloadSize();

static const size_t CANAS_PACKET_MIN_SIZE = 7;
static const size_t CANAS_PACKET_MAX_SIZE = CANAS_PACKET_MIN_SIZE + getPayloadSize<uint8_t[4]>();

struct EmergencyData {
    uint16_t errorCode;
    int8_t operationId; //unused
    int8_t locationId;
};

template<typename T = nodata, uint16_t DEF_ID = 0, uint8_t DEF_SRV = 0>
struct CanAsPacket {
    using PayloadType = T;
    uint16_t id = DEF_ID;
    uint8_t dlc = getPayloadSize<T>();
    uint8_t nodeId = 0;
    uint8_t dataType = toCanAsType<T>();
    uint8_t serviceCode = DEF_SRV;
    uint8_t messageCode = 0;
    T data;
};

template<typename C>
uint16_t getIdFromRaw(const C &data);
template<typename It>
uint16_t getIdFromRaw(It begin, It end);
template<typename C>
uint8_t getDataTypeFromRaw(const C &data);
template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end);
template<typename C>
uint8_t getSrvCodeFromRaw(const C &data);
template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end);
template<typename C>
uint8_t getMsgCodeFromRaw(const C &data);
template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end);

} // namespace canas

#include "canas_timpl.h"

#endif // CANAS_H
