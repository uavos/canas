#include "canas/crc16ibm.h"
#include "canas/crc16ibm_timpl.h"

namespace crc16ibm
{

void calc(std::byte byte, uint16_t &crc)
{
    crc = ((crc >> 8)) ^ crc16table.at(size_t((crc ^ uint8_t(byte)) & 0xFF));
}

}