#ifndef PACKETS_H
#define PACKETS_H

#include "canas.h"
#include "id.h"

namespace canas
{
#define CANAS_VAR(id, type, name) \
    using name##_t = Packet<type, id>;
#include "declare.h"
#undef CANAS_VAR
using ptuTisRequest_t = Packet<int16_t[2], ptuServiceRequest, TIS>;
using ptuTisResponse_t = Packet<nodata, ptuServiceResponse, TIS>;
using ptuIdsRequest_t = Packet<nodata, ptuServiceRequest, IDS>;
using ptuIdsResponse_t = Packet<uint8_t[4], ptuServiceResponse, IDS>;
using ptuEmergencyEvent_t = Packet<EmergencyData, ptuEmergencyEvent>;
}

#endif // PACKETS_H
