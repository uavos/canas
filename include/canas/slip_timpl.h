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
    static_assert(sizeof(typename C::value_type) == 1, "Container of bytes required");
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
    byteStuffing(Bytes{uint8_t(crc >> 8), uint8_t(crc & 0xFF)}, result);

    result.push_back(END);
    return result;
}

} // namespace slip

#endif // SLIP_TIMPL_H
