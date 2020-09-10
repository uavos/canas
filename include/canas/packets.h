#ifndef PACKETS_H
#define PACKETS_H

#include "canas.h"
#include "id.h"

namespace canas
{
#define CANAS_VAR(id, type, name) \
    using name##_t = CanPacket<CanAsPacket<type>, id>;
#include "declare.h"
#undef CANAS_VAR
using ptuTisRequest_t = CanPacket<CanAsPacket<int16_t[2], TIS>, ptuServiceRequest>;
using ptuTisResponse_t = CanPacket<CanAsPacket<uint8_t[0], TIS>, ptuServiceResponse>;
using ptuIdsRequest_t = CanPacket<CanAsPacket<uint8_t[0], IDS>, ptuServiceRequest>;
using ptuIdsResponse_t = CanPacket<CanAsPacket<uint8_t[4], IDS>, ptuServiceResponse>;
using ptuEmergencyEvent_t = CanPacket<CanAsPacket<EmergencyData>, ptuEmergencyEvent>;
} // namespace canas

#endif // PACKETS_H
