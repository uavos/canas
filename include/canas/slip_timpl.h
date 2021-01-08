#ifndef SLIP_TIMPL_H
#define SLIP_TIMPL_H

#include "slip.h"
#include "crc16ibm.h"

using namespace crc16ibm;

namespace slip
{

template<typename C>
void byteStuffing(const C &src, Bytes &dst)
{
    using value_type = typename std::iterator_traits<typename C::iterator>::value_type;
    static_assert(sizeof(value_type) == 1, "Container of bytes required");
    for(auto byte: src) {
        if(byte == END)
            dst.insert(dst.end(), {ESC, ESC_END});
        else if(byte == ESC)
            dst.insert(dst.end(), {ESC, ESC_ESC});
        else
            dst.push_back(byte);
    }
}

template<typename Container>
Bytes toSlipEncoding(const Container &data)
{
    Bytes result;
    result.reserve(data.size() * 2 + 2 + 2 * 2); //x2 bytes data worst case, 2 bytes markers, 2 bytes crc worst case
    result.push_back(END);

    byteStuffing(data, result);

    uint16_t crc = calc(data);
    Bytes crcBytes = {std::byte(uint8_t(crc >> 8)), std::byte(uint8_t(crc & 0xFF))};
    byteStuffing(crcBytes, result);

    result.push_back(END);
    return result;
}

template<typename Container>
Bytes fromSlipEncoding(const Container &data, bool &ok)
{
    PacketInfo<typename Container::const_iterator> info = {data.begin(), data.end()};
    return fromSlipEncoding(info, ok);
}

template<typename It>
Bytes fromSlipEncoding(const PacketInfo<It> &packet, bool &crcOk)
{
    size_t dataSize = size_t(std::distance(packet.begin, packet.end));
    //data requires begin, end markers and CRC at least
    if(dataSize >= 4) {
        Bytes result;
        result.reserve(dataSize - 2 - 2); //without begin, end markers and CRC
        auto startMarker = packet.begin;
        auto endMarker = std::prev(packet.end);
        if(*startMarker == END && *endMarker == END) {
            auto startData = startMarker + 1; //1 for END
            auto endData = endMarker - 1;     //1 for END
            while(startData <= endData) {
                bool isLastByte = (startData == endData);
                std::byte decodedByte;
                if(*startData == ESC && !isLastByte && *std::next(startData) == ESC_END) {
                    decodedByte = END;
                    startData++;
                } else if(*startData == ESC && !isLastByte && *std::next(startData) == ESC_ESC) {
                    decodedByte = ESC;
                    startData++;
                } else
                    decodedByte = *startData;
                result.push_back(decodedByte);
                startData++;
            }

            //check crc
            std::byte crc0 = result[result.size() - 1];
            std::byte crc1 = result[result.size() - 2];
            uint16_t crcExpected = uint16_t(uint8_t(crc1) << 8) | uint8_t(crc0);
            result.resize(result.size() - 2);
            uint16_t crcReal = calc(result);
            crcOk = (crcReal == crcExpected);
            return result;
        }
    }
    crcOk = false;
    return {};
}

template<typename Container, typename It>
std::optional<PacketInfo<It>> findPacketInByteStream(const Container &data)
{
    PacketInfo<It> info;
    info.begin = std::find(data.begin(), data.end(), END);
    if(info.begin != data.end()) {
        info.end = std::find(std::next(info.begin), data.end(), END);
        if(info.end != data.end()) {
            info.end = std::next(info.end);
            return info;
        }
    }
    return std::nullopt;
}

template<typename Container, typename It>
void truncateByteStream(Container &data, const PacketInfo<It> &packet)
{
    data.erase(data.begin(), packet.end);
}

template<typename Container>
void truncateByteStream(Container &data)
{
    auto it = std::find(data.begin(), data.end(), END);
    if(it != data.end())
        data.erase(data.begin(), std::next(it));
}

} // namespace slip

#endif // SLIP_TIMPL_H
