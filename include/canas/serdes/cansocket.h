#pragma once

#include <linux/can.h>
#include "../canas.h"
#include "serdes.h"

namespace canas::cansocket
{
static const size_t PAYLOAD_MIN_SIZE = 4;

template<typename T>
can_frame serialize(const T &message);
template<typename T>
std::optional<T> deserialize(const can_frame &frame);

uint8_t getNodeIdFromRaw(const can_frame &frame);
uint8_t getDataTypeFromRaw(const can_frame &frame);
uint8_t getSrvCodeFromRaw(const can_frame &frame);
uint8_t getMsgCodeFromRaw(const can_frame &frame);
}

#include "cansocket_timpl.h"