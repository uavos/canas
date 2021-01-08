#ifndef CRC16IBM_H
#define CRC16IBM_H

#include <cstdint>
#include <cstddef>

namespace crc16ibm
{

static const uint16_t INIT_VALUE = 0xFFFF;

template<typename Container>
uint16_t calc(const Container &data);
void calc(std::byte byte, uint16_t &crc);

} // namespace crc16ibm

#include "crc16ibm_timpl.h"

#endif // CRC16IBM_H
