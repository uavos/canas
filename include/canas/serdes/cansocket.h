#pragma once

#include <linux/can.h>
#include "../canas.h"
#include "serdes.h"

namespace canas::cansocket
{
template<typename T, size_t TSize = PACKET_MIN_SIZE + PAYLOAD_SIZE<typename T::PayloadType>>
can_frame serialize(const T &message);
template<typename T>
T deserialize(const can_frame &frame);

uint8_t getNodeIdFromRaw(const can_frame &frame);
uint8_t getDataTypeFromRaw(const can_frame &frame);
uint8_t getSrvCodeFromRaw(const can_frame &frame);
uint8_t getMsgCodeFromRaw(const can_frame &frame);
}

#include "cansocket_timpl.h"