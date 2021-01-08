#ifndef SLIP_H
#define SLIP_H

#include <vector>
#include <cstdint>
#include <cstddef>
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

using Bytes = std::vector<std::byte>;

static const std::byte END{192};
static const std::byte ESC{219};
static const std::byte ESC_END{220};
static const std::byte ESC_ESC{221};

template<typename It>
struct PacketInfo {
    It begin;
    It end;
};

template<typename Container>
Bytes toSlipEncoding(const Container &data);
template<typename Container>
Bytes fromSlipEncoding(const Container &data, bool &ok);
template<typename It>
Bytes fromSlipEncoding(const PacketInfo<It> &packet, bool &crcOk);
template<typename Container, typename It = typename Container::iterator>
std::optional<PacketInfo<It>> findPacketInByteStream(const Container &data);
template<typename Container, typename It = typename Container::iterator>
void truncateByteStream(Container &data, const PacketInfo<It> &packet);
template<typename Container>
void truncateByteStream(Container &data);

} // namespace slip

#include "slip_timpl.h"

#endif // SLIP_H
