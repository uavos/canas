#ifndef CANAS_H
#define CANAS_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include <cstddef>

namespace canas
{

enum CanAsType
{
    NODATA  = 0,
    ERROR   = 1,
    FLOAT   = 2,
    LONG    = 3,
    ULONG   = 4,
    SHORT   = 6,
    USHORT  = 7,
    CHAR    = 9,
    UCHAR   = 10,
    SHORT2  = 12,
    UCHAR4  = 16
};

enum CanAsServiceCode
{
    IDS     = 0,            //identification service
    TIS     = 5             //transmission interval service
};

enum CanAsError
{
    OK = 0,
    OUT_OF_RANGE = -6       //CAN identifier or transmission rate out of range
};

template<typename T> CanAsType toCanAsType();

struct EmergencyData
{
    uint16_t errorCode;
    int8_t operationId;     //unused
    int8_t locationId;
}__attribute__((__packed__));

template<typename T, uint8_t DEF_SRV = 0>
struct CanAsPacket
{
    using DATA_TYPE     = T;
    uint8_t nodeId      = 0;
    uint8_t dataType    = toCanAsType<DATA_TYPE>();
    uint8_t serviceCode = DEF_SRV;
    uint8_t messageCode = 0;
    DATA_TYPE data{};
    static_assert(sizeof(DATA_TYPE) <= 4, "Wrong canas data size");
}__attribute__((__packed__));

template<typename T = CanAsPacket<uint8_t[0]>, uint16_t DEF_ID = 0>
struct CanPacket
{
    using PAYLOAD_TYPE  = T;
    uint16_t id         = DEF_ID;
    uint8_t dlc         = sizeof(PAYLOAD_TYPE);
    PAYLOAD_TYPE as;
    static_assert(sizeof(PAYLOAD_TYPE) <= 8, "Wrong can payload size");
}__attribute__((__packed__));

static const size_t CAN_PACKET_MIN_SIZE = sizeof(CanPacket<uint8_t[0]>);
static const size_t CAN_PACKET_MAX_SIZE = sizeof(CanPacket<uint8_t[8]>);
static const size_t CANAS_PACKET_MIN_SIZE = sizeof(CanPacket<CanAsPacket<uint8_t[0]>>);
static const size_t CANAS_PACKET_MAX_SIZE = sizeof(CanPacket<CanAsPacket<uint8_t[4]>>);

template<typename C> uint16_t getIdFromRaw(const C &data);
template<typename It> uint16_t getIdFromRaw(It begin, It end);
template<typename C> uint8_t getDataTypeFromRaw(const C &data);
template<typename It> uint8_t getDataTypeFromRaw(It begin, It end);
template<typename C> uint8_t getSrvCodeFromRaw(const C &data);
template<typename It> uint8_t getSrvCodeFromRaw(It begin, It end);
template<typename C> uint8_t getMsgCodeFromRaw(const C &data);
template<typename It> uint8_t getMsgCodeFromRaw(It begin, It end);

}

#include "canas_timpl.h"

#endif // CANAS_H
