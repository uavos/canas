#pragma once

#include "canas.h"
#include "id.h"

namespace canas
{
#define CANAS_VAR(id, type, name) \
    using name##_t = Packet<type, id>;
#include "declare.h"
#undef CANAS_VAR
//TIS service
using ptuTisRequest_t = Packet<int16_t[2], ptuServiceRequest, TIS>;
using ptuTisResponse_t = Packet<nodata, ptuServiceResponse, TIS>;
//IDS service
using ptuIdsRequest_t = Packet<nodata, ptuServiceRequest, IDS>;
using ptuIdsResponse_t = Packet<uint8_t[4], ptuServiceResponse, IDS>;
//IDS UAVOS service
using ptuIdsUavosRequest_t = Packet<nodata, ptuServiceRequest, IDS_UAVOS>;
using ptuIdsUavosResponse1_t = Packet<uint8_t, ptuServiceResponse, IDS_UAVOS>;
using ptuIdsUavosResponse2_t = Packet<uint8_t[2], ptuServiceResponse, IDS_UAVOS>;
using ptuIdsUavosResponse3_t = Packet<uint8_t[3], ptuServiceResponse, IDS_UAVOS>;
using ptuIdsUavosResponse4_t = Packet<uint8_t[4], ptuServiceResponse, IDS_UAVOS>;
//FPS service
using ptuFpsRequest_t = Packet<nodata, ptuServiceRequest, FPS>;
using ptuFpsResponse_t = Packet<nodata, ptuServiceResponse, FPS>;
//DDS service
using ptuDdsRequestInit_t = Packet<uint32_t, ptuServiceRequest, DDS, MEMID>;
using ptuDdsResponse_t = Packet<uint32_t, ptuServiceResponse, DDS>;
using ptuDdsResponseFinal_t = Packet<uint32_t, ptuServiceResponse, DDS, CHKSUM>;
using ptuDdsBlob1_t = Packet<uint8_t, ptuServiceRequest, DDS>;
using ptuDdsBlob2_t = Packet<uint8_t[2], ptuServiceRequest, DDS>;
using ptuDdsBlob3_t = Packet<uint8_t[3], ptuServiceRequest, DDS>;
using ptuDdsBlob4_t = Packet<uint8_t[4], ptuServiceRequest, DDS>;
//EED service
using ptuEmergencyEvent_t = Packet<EmergencyData, ptuEmergencyEvent>;
}
