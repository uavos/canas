#include <algorithm>
#include "canas/slip.h"
#include "canas/crc16ibm.h"

using namespace crc16ibm;

namespace slip
{

Bytes fromSlipEncoding(const Bytes &data, bool &ok)
{
    PacketInfo info = {data.begin(), data.end() - 1};
    return fromSlipEncoding(info, ok);
}

Bytes fromSlipEncoding(const PacketInfo &packet, bool &crcOk)
{
    size_t dataSize = size_t(std::distance(packet.begin, std::next(packet.end)));
    //data requires begin, end markers and CRC at least
    if(dataSize >= 4)
    {
        Bytes result;
        result.reserve(dataSize - 2 - 2); //without begin, end markers and CRC
        auto startMarker = packet.begin;
        auto endMarker = packet.end;
        if(*startMarker == END && *endMarker == END)
        {
            auto startData = startMarker + 1;  //1 for END
            auto endData = endMarker - 1;      //1 for END
            while(startData <= endData)
            {
                bool isLastByte = (startData == endData);
                uint8_t decodedByte;
                if(*startData == ESC && !isLastByte && *std::next(startData) == ESC_END)
                {
                    decodedByte = END;
                    startData++;
                }
                else if(*startData == ESC && !isLastByte && *std::next(startData) == ESC_ESC)
                {
                    decodedByte = ESC;
                    startData++;
                }
                else
                    decodedByte = *startData;

                result.push_back(decodedByte);
                startData++;
            }

            //check crc
            uint8_t crc0 = result[result.size() - 1];
            uint8_t crc1 = result[result.size() - 2];
            uint16_t crcExpected = uint16_t(crc1 << 8) | crc0;
            result.resize(result.size() - 2);
            uint16_t crcReal = calc(result);
            crcOk = (crcReal == crcExpected);
            return result;
        }
    }
    crcOk = false;
    return {};
}

std::optional<PacketInfo> findPacketInByteStream(const Bytes &data)
{
    PacketInfo info;
    info.begin = std::find(data.begin(), data.end(), END);
    if(info.begin != data.end())
    {
        info.end = std::find(std::next(info.begin), data.end(), END);
        if(info.end != data.end())
            return info;
    }
    return std::nullopt;
}

void truncateByteStream(Bytes &data, const PacketInfo &packet)
{
    data.erase(data.begin(), std::next(packet.end));
}

void truncateByteStream(Bytes &data)
{
    auto it = std::find(data.begin(), data.end(), END);
    if(it != data.end())
        data.erase(data.begin(), std::next(it));
}

}
