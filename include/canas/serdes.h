#pragma once

#include "canas.h"
#include <array>
#include <cstring>

namespace canas {

template<typename T, size_t TSize = PACKET_MIN_SIZE + PAYLOAD_SIZE<typename T::PayloadType>>
std::array<std::byte, TSize> serialize(const T &message);
template<typename T, typename Container>
T deserialize(const Container &message);

#include "serdes_timpl.h"

}