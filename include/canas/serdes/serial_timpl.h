
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
std::optional<T> deserialize(const Container &message)
{
    if(PACKET_MIN_SIZE + PAYLOAD_SIZE < typename T::PayloadType > > message.size())
        return std::nullopt;
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
bool checkSize(It begin, It end)
{
    if(std::distance(begin, end) < int(PACKET_MIN_SIZE)) {
        std::cerr << "checkSize: Wrong message size" << std::endl;
        return false;
    }
    return true;
}

template<typename It>
uint8_t getByteValueAt(It begin, It end, uint8_t idx)
{
    if(checkSize(begin, end))
        return uint8_t(*(begin + idx));
    return 0;
}

template<typename C>
uint32_t getIdFromRaw(const C &data)
{
    return getIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint32_t getIdFromRaw(It begin, It end)
{
    uint32_t id = 0;
    if(checkSize(begin, end))
        deserializeField(begin, id);
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
    return getByteValueAt(begin, end, 4);
}

template<typename C>
uint8_t getNodeIdFromRaw(const C &data)
{
    return getNodeIdFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getNodeIdFromRaw(It begin, It end)
{
    return getByteValueAt(begin, end, 5);
}

template<typename C>
uint8_t getDataTypeFromRaw(const C &data)
{
    return getDataTypeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getDataTypeFromRaw(It begin, It end)
{
    return getByteValueAt(begin, end, 6);
}

template<typename C>
uint8_t getSrvCodeFromRaw(const C &data)
{
    return getSrvCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getSrvCodeFromRaw(It begin, It end)
{
    return getByteValueAt(begin, end, 7);
}

template<typename C>
uint8_t getMsgCodeFromRaw(const C &data)
{
    return getMsgCodeFromRaw(data.begin(), data.end());
}

template<typename It>
uint8_t getMsgCodeFromRaw(It begin, It end)
{
    return getByteValueAt(begin, end, 8);
}

} // namespace canas::serial
