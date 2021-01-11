#pragma once

#include "serdes.h"

template<typename T>
std::byte *serializeField(std::byte *pointer, const T &field)
{
    memcpy(pointer, &field, sizeof(T));
    return pointer + sizeof(T);
}

template<typename T>
void serializePayload(std::byte *pointer, const T &payload)
{
    serializeField(pointer, payload);
}

template<>
void serializePayload(std::byte *pointer, const canas::nodata &payload)
{
}

template<>
void serializePayload(std::byte *pointer, const canas::EmergencyData &payload)
{
    pointer = serializeField(pointer, payload.errorCode);
    pointer = serializeField(pointer, payload.operationId);
    pointer = serializeField(pointer, payload.locationId);
}

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

template<typename T>
const std::byte *deserializeField(const std::byte *pointer, T &field)
{
    memcpy(&field, pointer, sizeof(T));
    return pointer + sizeof(T);
}

template<typename T>
void deserializePayload(const std::byte *pointer, T &payload)
{
    deserializeField(pointer, payload);
}

template<>
void deserializePayload(const std::byte *pointer, canas::nodata &payload)
{
}

template<>
void deserializePayload(const std::byte *pointer, canas::EmergencyData &payload)
{
    pointer = deserializeField(pointer, payload.errorCode);
    pointer = deserializeField(pointer, payload.operationId);
    pointer = deserializeField(pointer, payload.locationId);
}

template<typename T, typename Container>
T deserialize(const Container &message)
{
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
