#ifndef CANAS_H
#define CANAS_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include <cstddef>

namespace canas
{

enum PayloadType {
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

enum ServiceCode {
    IDS = 0,            //identification service
    TIS = 5             //transmission interval service
};

enum ErrorCode {
    OK = 0,
    OUT_OF_RANGE = -6   //CAN identifier or transmission rate out of range
};

struct nodata {
};

template<typename T>
static constexpr uint8_t PAYLOAD_TYPE;
template<typename T>
static constexpr size_t PAYLOAD_SIZE = sizeof(T);

static const size_t PACKET_MIN_SIZE = 7;
static const size_t PACKET_MAX_SIZE = PACKET_MIN_SIZE + PAYLOAD_SIZE<uint8_t[4]>;

struct EmergencyData {
    uint16_t errorCode;
    int8_t operationId; //unused
    int8_t locationId;
};

template<typename T = nodata, uint16_t DEF_ID = 0, uint8_t DEF_SRV = 0>
struct Packet {
    using PayloadType = T;
    uint16_t id = DEF_ID;
    uint8_t dlc = PAYLOAD_SIZE<T>;
    uint8_t nodeId = 0;
    uint8_t dataType = PAYLOAD_TYPE<T>;
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

}

#include "canas_timpl.h"

#endif // CANAS_H
