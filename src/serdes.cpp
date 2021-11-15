#include "canas/serdes/serdes.h"

namespace canas
{

template<>
void serializePayload([[maybe_unused]] std::byte *pointer,
                      [[maybe_unused]] const nodata &payload)
{
}

template<>
void serializePayload(std::byte *pointer, const EmergencyData &payload)
{
    pointer = serializeField(pointer, payload.errorCode);
    pointer = serializeField(pointer, payload.operationId);
    pointer = serializeField(pointer, payload.locationId);
}

template<>
void deserializePayload([[maybe_unused]] const std::byte *pointer,
                        [[maybe_unused]] nodata &payload)
{
}

template<>
void deserializePayload(const std::byte *pointer, EmergencyData &payload)
{
    pointer = deserializeField(pointer, payload.errorCode);
    pointer = deserializeField(pointer, payload.operationId);
    pointer = deserializeField(pointer, payload.locationId);
}

} // namespace canas