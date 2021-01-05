#ifndef PACKETS_H
#define PACKETS_H

#include "canas.h"
#include "id.h"

namespace canas
{
#define CANAS_VAR(id, type, name) \
    using name##_t = CanAsPacket<type, id>;
#include "declare.h"
#undef CANAS_VAR
using ptuTisRequest_t = CanAsPacket<int16_t[2], ptuServiceRequest, TIS>;
using ptuTisResponse_t = CanAsPacket<nodata, ptuServiceResponse, TIS>;
using ptuIdsRequest_t = CanAsPacket<nodata, ptuServiceRequest, IDS>;
using ptuIdsResponse_t = CanAsPacket<uint8_t[4], ptuServiceResponse, IDS>;
using ptuEmergencyEvent_t = CanAsPacket<EmergencyData, ptuEmergencyEvent>;
} // namespace canas

#endif // PACKETS_H
