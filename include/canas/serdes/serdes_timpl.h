#pragma once

#include "serdes.h"

#include <cstring>

namespace canas
{

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
void serializePayload([[maybe_unused]] std::byte *pointer,
                      [[maybe_unused]] const nodata &payload);

template<>
void serializePayload(std::byte *pointer, const EmergencyData &payload);

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
void deserializePayload([[maybe_unused]] const std::byte *pointer,
                        [[maybe_unused]] nodata &payload);

template<>
void deserializePayload(const std::byte *pointer, EmergencyData &payload);

}