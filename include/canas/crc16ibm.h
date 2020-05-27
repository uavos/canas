#ifndef CRC16IBM_H
#define CRC16IBM_H

#include <cstdint>
#include <vector>

namespace crc16ibm
{

static const uint16_t INIT_VALUE = 0xFFFF;

template<typename C> uint16_t calc(const C &data);
template<typename T> void calc(T byte, uint16_t &crc);

}

#include "crc16ibm_timpl.h"

#endif // CRC16IBM_H
