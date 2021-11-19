#include <array>

#include "serdes.h"

namespace canas::serial
{
static const size_t PACKET_MIN_SIZE = 9;
static const size_t PACKET_MAX_SIZE = PACKET_MIN_SIZE + PAYLOAD_SIZE<uint8_t[4]>;

template<typename T, size_t TSize = PACKET_MIN_SIZE + PAYLOAD_SIZE<typename T::PayloadType>>
std::array<std::byte, TSize> serialize(const T &message);
template<typename T, typename Container>
std::optional<T> deserialize(const Container &message);

template<typename C>
uint32_t getIdFromRaw(const C &data);
template<typename It>
uint32_t getIdFromRaw(It begin, It end);
template<typename C>
uint8_t getDlcFromRaw(const C &data);
template<typename It>
uint8_t getDlcFromRaw(It begin, It end);
template<typename C>
uint8_t getNodeIdFromRaw(const C &data);
template<typename It>
uint8_t getNodeIdFromRaw(It begin, It end);
template<typename C>
uint8_t getDataTypeFromRaw(const C &data);
template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end);
template<typename C>
uint8_t getSrvCodeFromRaw(const C &data);
template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end);
template<typename C>
uint8_t getMsgCodeFromRaw(const C &data);
template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end);

} // namespace canas::serial

#include "serial_timpl.h"