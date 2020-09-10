#ifndef ID_H
#define ID_H

namespace canas
{

enum CanAsId {
    ptuEmergencyEvent = 0,

#define CANAS_VAR(id, type, name) name = (id),
#include "declare.h"
#undef CANAS_VAR

    ptuServiceRequest = 2000,
    ptuServiceResponse = 2001,
};

} // namespace canas

#endif // ID_H
