#ifndef SLIP_H
#define SLIP_H

#include <vector>
#include <cstdint>
#include <optional>

/* SLIP format:
 * <END> <DATA> <CRC_16_IBM> <END>
 * CRC_16_IBM - crc of all DATA bytes, before SLIP encoding applied
 *
 * Byte stuffing:
 * END = ESC, ESC_END
 * ESC = ESC, ESC_ESC
 */

namespace slip
{

using Bytes = std::vector<uint8_t>;

static const uint8_t END = 192;
static const uint8_t ESC = 219;
static const uint8_t ESC_END = 220;
static const uint8_t ESC_ESC = 221;

struct PacketInfo {
    Bytes::const_iterator begin;
    Bytes::const_iterator end;
};

template<typename Container>
Bytes toSlipEncoding(const Container &data);
Bytes fromSlipEncoding(const Bytes &data, bool &ok);
Bytes fromSlipEncoding(const PacketInfo &packet, bool &crcOk);
std::optional<PacketInfo> findPacketInByteStream(const Bytes &data);
void truncateByteStream(Bytes &data, const PacketInfo &packet);
void truncateByteStream(Bytes &data);

} // namespace slip

#include "slip_timpl.h"

#endif // SLIP_H
