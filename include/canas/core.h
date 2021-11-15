#pragma once

#include <vector>
#include <cstdint>
#include <type_traits>
#include <cstddef>

namespace canas
{

enum PayloadType {
    ptNoData = 0,
    ptError = 1,
    ptFloat = 2,
    ptLong = 3,
    ptUlong = 4,
    ptShort = 6,
    ptUshort = 7,
    ptChar = 9,
    ptUchar = 10,
    ptShort2 = 12,
    ptUchar4 = 16,
    ptUchar2 = 19,
    ptMemid = 21,
    ptChksum = 22,
    ptUchar3 = 27
};

enum ServiceCode {
    IDS = 0,        //identification service
    DDS = 2,        //data download service (send data to another device)
    TIS = 5,        //transmission interval service
    FPS = 6,        //flash programming service
    NIS = 11,       //node id setting service
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
    Loader = 1,
    Firmware = 2,
    Done = 3
};

template<typename T>
static constexpr uint8_t PAYLOAD_TYPE;
template<typename T>
static constexpr size_t PAYLOAD_SIZE = sizeof(T);

static const size_t PACKET_MIN_SIZE = 9;
static const size_t PACKET_MAX_SIZE = PACKET_MIN_SIZE + PAYLOAD_SIZE<uint8_t[4]>;

struct nodata {
    bool operator==([[maybe_unused]] const nodata &other);
};

struct EmergencyData {
    uint16_t errorCode;
    int8_t operationId; //unused
    int8_t locationId;
    bool operator==(const EmergencyData &other);
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

} // namespace canas

#include "core_timpl.h"
