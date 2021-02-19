#pragma once

namespace canas
{

enum Id {
    ptuEmergencyEvent = 0,

#define CANAS_VAR(id, type, name) name = (id),
#include "declare.h"
#undef CANAS_VAR

    ptuServiceRequestHigh = 128,
    ptuServiceResponseHigh = 129,
    ptuServiceRequest = 2000,
    ptuServiceResponse = 2001,
};

}
