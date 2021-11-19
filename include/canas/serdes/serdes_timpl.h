#pragma once

#include "serdes.h"

#include <cstring>

namespace canas
{

#ifdef CANAS_BIG_ENDIAN
template<typename Pointer, typename T>
Pointer serializeField(Pointer pointer, const T &field)
{
    std::byte *fieldPointer = (std::byte*)&field;
    for(size_t i = 0; i < sizeof(T); i++)
        pointer[i] = fieldPointer[i];
    return pointer + sizeof(T);
}

template<typename Pointer, typename T>
Pointer deserializeField(Pointer pointer, T &field)
{
    std::byte *fieldPointer = (std::byte*)&field;
    for(size_t i = 0; i < sizeof(T); i++)
        fieldPointer[i] = pointer[i];
    return pointer + sizeof(T);
}
#endif

#ifdef CANAS_LITTLE_ENDIAN
template<typename Pointer, typename T>
Pointer serializeField(Pointer pointer, const T &field)
{
    std::byte *fieldPointer = (std::byte*)&field;
    for(size_t i = 0; i < sizeof(T); i++)
        pointer[i] = fieldPointer[sizeof(T) - i - 1];
    return pointer + sizeof(T);
}

template<typename Pointer, typename T>
Pointer deserializeField(Pointer pointer, T &field)
{
    std::byte *fieldPointer = (std::byte*)&field;
    for(size_t i = 0; i < sizeof(T); i++)
        fieldPointer[i] = pointer[sizeof(T) - i - 1];
    return pointer + sizeof(T);
}
#endif

template<typename T>
void serializePayload(std::byte *pointer, const T &payload)
{
    if constexpr(std::rank_v<T> == 0)
        serializeField(pointer, payload);
    else
        for(size_t i = 0; i < std::extent_v<T>; i++)
            pointer = serializeField(pointer, payload[i]);
}

template<typename T>
void deserializePayload(const std::byte *pointer, T &payload)
{
    if constexpr(std::rank_v<T> == 0)
        deserializeField(pointer, payload);
    else
        for(size_t i = 0; i < std::extent_v<T>; i++)
            pointer = deserializeField(pointer, payload[i]);
}

//specs for custom payloads
template<>
void serializePayload([[maybe_unused]] std::byte *pointer,
                      [[maybe_unused]] const nodata &payload);

template<>
void serializePayload(std::byte *pointer, const EmergencyData &payload);

template<>
void deserializePayload([[maybe_unused]] const std::byte *pointer,
                        [[maybe_unused]] nodata &payload);

template<>
void deserializePayload(const std::byte *pointer, EmergencyData &payload);

}