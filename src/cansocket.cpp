#include "canas/serdes/cansocket.h"

namespace canas::cansocket
{

uint8_t getNodeIdFromRaw(const can_frame &frame)
{
    return frame.data[0];
}

uint8_t getDataTypeFromRaw(const can_frame &frame)
{
    return frame.data[1];
}

uint8_t getSrvCodeFromRaw(const can_frame &frame)
{
    return frame.data[2];
}

uint8_t getMsgCodeFromRaw(const can_frame &frame)
{
    return frame.data[3];
}

}