#include "cansocket.h"

namespace canas::cansocket
{

template<typename T, size_t TSize = PACKET_MIN_SIZE + PAYLOAD_SIZE<typename T::PayloadType>>
can_frame serialize(const T &message)
{
    can_frame frame;
    frame.can_id = message.id;
    frame.can_dlc = message.dlc;
    std::byte *pointer = (std::byte*)frame.data;
    pointer = serializeField(pointer, message.nodeId);
    pointer = serializeField(pointer, message.dataType);
    pointer = serializeField(pointer, message.serviceCode);
    pointer = serializeField(pointer, message.messageCode);
    serializePayload(pointer, message.data);
    return frame;
}

template<typename T>
T deserialize(const can_frame &frame)
{
    T result;
    result.id = frame.can_id;
    result.dlc = frame.can_dlc;
    const std::byte *pointer = (std::byte*)frame.data;
    pointer = deserializeField(pointer, result.nodeId);
    pointer = deserializeField(pointer, result.dataType);
    pointer = deserializeField(pointer, result.serviceCode);
    pointer = deserializeField(pointer, result.messageCode);
    deserializePayload(pointer, result.data);
    return result;
}

} // namespace canas::cansocket