#pragma once

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
    UCHAR4 = 16,
    UCHAR2 = 19,
    MEMID = 21,
    CHKSUM = 22,
    UCHAR3 = 27
};

enum ServiceCode {
    IDS = 0,        //identification service
    DDS = 2,        //data download service (send data to another device)
    TIS = 5,        //transmission interval service
    FPS = 6,        //flash programming service
    IDS_UAVOS = 100 //UAVOS identification service (IdsUavosType in msg code and 1-4 bytes payload)
};

enum ResponseCode {
    OUT_OF_RANGE = -6,  //CAN identifier or transmission rate out of range
    SECURITY_FAIL = -3, //invalid security code
    INVALID = -2,       //dds invalid response
    ABORT = -1,         //dds abort response
    OK = 0,
    XOFF = 0,
    XON = 1
};

enum IdsUavosType {
    NamePart1 = 0,
    NamePart2 = 1,
    NamePart3 = 2,
    NamePart4 = 3,
    NamePart5 = 4,
    NamePart6 = 5,
    NamePart7 = 6,
    NamePart8 = 7,
    DescriptionPart1 = 10,
    DescriptionPart2 = 11,
    DescriptionPart3 = 12,
    DescriptionPart4 = 13,
    DescriptionPart5 = 14,
    DescriptionPart6 = 15,
    DescriptionPart7 = 16,
    DescriptionPart8 = 17,
    DescriptionPart9 = 18,
    DescriptionPart10 = 19,
    SoftwareVersion = 20, //[major.minor.patch]
    HardwareVersion = 21, //[major.minor.patch]

    NameBegin = NamePart1,
    NameEnd = NamePart8,
    DescriptionBegin = DescriptionPart1,
    DescriptionEnd = DescriptionPart10,
};

enum FpsSecurityCode {
    WriteStart = 1,
    WriteDone = 2,
};

struct nodata {
};

template<typename T>
static constexpr uint8_t PAYLOAD_TYPE;
template<typename T>
static constexpr size_t PAYLOAD_SIZE = sizeof(T);

static const size_t PACKET_MIN_SIZE = 9;
static const size_t PACKET_MAX_SIZE = PACKET_MIN_SIZE + PAYLOAD_SIZE<uint8_t[4]>;

struct EmergencyData {
    uint16_t errorCode;
    int8_t operationId; //unused
    int8_t locationId;
};

template<typename T = nodata, uint32_t DEF_ID = 0, uint8_t DEF_SRV = 0, uint8_t DEF_TYPE = PAYLOAD_TYPE<T>>
struct Packet {
    using PayloadType = T;
    uint32_t id = DEF_ID;
    uint8_t dlc = PAYLOAD_SIZE<T> + 4;
    uint8_t nodeId = 0;
    uint8_t dataType = DEF_TYPE;
    uint8_t serviceCode = DEF_SRV;
    uint8_t messageCode = 0;
    T data{};
};

template<typename C>
uint32_t getIdFromRaw(const C &data);
template<typename It>
uint32_t getIdFromRaw(It begin, It end);
template<typename C>
uint8_t getDlcFromRaw(const C &data);
template<typename It>
uint8_t getDlcFromRaw(It begin, It end);
template<typename C>
uint8_t getNodeIdFromRaw(const C &data);
template<typename It>
uint8_t getNodeIdFromRaw(It begin, It end);
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

#include "core_timpl.h"
