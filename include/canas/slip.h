#pragma once

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

static const std::byte END{192};
static const std::byte ESC{219};
static const std::byte ESC_END{220};
static const std::byte ESC_ESC{221};

template<typename Container>
struct PacketInfo {
    typename Container::const_iterator begin;
    typename Container::const_iterator end;
};

template<typename Container>
std::vector<std::byte> toSlipEncoding(const Container &data);
template<typename Container>
std::vector<std::byte> fromSlipEncoding(const Container &data, bool &ok);
template<typename Container>
std::vector<std::byte> fromSlipEncoding(const PacketInfo<Container> &packet, bool &crcOk);
template<typename Container>
std::optional<PacketInfo<Container>> findPacketInByteStream(const Container &data);
template<typename Container>
void truncateByteStream(Container &data, const PacketInfo<Container> &packet);
template<typename Container>
void truncateByteStream(Container &data);

} // namespace slip

#include "slip_timpl.h"
