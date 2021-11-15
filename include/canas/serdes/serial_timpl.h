
#include <array>

namespace canas::serial
{

template<typename T, size_t TSize>
std::array<std::byte, TSize> serialize(const T &message)
{
    std::array<std::byte, TSize> data;
    auto pointer = data.data();
    pointer = serializeField(pointer, message.id);
    pointer = serializeField(pointer, message.dlc);
    pointer = serializeField(pointer, message.nodeId);
    pointer = serializeField(pointer, message.dataType);
    pointer = serializeField(pointer, message.serviceCode);
    pointer = serializeField(pointer, message.messageCode);
    serializePayload(pointer, message.data);
    return data;
}

template<typename T, typename Container>
T deserialize(const Container &message)
{
    if(PACKET_MIN_SIZE + PAYLOAD_SIZE < typename T::PayloadType >> message.size()) {
        std::cerr << "Not enough container size" << std::endl;
        return T();
    }
    T result;
    auto pointer = message.data();
    pointer = deserializeField(pointer, result.id);
    pointer = deserializeField(pointer, result.dlc);
    pointer = deserializeField(pointer, result.nodeId);
    pointer = deserializeField(pointer, result.dataType);
    pointer = deserializeField(pointer, result.serviceCode);
    pointer = deserializeField(pointer, result.messageCode);
    deserializePayload(pointer, result.data);
    return result;
}

template<typename It>
std::byte getByteAt(It begin, It end, uint8_t idx)
{
    if(std::distance(begin, end) >= int(PACKET_MIN_SIZE)) {
        std::advance(begin, idx);
        return *begin;
    }

    std::cerr << "getByteAt: Wrong message size" << std::endl;
    return std::numeric_limits<std::byte>::max();
}

template<typename C>
uint32_t getIdFromRaw(const C &data)
{
    return getIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint32_t getIdFromRaw(It begin, It end)
{
    uint32_t id = uint32_t(getByteAt(begin, end, 3)) << 24 |
                  uint32_t(getByteAt(begin, end, 2)) << 16 |
                  uint32_t(getByteAt(begin, end, 1)) << 8 |
                  uint32_t(getByteAt(begin, end, 0));
    return id;
}

template<typename C>
uint8_t getDlcFromRaw(const C &data)
{
    return getDlcFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDlcFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 4));
}

template<typename C>
uint8_t getNodeIdFromRaw(const C &data)
{
    return getNodeIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getNodeIdFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 5));
}

template<typename C>
uint8_t getDataTypeFromRaw(const C &data)
{
    return getDataTypeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 6));
}

template<typename C>
uint8_t getSrvCodeFromRaw(const C &data)
{
    return getSrvCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 7));
}

template<typename C>
uint8_t getMsgCodeFromRaw(const C &data)
{
    return getMsgCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end)
{
    return uint8_t(getByteAt(begin, end, 8));
}

} // namespace canas::serial
